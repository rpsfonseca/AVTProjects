#include "Car.h"


namespace AVTEngine
{

	Car::Car(SceneNode *node_, Shader *shader_, Mesh *mesh_, glm::vec3 startPos_, float rotation_) :
		node(node_){

		Entity::Entity(shader_, mesh_, 100, 3, glm::vec3(1, 0, 0));
		
		acceleration = 20;
		deceleration = 10;
		maxTurnRate = CAR_MAX_TURNRATE;
		position = startPos_;
		initialPos = startPos_;

		minVelocity = 0.1; // Velocidade para qual o algoritmo arredonda para 0
		minDrag = MIN_DRAG; // Forca minima de fricao

		rotate(rotation_);
		//TODO SceneNode.add(this); Adicionar o carro à cena?
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
		Entity::reset();

		rotate(-rotationAccum); // roda no sentido contrario da soma de todas as rotacoes, ou seja, volta ao inicial
		position = initialPos;
	}

	void Car::update(float delta_) { //
		float turnRate = 0;

		/* Turn inputs */
		if (Input::isKeyDown(37)) { //seta esquerda
			turnRate = maxTurnRate;
		}
		else if (Input::isKeyDown(39)) { //seta direita
			turnRate = -maxTurnRate;
		}
		
		float accel = 0;

		/* Speed input */
		if (Input::isKeyDown(38)) { //seta acima
			accel = acceleration;
		}
		else if (Input::isKeyDown(40)) { //seta abaixo
			accel = -deceleration;
		}

		/* TODO Lights input */
		if (Input::isKeyDown(72)) { //tecla H //Turn lights on or off
			/*
			keyboard.unpressKey(TECLA_H);
			this.spotLight1.intensity = 1 - this.spotLight1.intensity;
			this.spotLight2.intensity = 1 - this.spotLight2.intensity;
			*/
		}
		
		//Update
		Entity::integrate(accel, turnRate, delta_);
	}

}
