#include "Orange.h"


namespace AVTEngine
{

	Orange::Orange(SceneNode *node_, Shader *shader_, Mesh *mesh_, float levelWidth_, float levelHeight_) :
		node(node_) {

		Entity::Entity(shader_, mesh_, 100, 3, glm::vec3(1, 0, 0));

		velocity = getRandomRate() * 10; //TODO fix getRandomRate in entity class

		//Margin for when orange exits table

		float change = ORANGE_DEFAULT_RADIUS + 0.1; //Work around
		levelWidth = levelWidth_ - 2 * change;
		levelHeight = levelHeight_ - 2 * change;

		//Get a random position and direction
		glm::vec3 pos = getRandomPosition();
		glm::vec3 tempMovOrientation = getDirection(pos);
		orientation = tempMovOrientation;
		movementOrientation = tempMovOrientation;

		increaseSpeedTimer = TEMPO_ACELERAR_LARANJAS;
		respawnTimer = 0;
		dead = false;

		
		//Node.add(this); Adicionar o carro à cena?

		position = pos;
		//position.setY(ORANGE_DEFAULT_RADIUS); //Set minimum height, so the orange isn't inside the table

		//name = "orange"; Not needed?
							
	};
	
	
	void Orange::update(float delta) {
		increaseSpeedTimer -= delta;

        if(increaseSpeedTimer < 0){
            increaseSpeedTimer = TEMPO_ACELERAR_LARANJAS - increaseSpeedTimer; // 
            
            //velocity += (Math.floor(Math.random() * 2) + 1) * 5; //TODO passar de JS para C++
        }

        if(dead){
            respawnTimer -= delta;
            if(respawnTimer < 0){
                dead = false;
                visible = true;
            } else {
                return;
            }
        }

        orangeMovement(delta);
	}
	

	void Orange::orangeMovement(float delta) {
		glm::vec3 temp = movementOrientation;
		//glm::vec3 velocityVector = temp.multiplyScalar(velocity*delta);
		//position += velocityVector;

		// calcula quanto temos de rodar para coincidir com a velocidade atual
		float turnRateTemp = (velocity*delta) / ORANGE_DEFAULT_RADIUS;
		orangeRotation(turnRateTemp);
	}

	void Orange::orangeRotation(float turnRate) {
		rotationAccum += turnRate;
		glm::vec3 temp = movementOrientation;
		/*
		temp.normalize();
		temp.applyAxisAngle(new THREE.Vector3(0, 1, 0), 90 * (Math.PI / 180)); //Rodar o vector para obter um eixo de rotacao adequado ao movimento
		this.object.rotateOnAxis(temp, turnRate); //rotateOnAxis( Axis, Angle)   //angle em radianos		
		*/		
	}

	glm::vec3 Orange::getDirection(glm::vec3 pos) {
		/*
		var direction = pos.clone().multiplyScalar(-1);
		direction.setY(0);
		direction = direction.normalize()

			direction.applyAxisAngle(yAxis, (Math.random() * MAX_ORANGE_RANDOM_ANGLE * 2) - MAX_ORANGE_RANDOM_ANGLE)
			return direction;
		*/
		return glm::vec3(0); //Temp
	}

	glm::vec3 Orange::getRandomPosition() {
		/*
		var side1 = Math.random() < 0.5;
		var side2 = Math.random() < 0.5;

		var x;
		var z;

		if (side1) { // Começa ou no topo ou em baixo
			z = (side2 ? this.levelHeight : -this.levelHeight) / 2;
			x = ((Math.random() * this.levelWidth * 2) - this.levelWidth) / 2;
		}
		else { // Começa a esquerda ou a direita
			x = (side2 ? this.levelWidth : -this.levelWidth) / 2;
			z = ((Math.random() * this.levelHeight * 2) - this.levelHeight) / 2;
		}

		return new THREE.Vector3(x, 0, z);
		*/
		return glm::vec3(0); //Temp
	}

	void Orange::setOrientation(glm::vec3 orientation_) {
		movementOrientation = orientation_;
	}

	/* Stuff for collision detection
	get type() {   //Para saber que tipo de colisão se trata
	return TYPE.ORANGE;
	}

	getBoundingVolume(){ //Raio da caixa para colisao
        return new Circle(this.getPosition(),ORANGE_DEFAULT_RADIUS);
    }
	*/

	void Orange::reset() {
		Entity::reset();

		position = initialPos;
		orangeRotation(-rotationAccum); // roda no sentido contrario da soma de todas as rotacoes, ou seja, volta ao inicial

		velocity = getRandomRate() * 10;
		setPosition(getRandomPosition());
		//position.setY(ORANGE_DEFAULT_RADIUS);
		setOrientation(getDirection(getPosition()));
		increaseSpeedTimer = TEMPO_ACELERAR_LARANJAS;
	}

	void Orange::kill() {
		orangeRotation(-rotationAccum);
		setPosition(getRandomPosition());
		//position.setY(ORANGE_DEFAULT_RADIUS);
		setOrientation(getDirection(getPosition()));
		dead = true;
		visible = false;
		respawnTimer = TEMPO_REAPARECER_LARANJAS;
	}

}
