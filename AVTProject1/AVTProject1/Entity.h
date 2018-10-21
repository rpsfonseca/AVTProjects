#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Constants.h"
//#include "Texture.h"
#include <glm/glm.hpp>

namespace AVTEngine
{

	struct EntityTexture
	{
		std::string key;
		//Texture *texture;
	};

	// Superclasse de todos os objectos que se movem
	class Entity {

	protected:
		Shader *shader;
		Mesh *mesh;
		Material *material; 
		glm::mat4 resultMatrix;


	private:
		glm::mat4 ModelViewMatrix = glm::mat4(1.0); //Identity Matrix
		std::vector<EntityTexture> textureArray;


	public:

		Entity(Shader *shader_, Mesh *mesh_, float maxVelocity_, float orientation_);
		Entity() = default;

		glm::vec3 position = glm::vec3(0, 0, 0);

		float velocity; //Velocidade momentânea 
		float accel; //Aceleração
		float maxVelocity;  // Velocidade maxima
		float minVelocity; // Velocidade para qual o algoritmo arredonda para 0
		float minDrag; // Forca minima de fricao
		float maxTurnRate; //Variação máxima da direção
		float orientation;
		float movementOrientation;
		float rotationAccum;
		bool enabled = false; // Se o objecto deve detectar colisões ou não
		
		/* Possibly needed variables
			int id
			string name
			quaternion de rotaçao
			vec3 scale
			boolean visible
		*/

		//Methods
		void integrate(float accel_, float turnRate_, float delta_); //Update velocity and rotation
		void disable(); 
		void enable();
		bool isDisabled();
		bool isMoving();
		float getOrientation();
		glm::vec3 getPosition();
		void setPosition(glm::vec3 position_);
		void rotate(float angle_);
		void reset();
		int getRandomRate();

	};
}






