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

void TriangleAssembly(GPUMemory &mem, Triangle &triangle, Program const &prg, VertexArray &vao, uint32_t tId)
{
	for (int i = 0; i < 3; ++i)
	{ // smyčka přes vrcholy trojúhelníku
		InVertex inVertex;
		uint32_t correct_idx = tId + i;
		uint32_t smh = 0;
		ShaderInterface si;

		VertexAssembly(mem, vao, inVertex, &correct_idx, &smh);
		prg.vertexShader(triangle.points[i], inVertex, si);
	}
}

void rasterize(Frame &frame, Triangle const &triangle, Program const &prg, bool backFaceCulling)
{

	// spočítat hranice, trojúhelníka
	//
	if (!backFaceCulling)
	{
		// pokud je vypnuty back face culling, zobrazují se i odvracene trojúhelníky
		// prohodí se, co je uvnitř a venku
	}
	for (;;) // smyčka přes pixely
		for (;;)
		{
			if (true) // pixel in triangle
			{
				InFragment inFragment;
				OutFragment outFragment;
				ShaderInterface si;
				prg.fragmentShader(outFragment, inFragment, si);
			}
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

void viewportTransformation(Triangle &triangle,uint32_t width, uint32_t height)
{
	for (int i = 0; i < 3; i++)
	{
		triangle.points[i].gl_Position.x += 1.f;
		triangle.points[i].gl_Position.y += 1.f;

		triangle.points[i].gl_Position.x /= 2.f;
		triangle.points[i].gl_Position.y /= 2.f;

		triangle.points[i].gl_Position.x *= width;
		triangle.points[i].gl_Position.y *= height;
	}
}

void draw(GPUMemory &mem, DrawCommand cmd, uint32_t draw_id)
{
	Program prg = mem.programs[cmd.programID];
	VertexShader vs = prg.vertexShader;

	for (uint32_t n = 0; n < cmd.nofVertices; ++n)
	{
		InVertex inVertex;
		OutVertex outVertex;

		VertexAssembly(mem, cmd.vao, inVertex, &n, &draw_id);

		ShaderInterface si;
		vs(outVertex, inVertex, si);
	}

	// for (uint32_t n = 0; n < cmd.nofVertices / 3; ++n)
	// { // smyčka přeš trojúhelníky
	// 	Triangle triangle;
	// 	TriangleAssembly(mem, triangle, prg, cmd.vao, n);

	// 	perspectiveDivision(triangle);

	// 	viewportTransformation(triangle, mem.framebuffer.width, mem.framebuffer.height);

	// 	rasterize(mem.framebuffer, triangle, prg, cmd.backfaceCulling);
	// }
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
	// auto t   = glm::fract(uv2);
	glm::vec4 color = glm::vec4(0.f, 0.f, 0.f, 1.f);
	for (uint32_t c = 0; c < texture.channels; ++c)
		color[c] = texture.data[(pix.y * texture.width + pix.x) * texture.channels + c] / 255.f;
	return color;
}
