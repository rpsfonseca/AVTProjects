#include "DynamicEntity.h"


namespace AVTEngine
{
	DynamicEntity::DynamicEntity() {
	};

	DynamicEntity::DynamicEntity(SceneNode *node_, Shader *shader_, Mesh *mesh_, glm::vec3 startPos_, int maxVelocity_, int maxTurnRate_) : 
		maxVelocity(maxVelocity_), maxTurnRate(maxTurnRate_) {

		Entity::Entity(shader_, mesh_, 100, 3, glm::vec3(1, 0, 0));
		setPosition(startPos_);
		orientation = glm::vec3(1, 0, 0);
		maxTurnRate = maxTurnRate_;

		velocity = 0;	// Velocidade inicial
		minVelocity = 0.1; // Velocidade para qual o algoritmo arredonda para 0
	};


	void DynamicEntity::integrate(float accel_, float turnRate_, float delta_) { //Delta makes it fps independent

		//Calculate rotation
		rotate((turnRate_ * delta_ * (velocity / maxVelocity)));

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

	void DynamicEntity::reset() {
		velocity = 0;
	}

	int DynamicEntity::getRandomRate() {
		int min = 1;
		int max = 5;
		int randNum = rand() % (max - min + 1) + min;
		return randNum;
	}

}
