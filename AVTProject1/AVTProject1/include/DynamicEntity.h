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

	class DynamicEntity : public Entity
	{

	protected:

	private:

	public:
		float velocity; //Velocidade moment�nea 
		float acceleration; //Acelera��o
		float deceleration; //Desacelara��o
		float maxVelocity;  // Velocidade maxima
		float minVelocity; // Velocidade para qual o algoritmo arredonda para 0
		float minDrag; // Forca minima de fricao
		float maxTurnRate; //Varia��o m�xima da dire��o
		glm::vec3 movementOrientation;

		DynamicEntity();
		DynamicEntity(SceneNode *node_, Shader *shader_, Mesh *mesh_, glm::vec3 startPos_, int maxVelocity_, int maxTurnRate_);
		void integrate(float accel_, float turnRate_, float delta_); //Update velocity and rotation
		void reset();
		int getRandomRate();
	};
}

