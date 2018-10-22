#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Constants.h"
#include "Entity.h"
#include "node.h"
//#include "Texture.h"
#include <glm/glm.hpp>

namespace AVTEngine
{

	class Car: Entity
	{

	protected:
		SceneNode *node;

	private:


	public:

		Car(SceneNode *node_, Shader *shader_, Mesh *mesh_, glm::vec3 startPos_, float rotation_);
		Car() = default;

		glm::vec3 initialPos;
		/*
		Light spotlight1;
		Light spotlight2;
		*/

		void reset();
		void update(float delta);

	};
}

