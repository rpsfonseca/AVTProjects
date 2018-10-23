#include "Car.h"


namespace AVTEngine
{

	Car::Car(SceneNode *node_, Shader *shader_, Mesh *mesh_, glm::vec3 startPos_, float rotation_){

		DynamicEntity::DynamicEntity(node_, shader_, mesh_, glm::vec3(1, 0, 0), CAR_MAX_VELOCITY, CAR_MAX_TURNRATE);

		
		acceleration = 20;
		deceleration = 10;
		initialPos = startPos_;

		minVelocity = 0.1; // Velocidade para qual o algoritmo arredonda para 0
		minDrag = MIN_DRAG; // Forca minima de fricao

		rotate(rotation_);
		//TODO SceneNode.add(this); Adicionar o carro à cena?
	};

	//TODO teste
	Car::Car(SceneNode *node_, glm::vec3 startPos_, float rotation_) : DynamicEntity(node_, glm::vec3(1, 0, 0), CAR_MAX_VELOCITY, CAR_MAX_TURNRATE) {

		acceleration = 20;
		deceleration = 10;
		initialPos = startPos_;

		minVelocity = 0.1; // Velocidade para qual o algoritmo arredonda para 0
		minDrag = MIN_DRAG; // Forca minima de fricao

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
		if (Input::isKeyDown('a')) { //seta esquerda
			turnRate = maxTurnRate;
			printf("tecla A");
		}
		else if (Input::isKeyDown('d')) { //seta direita
			turnRate = -maxTurnRate;
		}
		
		float accel = 0;

		/* Speed input */
		if (Input::isKeyDown('w')) { //seta acima
			accel = acceleration;
			//printf();
		}
		else if (Input::isKeyDown('s')) { //seta abaixo
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
		DynamicEntity::integrate(accel, turnRate, delta_);
	}

}
