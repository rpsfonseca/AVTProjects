#include "CommandBuffer.h"

namespace AVTEngine
{
	CommandBuffer::CommandBuffer(Renderer* _renderer)
		: renderer(_renderer)
	{
	}

	CommandBuffer::~CommandBuffer()
	{
	}

	void CommandBuffer::pushCommand(Mesh* mesh, Material* material, glm::mat4 transform)
	{
		RenderCommand command;
		command.mesh = mesh;
		command.material = material;
		command.transform = transform;

		renderCommands.push_back(command);
	}

	void CommandBuffer::clear()
	{
		renderCommands.clear();
	}

	std::vector<RenderCommand> CommandBuffer::getRenderCommands()
	{
		return renderCommands;
	}
}