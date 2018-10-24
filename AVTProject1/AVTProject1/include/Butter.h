#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Constants.h"
#include "DynamicEntity.h"
//#include "Texture.h"
#include "Input.h"
#include <glm/glm.hpp>

namespace AVTEngine
{

	class Butter : public DynamicEntity
	{

	protected:


	private:


	public:

		Butter(SceneNode *node_, glm::vec3 startPos_);
		void update(float delta);

	};
}

