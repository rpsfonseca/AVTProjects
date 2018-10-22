#pragma once

#include "RenderCommand.h"

#include <vector>

namespace AVTEngine
{
	class Renderer;
	class Mesh;
	class Material;

	class CommandBuffer
	{
	private:
		Renderer* renderer;

		std::vector<RenderCommand> renderCommands;

	public:
		CommandBuffer(Renderer* _renderer);
		~CommandBuffer();

		// pushes render state relevant to a single render call to the command buffer.
		void pushCommand(Mesh* mesh, Material* material, glm::mat4 transform = glm::mat4());

		// clears the command buffer; usually done after issuing all the stored render commands.
		void clear();

		// returns the list of render commands. For minimizing state changes it is advised to first 
		std::vector<RenderCommand> getRenderCommands();

	private:

	};
}