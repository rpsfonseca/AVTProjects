#include "Entity.h"


namespace AVTEngine
{

	Entity::Entity(Shader *shader_, Mesh *mesh_, float maxVelocity_, float maxTurnRate_, glm::vec3 orientation_) :
		shader(shader_), mesh(mesh_), maxVelocity(maxVelocity_), maxTurnRate(maxTurnRate_), orientation(orientation_), movementOrientation(orientation_){
		
		velocity = 0;	// Velocidade inicial
		minVelocity = 0.1; // Velocidade para qual o algoritmo arredonda para 0
		enabled = true;
		rotationAccum = 0;
	};


	void Entity::integrate(float accel_, float turnRate_, float delta_) { //Delta makes it fps independent
		
		//Calculate rotation
		rotate((turnRate_ * delta_ * (velocity / maxVelocity) ));
		
		//Calculate Speed
		velocity += accel_ * delta_; 
		if (isMoving()) {
			velocity *= 0.995;	// Aplica forca de atrito para desacelarar 
		}

		if (abs(velocity) < abs(minVelocity)) { //Forces car to stop
			velocity = 0;
		}
		if (abs(velocity) > abs(maxVelocity)) { //Limits velocity, independent of foward or backwards movement
			velocity = maxVelocity;
		}

		//Calculo da alteraçao da posição consoante a velocidade
		//É preciso pegar no vector de orientaçao, multiplica-lo pela velocidade actual, e adicionar o resultado à posição actual do carro
		glm::vec3 ori = orientation;
		glm::vec3 velocityVector = ori * (velocity * delta_);
		position += velocityVector;
	}

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

	bool Entity::isMoving() {
		return abs(velocity) > minVelocity;
	}

	glm::vec3 Entity::getOrientation() {
		return orientation;
	}

	glm::vec3 Entity::getPosition() {
		return position;
	}

	void Entity::setPosition(glm::vec3 position_) {
		position = position_;
	}


	//Aplicar rotaçao na matriz do modelo
	void Entity::rotate(float angle_) {
		rotationAccum += angle_;
		glm::vec3 y_axis = Y_AXIS;

		//Rotate model
		ModelViewMatrix = glm::rotate(ModelViewMatrix, angle_, y_axis);
		orientation = glm::rotateY(orientation, angle_);
	}

	void Entity::reset() {
		//acceleration = 0;
		velocity = 0;
	}

	int Entity::getRandomRate() {
		int min = 1;
		int max = 5;
		int randNum = rand()%(max-min + 1) + min; 
		return randNum;
	}
}
