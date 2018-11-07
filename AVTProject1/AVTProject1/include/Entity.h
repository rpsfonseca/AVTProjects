#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Model.h"
#include "Constants.h"
//#include "Texture.h"
#include "node.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <math.h>
#include "AABB.h"


namespace AVTEngine
{
	class Car;

	struct EntityTexture
	{
		std::string key;
		//Texture *texture;
	};

	// Superclasse de todos os objectos que se movem
	class Entity
	{

	protected:
		Shader* shader;
		Mesh* mesh;
		Material* material; 
		SceneNode* node;
		//Model *model;
		glm::mat4 resultMatrix;


	private:
		
		std::vector<EntityTexture> textureArray;


	public:

		Entity(SceneNode *node_, Shader *shader_, Mesh *mesh_);
		Entity(Shader *shader_, Mesh *mesh_, float maxVelocity_, float maxTurnRate_, glm::vec3 orientation_);
		Entity();

		//TODO teste
		Entity(SceneNode *node_); //Dynamic Entity

		glm::mat4 ModelViewMatrix = glm::mat4(1.0); //Identity Matrix
		glm::vec3 position;
		glm::vec3 orientation;
		glm::vec3 movementOrientation;

		
		
		
		float rotationAccum;
		bool enabled = false; // Se o objecto deve detectar colis�es ou n�o
		
		/* Possibly needed variables
			int id
			string name
			quaternion de rota�ao
			vec3 scale
			boolean visible
		*/

		//Methods
		void disable(); 
		void enable();
		bool isDisabled();
		glm::vec3 getOrientation();
		glm::vec3 getPosition();
		void setPosition(glm::vec3 position_);
		void rotate(float angle_);
		void orangeRotate(float angle_, glm::vec3 axis_);
		void setMesh(Mesh* mesh_);
		void setMaterial(Material* material_);
		virtual void update(float delta_);
		virtual AABB getBoundingBox() {
			return AABB(99999999.f, 99999999.f, 99999999.f, 99999999.f, 99999999.f, 99999999.f);
		}
		virtual bool handleCarCollision(Car* car) { return false; } // returns whether collision makes player stop
	};
}

