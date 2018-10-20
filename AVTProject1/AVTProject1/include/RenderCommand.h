#pragma once

#include <glm/glm.hpp>

namespace AVTEngine
{
	class Mesh;
	class Material;

	struct RenderCommand
	{
		glm::mat4 transform;
		glm::mat4 previousTransform;
		Mesh*      mesh;
		Material*  material;
	};
}