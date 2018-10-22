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

		//this.rotate(rotation);
		//SceneNode.add(this); Adicionar o carro à cena?
	};

	/* Stuff for collision detection

	get type() {   //Para saber que tipo de colisão se trata
		return TYPE.CAR;
	}

	getBoundingVolume() { //Raio da caixa para colisao
		return new Circle(this.getPosition(), 5.5);
	}
	*/

	void Car::reset() {
		Entity::reset();

		// roda no sentido contrario da soma de todas as rotacoes, ou seja, volta ao inicial
		//this.rotate(-this.rotationAccum);

		position = initialPos;
	}

	void Car::update(float delta_) { //
		float turnRate = 0;

		/* Turn inputs			input.isKeyPressed para verificar o array keys[keycode], e dar o keyCode correspondente, que deve vir do constants.h
		if (keyboard.isKeyPressed(TECLA_VIRAR_ESQUERDA)) {
			turnRate = maxTurnRate;
		}
		else if (keyboard.isKeyPressed(TECLA_VIRAR_DIREITA)) {
			turnRate = -maxTurnRate;
		}
		*/

		
		float accel = 0;
		/* Speed input
		if (keyboard.isKeyPressed(TECLA_ACELERAR)) {
			accel = acceleration;
		}
		else if (keyboard.isKeyPressed(TECLA_DESACELERAR)) {
			accel = -deceleration;
		}

		if (keyboard.isKeyPressed(TECLA_H)) { //Turn lights on or off
			keyboard.unpressKey(TECLA_H);
			this.spotLight1.intensity = 1 - this.spotLight1.intensity;
			this.spotLight2.intensity = 1 - this.spotLight2.intensity;
		}
		*/

		//Update
		Entity::integrate(accel, turnRate, delta_);
	}

}
