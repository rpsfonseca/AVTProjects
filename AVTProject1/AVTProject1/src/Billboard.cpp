#include "Billboard.h"

#include "Mesh.h"
#include "ResourcesManager.h"

namespace AVTEngine
{
	Billboard::Billboard()
	{
		std::vector<glm::vec3> vertices = {
			glm::vec3(-0.5f, -0.5f, 0.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),
			glm::vec3(-0.5f, 0.5f, 0.0f),
			glm::vec3(0.5f, 0.5f, 0.0f)
		};
		
		mesh = ResourcesManager::loadOBJ("quad");
	}

	Billboard::~Billboard()
	{
	}
}