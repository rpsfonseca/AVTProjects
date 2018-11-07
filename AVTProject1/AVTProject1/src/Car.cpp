#include "Car.h"
#include "Entity.h"
#include "scene.h"
#include <utility>


namespace AVTEngine
{

	//TODO teste
	Car::Car(SceneNode *node_, glm::vec3 startPos_, float rotation_) : DynamicEntity(node_, startPos_, CAR_MAX_VELOCITY, CAR_MAX_TURNRATE) {

		acceleration = 20;
		deceleration = 10;
		initialPos = startPos_;

		minVelocity = 0.1; // Velocidade para qual o algoritmo arredonda para 0

		rotate(rotation_);
	};


	/* TODO Stuff for collision detection

	get type() {   //Para saber que tipo de colisão se trata
		return TYPE.CAR;
	}

	getBoundingVolume() { //Raio da caixa para colisao
		return new Circle(this.getPosition(), 5.5);
	}
	*/

	void Car::reset() {
		DynamicEntity::reset();

		this->rotate(-rotationAccum); // roda no sentido contrario da soma de todas as rotacoes, ou seja, volta ao inicial
		setPosition(initialPos); //Voltar à posição inicial do carro
	}

	void Car::update(float delta_) { //
		float turnRate = 0;

		/* Turn inputs */
		if (Input::isKeyDown('o')) { //seta esquerda
			turnRate = maxTurnRate;
		}
		else if (Input::isKeyDown('p')) { //seta direita
			turnRate = -maxTurnRate;
		}

		float accel = 0;

		/* Speed input */
		if (Input::isKeyDown('q')) { //seta acima
			accel = acceleration;
			//printf();
		}
		else if (Input::isKeyDown('a')) { //seta abaixo
			accel = -deceleration;
		}

		//Update
		auto oldPos = getPosition();
		DynamicEntity::integrate(accel, turnRate, delta_);

		// check collisions
		auto myAABB = getBoundingBox();

		for (std::map<std::string, Entity*>::iterator it = Application::getInstance()->scene->entities.begin();
			it != Application::getInstance()->scene->entities.end();
			++it)
		{
			if (myAABB.collidesWith(it->second->getBoundingBox())) {
				if (it->second->handleCarCollision(this)) {
					// undo movement and stop moving
					setPosition(oldPos);
					velocity = 0;
				}
			}
		}
	}

	AABB Car::getBoundingBox() {
		return AABB(
			position.x - 3.f,
			position.x + 3.f,
			position.y,
			position.y + 3.f,
			position.z - 3.f,
			position.z + 3.f
			);
	}
}
