#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Model.h"
#include "Constants.h"
//#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <math.h>

#include "node.h"

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
		SceneNode *node;
		//Model *model;
		glm::mat4 resultMatrix;


	private:
		
		std::vector<EntityTexture> textureArray;


	public:

		Entity::Entity(SceneNode *node_, Shader *shader_, Mesh *mesh_);
		Entity(Shader *shader_, Mesh *mesh_, float maxVelocity_, float maxTurnRate_, glm::vec3 orientation_);
		Entity() = default;

		glm::mat4 ModelViewMatrix = glm::mat4(1.0); //Identity Matrix
		glm::vec3 position;
		glm::vec3 orientation;
		glm::vec3 movementOrientation;

		
		
		
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
		void disable(); 
		void enable();
		bool isDisabled();
		bool isMoving();
		glm::vec3 getOrientation();
		glm::vec3 getPosition();
		void setPosition(glm::vec3 position_);
		void rotate(float angle_);
		void setMesh(Mesh* mesh_);
		void setMaterial(Material* material_);
	};
}

