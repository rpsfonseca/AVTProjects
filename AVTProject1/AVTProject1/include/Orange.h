#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Constants.h"
#include "DynamicEntity.h"
//#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace AVTEngine
{

	class Orange: public DynamicEntity {

	protected:

	private:


	public:

		Orange(SceneNode *node_, Shader *shader_, Mesh *mesh_, float levelWidth_, float levelHeight_);
		Orange() = default;

		glm::vec3 initialPos;

		float levelWidth;
		float levelHeight;

		/*
		Light spotlight1;
		Light spotlight2;
		*/

		float increaseSpeedTimer;
		float respawnTimer;
		bool dead;
		bool visible; //If it should be rendered or not
		//char name;

		//Methods
		void update(float delta);
		void orangeMovement(float delta);
		void orangeRotation(float turnRate);
		glm::vec3 getDirection(glm::vec3 pos);
		glm::vec3 getRandomPosition();
		void setOrientation(glm::vec3 orientation_);

		//void getType()
		//void getBoundingVolume();
		void reset();
		void kill();

	};
}

