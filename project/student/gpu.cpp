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
		for (int i = 0; i + 4 < (mem.framebuffer.height * mem.framebuffer.width); i += 4)
		{
			mem.framebuffer.color[i] = (uint8_t)(cmd.color.r * 255.f);
			mem.framebuffer.color[i + 1] = (uint8_t)(cmd.color.g * 255.f);
			mem.framebuffer.color[i + 2] = (uint8_t)(cmd.color.b * 255.f);
			mem.framebuffer.color[i + 3] = (uint8_t)(cmd.color.a * 255.f);
		}
	}
	if (cmd.clearDepth)
	{
		for (int i = 0; i < (mem.framebuffer.height * mem.framebuffer.width); i++)
		{
			mem.framebuffer.depth[i] = (cmd.depth);
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
		OutVertex outVertex;

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

void barycentric(glm::vec3 pos, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 &bar)
{
	glm::vec2 v0 = b - a, v1 = c - a, v2 = pos - a;

	float d00 = glm::dot(v0, v0);
	float d01 = glm::dot(v0, v1);
	float d11 = glm::dot(v1, v1);
	float d20 = glm::dot(v2, v0);
	float d21 = glm::dot(v2, v1);
	float denom = d00 * d11 - d01 * d01;

	bar.y = (d11 * d20 - d01 * d21) / denom;
	bar.z = (d00 * d21 - d01 * d20) / denom;
	bar.x = 1.0f - bar.y - bar.z;
}

void fragmentAssembly(InFragment &in, glm::vec3 pos, glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	in.gl_FragCoord.x = pos.x;
	in.gl_FragCoord.y = pos.y;

	glm::vec3 bar{0, 0, 0};

	barycentric(pos, a, b, c, bar);

	in.gl_FragCoord.z = a.z * bar.x + b.z * bar.y + c.z * bar.z;
}

void rasterize(Frame &frame, Triangle const &triangle, Program const &prg, ShaderInterface si, bool backFaceCulling)
{
	FragmentShader fs = prg.fragmentShader;

	OutVertex v[3] = {triangle.points[0], triangle.points[1], triangle.points[2]};

	if (!backFaceCulling)
	{
		if (((v[1].gl_Position.x - v[0].gl_Position.x) * (v[2].gl_Position.y - v[0].gl_Position.y) -
			 (v[2].gl_Position.x - v[0].gl_Position.x) * (v[1].gl_Position.y - v[0].gl_Position.y)) < 0.f)
		{
			OutVertex tmp;
			tmp = v[1];
			v[1] = v[2];
			v[2] = tmp;
		}
	}

	OutVertex max{};
	max.gl_Position.x = 0.f;
	max.gl_Position.y = 0.f;

	for (int i = 0; i < 3; i++)
	{
		max.gl_Position.x = glm::max(max.gl_Position.x, v[i].gl_Position.x);
		max.gl_Position.y = glm::max(max.gl_Position.y, v[i].gl_Position.y);
	}

	OutVertex min{};
	min.gl_Position.x = frame.width;
	min.gl_Position.y = frame.height;

	for (int i = 0; i < 3; i++)
	{
		min.gl_Position.x = glm::min(min.gl_Position.x, v[i].gl_Position.x);
		min.gl_Position.y = glm::min(min.gl_Position.y, v[i].gl_Position.y);
	}

	// Clipping
	float maxFrameWidth = frame.width;
	float maxFrameHeight = frame.height;

	max.gl_Position.x = glm::min(max.gl_Position.x, maxFrameWidth - 0.5f);
	max.gl_Position.y = glm::min(max.gl_Position.y, maxFrameHeight - 0.5f);

	min.gl_Position.x = glm::max(min.gl_Position.x, 0.0f);
	min.gl_Position.y = glm::max(min.gl_Position.y, 0.0f);

	//(xi1 − xi0, yi1 − yi0) = (∆xi, ∆yi)
	glm::vec2 delta[3];
	for (int i = 0; i < 3; i++)
	{
		int j = (i + 1) % 3;
		delta[i] = v[j].gl_Position - v[i].gl_Position;
	}

	for (uint32_t y = min.gl_Position.y; y <= max.gl_Position.y; ++y)
	{

		for (uint32_t x = min.gl_Position.x; x <= max.gl_Position.x; ++x)
		{
			float E[3];
			glm::vec3 pos{x + 0.5f, y + 0.5f, 0};

			for (int i = 0; i < 3; i++)
				E[i] = ((pos.y - v[i].gl_Position.y) * delta[i].x - ((pos.x - v[i].gl_Position.x) * delta[i].y));

			if (E[0] >= 0.f && E[1] >= 0.f && E[2] >= 0.f)
			{
				InFragment inFragment;

				fragmentAssembly(inFragment, pos, v[0].gl_Position, v[1].gl_Position, v[2].gl_Position);

				OutFragment outFragment;
				fs(outFragment, inFragment, si);
			}
		}
	}
}

void draw(GPUMemory &mem, DrawCommand cmd, uint32_t draw_id)
{
	ShaderInterface si;
	Program prg = mem.programs[cmd.programID];
	si.textures = &mem.textures[cmd.programID];
	si.uniforms = &mem.uniforms[cmd.programID];

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
