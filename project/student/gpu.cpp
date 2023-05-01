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
	uint32_t index = *shaderInvocation;

	switch (vao.indexType)
	{
	case IndexType::UINT32:
		uint32_t *ind_32;
		ind_32 = (uint32_t *)(mem.buffers[vao.indexBufferID].data) + (vao.indexOffset / sizeof(uint32_t));
		inVertex.gl_VertexID = ind_32[index];
		break;

	case IndexType::UINT16:
		uint16_t *ind_16;
		ind_16 = (uint16_t *)(mem.buffers[vao.indexBufferID].data) + (vao.indexOffset / sizeof(uint16_t));
		inVertex.gl_VertexID = ind_16[index];
		break;

	case IndexType::UINT8:
		uint8_t *ind_8;
		ind_8 = (uint8_t *)(mem.buffers[vao.indexBufferID].data) + (vao.indexOffset / sizeof(uint8_t));
		inVertex.gl_VertexID = ind_8[index];
		break;

	default:
		break;
	}
}

void getAttr(GPUMemory &mem, VertexAttrib *vertexAttrib, InVertex &inVertex)
{
	for (uint32_t i = 0; i < maxAttributes; i++)
	{
		if (vertexAttrib[i].type == AttributeType::EMPTY)
			continue;

		uint8_t *IndexBuffer = (uint8_t *)(mem.buffers[vertexAttrib[i].bufferID].data);

		uint8_t offset = (vertexAttrib[i].offset / sizeof(uint8_t));
		uint8_t stride = (vertexAttrib[i].stride / sizeof(uint8_t));

		uint8_t *attr_buffer = (IndexBuffer + offset + (stride * inVertex.gl_VertexID));

		switch (vertexAttrib[i].type)
		{
		case AttributeType::FLOAT:
			inVertex.attributes[i].v1 = *(float *)attr_buffer;
			break;

		case AttributeType::VEC2:
			inVertex.attributes[i].v2 = *(glm::vec2 *)attr_buffer;
			break;

		case AttributeType::VEC3:
			inVertex.attributes[i].v3 = *(glm::vec3 *)attr_buffer;
			break;

		case AttributeType::VEC4:
			inVertex.attributes[i].v4 = *(glm::vec4 *)attr_buffer;
			break;

		case AttributeType::UINT:
			inVertex.attributes[i].u1 = *(uint32_t *)attr_buffer;
			break;

		case AttributeType::UVEC2:
			inVertex.attributes[i].u2 = *(glm::uvec2 *)attr_buffer;
			break;

		case AttributeType::UVEC3:
			inVertex.attributes[i].u3 = *(glm::uvec3 *)attr_buffer;
			break;

		case AttributeType::UVEC4:
			inVertex.attributes[i].u4 = *(glm::uvec4 *)attr_buffer;
			break;
		}
	}
}

void runVertexAssembly(GPUMemory &mem, VertexArray &vao, InVertex &inVertex, uint32_t *shaderInvocation, uint32_t *draw_id)
{
	inVertex.gl_DrawID = *draw_id;

	computeVertexID(mem, vao, shaderInvocation, inVertex);
	getAttr(mem, vao.vertexAttrib, inVertex);
}

// void runPrimitiveAssembly(primitive, VertexArray vao, t, Program prg)
// {
// 	for (every vertex v in triangle)
// 	{
// 		InVertex inVertex;
// 		runVertexAssembly(inVertex, vao, t + v);
// 		prg.vertexShader(primitive.vertex, inVertex, prg.uniforms);
// 	}
// }

// void rasterizeTriangle(frame, primitive, prg)
// {
// 	for (pixels in frame)
// 	{
// 		if (pixels in primitive)
// 		{
// 			InFragment inFragment;
// 			createFragment(inFragment, primitive, barycentrics, pixelCoord, prg);
// 			OutFragment outFragment;
// 			prg.fragmentShader(outFragment, inFragment, uniforms);
// 		}
// 	}
// }

void draw(GPUMemory &mem, DrawCommand cmd, uint32_t draw_id)
{
	VertexShader vs = mem.programs[cmd.programID].vertexShader;
	for (uint32_t n = 0; n < cmd.nofVertices; ++n)
	{
		InVertex inVertex;
		OutVertex outVertex;

		runVertexAssembly(mem, cmd.vao, inVertex, &n, &draw_id);

		ShaderInterface si;
		vs(outVertex, inVertex, si);
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
	// auto t   = glm::fract(uv2);
	glm::vec4 color = glm::vec4(0.f, 0.f, 0.f, 1.f);
	for (uint32_t c = 0; c < texture.channels; ++c)
		color[c] = texture.data[(pix.y * texture.width + pix.x) * texture.channels + c] / 255.f;
	return color;
}
