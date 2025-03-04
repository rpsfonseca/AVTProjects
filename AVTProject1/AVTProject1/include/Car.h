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

	class Car: public DynamicEntity
	{

	protected:


	private:


	public:

		Car(SceneNode *node_, glm::vec3 startPos_, float rotation_);
		Car() = default;
	
		glm::vec3 initialPos;

		void reset();
		void update(float delta);

		AABB getBoundingBox() override;

	};
}

