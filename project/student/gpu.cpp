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
		for (int i = 0 ; i+4 < (mem.framebuffer.height * mem.framebuffer.width) ; i+=4 )
		{
			mem.framebuffer.color[i] = (uint8_t)(cmd.color.r * 255.f);
			mem.framebuffer.color[i+1] = (uint8_t)(cmd.color.g * 255.f);
			mem.framebuffer.color[i+2] = (uint8_t)(cmd.color.b * 255.f);
			mem.framebuffer.color[i+3] = (uint8_t)(cmd.color.a * 255.f);
		}
	}
	if(cmd.clearDepth)
	{
		for (int i = 0; i < (mem.framebuffer.height * mem.framebuffer.width); i++)
		{
			mem.framebuffer.depth[i] = (cmd.depth);
		}
	}
}

void runVertexAssembly(InVertex in, VertexArray vao, VertexShader vs)
{
	// computeVertexID();
	// readAttributes();
}

void draw(GPUMemory&mem,DrawCommand cmd, uint32_t draw_id)
{
	VertexShader vs = mem.programs[cmd.programID].vertexShader;
	for (uint32_t n = 0; n < cmd.nofVertices; ++n)
	{
		InVertex inVertex;
		OutVertex outVertex;
		inVertex.gl_VertexID = n;
		inVertex.gl_DrawID = draw_id;
		runVertexAssembly(inVertex, cmd.vao, vs);
		ShaderInterface si;
		vs(outVertex, inVertex, si);
	}

}

  //! [gpu_execute]
	void gpu_execute(GPUMemory & mem, CommandBuffer & cb)
	{
		uint32_t draw_id_gpu = 0;
		for (uint32_t i = 0 ; i < cb.nofCommands; ++i)
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
