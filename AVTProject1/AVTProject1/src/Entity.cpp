#include "Entity.h"

namespace AVTEngine
{
	Entity::Entity() {}

	Entity::Entity(SceneNode *node_, Shader *shader_, Mesh *mesh_):
		node(node_), shader(shader_), mesh(mesh_){
	}

	Entity::Entity(Shader *shader_, Mesh *mesh_, float maxVelocity_, float maxTurnRate_, glm::vec3 orientation_){
		enabled = true;
		rotationAccum = 0;
		orientation = orientation_;
	};

	//TODO teste
	Entity::Entity(SceneNode *node_) : 
		node(node_) {
		enabled = true;
		rotationAccum = 0;
	};

	void Entity::disable() {
		enabled = false;
	};

	void Entity::enable() {
		enabled = true;
	};

	//Uma entidade disabled nao "existe" no mapa, ou seja, nao sofre colisoes e nao e atualizada (apesar de ainda poder aparecer)
	bool Entity::isDisabled() {
		return !enabled;
	}

	glm::vec3 Entity::getOrientation() {
		return orientation;
	}

	glm::vec3 Entity::getPosition() {
		return position;
	}

	void Entity::setPosition(glm::vec3 position_) {
		position = position_;
		node->setPosition(position_); //Tell node to change position
	}


	//Aplicar rotaçao na matriz do modelo
	/* 
	void Entity::rotate(float angle_) {
		rotationAccum += angle_;
		glm::vec3 y_axis = Y_AXIS;

		//Rotate model
		ModelViewMatrix = glm::rotate(ModelViewMatrix, angle_, y_axis);
		orientation = glm::rotateY(orientation, angle_);
	}
	*/
	void Entity::rotate(float angle_) {

		rotationAccum += angle_;
		glm::vec3 y_axis = Y_AXIS;

		//Rotate model
		glm::quat quaternion = glm::angleAxis(rotationAccum, y_axis);
		node->setRotation(quaternion);
		
		//Also update orientation, for movement calculation purposes
		orientation = glm::rotateY(orientation, angle_);
	}

	void Entity::orangeRotate(float angle_, glm::vec3 axis_) {

		rotationAccum += angle_;

		//Rotate model
		glm::quat quaternion = glm::angleAxis(rotationAccum, axis_);
		node->setRotation(quaternion);

		//Also update orientation, for movement calculation purposes
		orientation = glm::rotateY(orientation, angle_);
	}

	void Entity::setMesh(Mesh* mesh_) {
		mesh = mesh_;
	}

	void Entity::setMaterial(Material* material_) {
		material = material_;
	}

	void Entity::update(float delta_)
	{
		//Empty
	}//Virtual

}
