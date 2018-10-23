#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Constants.h"
#include "Entity.h"
#include "node.h"
//#include "Texture.h"
#include "Input.h"
#include <glm/glm.hpp>

namespace AVTEngine
{

	class StaticEntity : Entity
	{

	protected:

	private:

	public:
		StaticEntity();
		StaticEntity(SceneNode *node_, Shader *shader_, Mesh *mesh_, glm::vec3 startPos_);
	};
}

