/*!
 * @file
 * @brief This file contains implementation of gpu
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#include <student/gpu.hpp>

void clear(GPUMemory &mem, ClearCommand cmd)
{
	if (cmd.clearColor)
	{
		for (uint64_t i = 0; i + 4 < 4 * (mem.framebuffer.height * mem.framebuffer.width); i += 4)
		{
			mem.framebuffer.color[i] = static_cast<uint8_t>(cmd.color.r * 255.f);
			mem.framebuffer.color[i + 1] = static_cast<uint8_t>(cmd.color.g * 255.f);
			mem.framebuffer.color[i + 2] = static_cast<uint8_t>(cmd.color.b * 255.f);
			mem.framebuffer.color[i + 3] = static_cast<uint8_t>(cmd.color.a * 255.f);
		}
	}
	if (cmd.clearDepth)
	{
		for (int i = 0; i < (mem.framebuffer.height * mem.framebuffer.width); i++)
		{
			mem.framebuffer.depth[i] = cmd.depth;
		}
	}
}

void computeVertexID(GPUMemory &mem, VertexArray &vao, uint32_t *shaderInvocation, InVertex &inVertex)
{
	if (vao.indexBufferID < 0)
	{
		inVertex.gl_VertexID = *shaderInvocation;
		return;
	}
	const uint32_t index = *shaderInvocation;
	const Buffer &indexBuffer = mem.buffers[vao.indexBufferID];
	const uint8_t *indexData = static_cast<const uint8_t *>(indexBuffer.data) + (vao.indexOffset / sizeof(uint8_t));

	switch (vao.indexType)
	{
	case IndexType::UINT32:
		inVertex.gl_VertexID = *reinterpret_cast<const uint32_t *>(indexData + index * sizeof(uint32_t));
		break;

	case IndexType::UINT16:
		inVertex.gl_VertexID = *reinterpret_cast<const uint16_t *>(indexData + index * sizeof(uint16_t));
		break;

	case IndexType::UINT8:
		inVertex.gl_VertexID = *reinterpret_cast<const uint8_t *>(indexData + index * sizeof(uint8_t));
		break;

	default:
		break;
	}
}

void getAttr(GPUMemory &mem, VertexAttrib *vertexAttrib, InVertex &inVertex)
{
	for (uint32_t i = 0; i < maxAttributes; i++)
	{
		const auto &attrib = vertexAttrib[i];
		if (attrib.type == AttributeType::EMPTY)
			continue;

		const auto &buffer = mem.buffers[attrib.bufferID];
		const uint8_t *bufferData = static_cast<const uint8_t *>(buffer.data);
		const uint8_t *attrData = bufferData + (attrib.offset / sizeof(uint8_t)) + (attrib.stride / sizeof(uint8_t)) * inVertex.gl_VertexID;

		switch (attrib.type)
		{
		case AttributeType::FLOAT:
			inVertex.attributes[i].v1 = *reinterpret_cast<const float *>(attrData);
			break;

		case AttributeType::VEC2:
			inVertex.attributes[i].v2 = *reinterpret_cast<const glm::vec2 *>(attrData);
			break;

		case AttributeType::VEC3:
			inVertex.attributes[i].v3 = *reinterpret_cast<const glm::vec3 *>(attrData);
			break;

		case AttributeType::VEC4:
			inVertex.attributes[i].v4 = *reinterpret_cast<const glm::vec4 *>(attrData);
			break;

		case AttributeType::UINT:
			inVertex.attributes[i].u1 = *reinterpret_cast<const uint32_t *>(attrData);
			break;

		case AttributeType::UVEC2:
			inVertex.attributes[i].u2 = *reinterpret_cast<const glm::uvec2 *>(attrData);
			break;

		case AttributeType::UVEC3:
			inVertex.attributes[i].u3 = *reinterpret_cast<const glm::uvec3 *>(attrData);
			break;

		case AttributeType::UVEC4:
			inVertex.attributes[i].u4 = *reinterpret_cast<const glm::uvec4 *>(attrData);
			break;
		}
	}
}

void VertexAssembly(GPUMemory &mem, VertexArray &vao, InVertex &inVertex, uint32_t *shaderInvocation, uint32_t *draw_id)
{
	inVertex.gl_DrawID = *draw_id;
	computeVertexID(mem, vao, shaderInvocation, inVertex);
	getAttr(mem, vao.vertexAttrib, inVertex);
}

void TriangleAssembly(GPUMemory &mem, Triangle &triangle, Program const &prg, VertexArray &vao, ShaderInterface si, uint32_t tId, uint32_t draw_id)
{
	VertexShader vs = prg.vertexShader;

	for (uint32_t i = 0; i < 3; ++i)
	{
		InVertex inVertex;

		uint32_t correctId = i + tId * 3;

		VertexAssembly(mem, vao, inVertex, &correctId, &draw_id);

		vs(triangle.points[i], inVertex, si);
	}
}

void perspectiveDivision(Triangle &triangle)
{
	for (int i = 0; i < 3; i++)
	{
		triangle.points[i].gl_Position.x /= triangle.points[i].gl_Position.w;
		triangle.points[i].gl_Position.y /= triangle.points[i].gl_Position.w;
		triangle.points[i].gl_Position.z /= triangle.points[i].gl_Position.w;
	}
}

void viewportTransformation(Triangle &triangle, uint32_t width, uint32_t height)
{
	for (int i = 0; i < 3; i++)
	{
		triangle.points[i].gl_Position.x = ((triangle.points[i].gl_Position.x * 0.5) + 0.5) * (float)width;
		triangle.points[i].gl_Position.y = ((triangle.points[i].gl_Position.y * 0.5) + 0.5) * (float)height;
	}
}

void barycentric(const glm::vec2 &pos, const glm::vec4 &a, const glm::vec4 &b, const glm::vec4 &c, glm::vec3 &bar)
{
	glm::vec4 pos_4 = {pos.x, pos.y, 0, 0};
	const glm::vec2 v0 = b - a;
	const glm::vec2 v1 = c - a;
	const glm::vec2 v2 = pos_4 - a;

	const float d00 = glm::dot(v0, v0);
	const float d01 = glm::dot(v0, v1);
	const float d11 = glm::dot(v1, v1);
	const float d20 = glm::dot(v2, v0);
	const float d21 = glm::dot(v2, v1);
	const float denom = d00 * d11 - d01 * d01;

	bar.y = (d11 * d20 - d01 * d21) / denom;
	bar.z = (d00 * d21 - d01 * d20) / denom;
	bar.x = 1.0f - bar.y - bar.z;
}

template <typename T>
T interpolateAttribute(const T &a, const T &b, const T &c, const glm::vec3 &bary)
{
	return a * bary.x + b * bary.y + c * bary.z;
}

void interpolate(InFragment &in, Triangle t, glm::vec3 bar, AttributeType *vs2fs)
{
	const glm::vec4 a = t.points[0].gl_Position;
	const glm::vec4 b = t.points[1].gl_Position;
	const glm::vec4 c = t.points[2].gl_Position;

	const Attribute *const A = t.points[0].attributes;
	const Attribute *const B = t.points[1].attributes;
	const Attribute *const C = t.points[2].attributes;

	in.gl_FragCoord.z = a.z * bar.x + b.z * bar.y + c.z * bar.z;

	const float s = (bar.x / a.w) + (bar.y / b.w) + (bar.z / c.w);

	const glm::vec3 perspectiveBary = {(bar.x / (a.w * s)), (bar.y / (b.w * s)), (bar.z / (c.w * s))};

	for (uint32_t i = 0; i < maxAttributes; i++)
	{
		switch (vs2fs[i])
		{
		case AttributeType::FLOAT:
			in.attributes[i].v1 = interpolateAttribute(A[i].v1, B[i].v1, C[i].v1, perspectiveBary);
			break;

		case AttributeType::VEC2:
			in.attributes[i].v2 = interpolateAttribute(A[i].v2, B[i].v2, C[i].v2, perspectiveBary);
			break;

		case AttributeType::VEC3:
			in.attributes[i].v3 = interpolateAttribute(A[i].v3, B[i].v3, C[i].v3, perspectiveBary);
			break;

		case AttributeType::VEC4:
			in.attributes[i].v4 = interpolateAttribute(A[i].v4, B[i].v4, C[i].v4, perspectiveBary);
			break;

		case AttributeType::UINT:
			in.attributes[i].u1 = A[i].u1;
			break;

		case AttributeType::UVEC2:
			in.attributes[i].u2 = A[i].u2;
			break;

		case AttributeType::UVEC3:
			in.attributes[i].u3 = A[i].u3;
			break;

		case AttributeType::UVEC4:
			in.attributes[i].u4 = A[i].u4;
			break;
		}
	}
}

void fragmentAssembly(InFragment &in, glm::vec2 pos, Triangle t, AttributeType *vs2fs)
{
	auto a = t.points[0], b = t.points[1], c = t.points[2];

	in.gl_FragCoord.x = pos.x;
	in.gl_FragCoord.y = pos.y;

	glm::vec3 bar{0, 0, 0};

	barycentric(pos, a.gl_Position, b.gl_Position, c.gl_Position, bar);

	interpolate(in, t, bar, vs2fs);
}

void perFragmentOperations(Frame const &framebuffer, OutFragment &outF, InFragment &inF, const glm::uvec2 &pos)
{
	glm::vec4 color = glm::clamp(outF.gl_FragColor, glm::vec4(0.f), glm::vec4(1.f));

	const uint32_t idx = pos.y * framebuffer.width + pos.x;

	const float alpha = outF.gl_FragColor.w;
	const float inDepth = inF.gl_FragCoord.z;

	if ((alpha < 1.0f) && (framebuffer.depth[idx] >= inDepth))
	{
		color = glm::mix(
			glm::vec4(static_cast<float>(framebuffer.color[(4 * idx) + 0] / 255.f),
					  static_cast<float>(framebuffer.color[(4 * idx) + 1] / 255.f),
					  static_cast<float>(framebuffer.color[(4 * idx) + 2] / 255.f),
					  static_cast<float>(framebuffer.color[(4 * idx) + 3] / 255.f)),
			glm::vec4(color.r, color.g, color.b, color.a), alpha);

		color += glm::vec4(0.0001f);

		color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
	}

	if (framebuffer.depth[idx] >= inDepth)
	{
		if (alpha > 0.5f)
			framebuffer.depth[idx] = inDepth;

		framebuffer.color[(4 * idx) + 0] = static_cast<uint8_t>(color.r * 255.f);
		framebuffer.color[(4 * idx) + 1] = static_cast<uint8_t>(color.g * 255.f);
		framebuffer.color[(4 * idx) + 2] = static_cast<uint8_t>(color.b * 255.f);
		framebuffer.color[(4 * idx) + 3] = static_cast<uint8_t>(color.a * 255.f);
	}
}

void rasterize(Frame const &frame, Triangle const &triangle, Program &prg, ShaderInterface si, bool backFaceCulling)
{
	FragmentShader fs = prg.fragmentShader;
	AttributeType *vs2fs = prg.vs2fs;
	OutVertex v[3] = {triangle.points[0], triangle.points[1], triangle.points[2]};

	if (!backFaceCulling)
	{
		const float backface = (v[1].gl_Position.x - v[0].gl_Position.x) * (v[2].gl_Position.y - v[0].gl_Position.y) -
							   (v[2].gl_Position.x - v[0].gl_Position.x) * (v[1].gl_Position.y - v[0].gl_Position.y);
		if (backface < 0.0f)
			std::swap(v[1], v[2]);
	}

	glm::vec2 max, min;
	max.x = max.y = 0.f;
	min.x = frame.width;
	min.y = frame.height;

	for (int i = 0; i < 3; i++)
	{
		max.x = glm::max(max.x, v[i].gl_Position.x);
		max.y = glm::max(max.y, v[i].gl_Position.y);
		min.x = glm::min(min.x, v[i].gl_Position.x);
		min.y = glm::min(min.y, v[i].gl_Position.y);
	}

	max.x = glm::min(max.x, static_cast<float>(frame.width - 0.5f));
	max.y = glm::min(max.y, static_cast<float>(frame.height - 0.5f));
	min.x = glm::max(min.x, 0.0f);
	min.y = glm::max(min.y, 0.0f);

	glm::vec2 delta[3];
	for (int i = 0; i < 3; i++)
	{
		int j = (i + 1) % 3;
		delta[i] = v[j].gl_Position - v[i].gl_Position;
	}

	for (uint32_t y = static_cast<uint32_t>(min.y); y <= static_cast<int>(max.y); ++y)
	{
		for (uint32_t x = static_cast<uint32_t>(min.x); x <= static_cast<int>(max.x); ++x)
		{
			float E[3];
			glm::uvec2 pos{x, y};
			glm::vec2 pos_f{x + 0.5f, y + 0.5f};

			for (int i = 0; i < 3; i++)
				E[i] = (((pos_f.y - v[i].gl_Position.y) * delta[i].x) - ((pos_f.x - v[i].gl_Position.x) * delta[i].y));

			if (E[0] >= 0.f && E[1] >= 0.f && E[2] >= 0.f)
			{
				InFragment inFragment;

				fragmentAssembly(inFragment, pos_f, triangle, vs2fs);

				OutFragment outFragment;

				fs(outFragment, inFragment, si);

				perFragmentOperations(frame, outFragment, inFragment, pos);
			}
		}
	}
}

void draw(GPUMemory &mem, DrawCommand cmd, uint32_t draw_id)
{
	ShaderInterface si;
	Program prg = mem.programs[cmd.programID];
	si.textures = mem.textures;
	si.uniforms = mem.uniforms;

	for (uint32_t n = 0; n < cmd.nofVertices / 3; ++n)
	{

		Triangle triangle;

		TriangleAssembly(mem, triangle, prg, cmd.vao, si, n, draw_id);

		perspectiveDivision(triangle);

		viewportTransformation(triangle, mem.framebuffer.width, mem.framebuffer.height);

		rasterize(mem.framebuffer, triangle, prg, si, cmd.backfaceCulling);
	}
}

//! [gpu_execute]
void gpu_execute(GPUMemory &mem, CommandBuffer &cb)
{
	uint32_t draw_id_gpu = 0;
	for (uint32_t i = 0; i < cb.nofCommands; ++i)
	{
		CommandType type = cb.commands[i].type;
		CommandData data = cb.commands[i].data;

		if (type == CommandType::CLEAR)
		{
			clear(mem, data.clearCommand);
		}
		if (type == CommandType::DRAW)
		{
			draw(mem, data.drawCommand, draw_id_gpu);
			draw_id_gpu++;
		}
	}
}
//! [gpu_execute]

/**
 * @brief This function reads color from texture.
 *
 * @param texture texture
 * @param uv uv coordinates
 *
 * @return color 4 floats
 */
glm::vec4 read_texture(Texture const &texture, glm::vec2 uv)
{
	if (!texture.data)
		return glm::vec4(0.f);
	auto uv1 = glm::fract(uv);
	auto uv2 = uv1 * glm::vec2(texture.width - 1, texture.height - 1) + 0.5f;
	auto pix = glm::uvec2(uv2);
	// auto t   = glm::fract(u2.gl_Position);
	glm::vec4 color = glm::vec4(0.f, 0.f, 0.f, 1.f);
	for (uint32_t c = 0; c < texture.channels; ++c)
		color[c] = texture.data[(pix.y * texture.width + pix.x) * texture.channels + c] / 255.f;
	return color;
}
