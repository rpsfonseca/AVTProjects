#include "Orange.h"
#include "Car.h"
#include "Application.h"


namespace AVTEngine
{

	Orange::Orange(SceneNode *node_, float levelWidth_, float levelHeight_) : DynamicEntity(node_, ORANGE_MAX_VELOCITY, ORANGE_MAX_TURNRATE) {

		velocity = getRandomRate() * 10; //Oranges shouldn't all behave the same

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

		position = pos;
		setPosition(pos);
		position.y = ORANGE_DEFAULT_RADIUS; //Set minimum height, so the orange isn't inside the table
	};
	
	
	void Orange::update(float delta_) {
		increaseSpeedTimer -= delta_;

        if(increaseSpeedTimer < 0){
            increaseSpeedTimer = TEMPO_ACELERAR_LARANJAS - increaseSpeedTimer; // 
		
			//int randNum = rand() % (2 - 1 + 1) + 1; //int randNum = rand()%(max-min + 1) + min; //Random velocity increase (5 or 10)
			velocity += 10; 
        }

        if(dead){
            respawnTimer -= delta_;
            if(respawnTimer < 0){
                dead = false;
                visible = true;
            } else {
                return;
            }
        }

        orangeMovement(delta_);
	}
	

	void Orange::orangeMovement(float delta_) {
		glm::vec3 temp = movementOrientation;
		glm::vec3 velocityVector = temp * (velocity * delta_); //Calculate the speed vector
		position += velocityVector; //Add the speed vector to the current position
		setPosition(position); //Update node position

		// calcula quanto temos de rodar para coincidir com a velocidade atual
		float turnRateTemp = (velocity*delta_) / ORANGE_DEFAULT_RADIUS;
		orangeRotation(turnRateTemp);
	}

	void Orange::orangeRotation(float turnRate_) {
		rotationAccum += turnRate_;
		glm::vec3 temp = movementOrientation;
		
		glm::vec3 normalized = glm::normalize(temp);
		float rot = 90 * (M_PI / 180);

		normalized = glm::rotateY(normalized, rot); //Rodar o vector para obter um eixo de rotacao adequado ao movimento

		Entity::orangeRotate(turnRate_, normalized); ////Tells the Entity class to tell the Node class that the node needs to update
		/*
		ModelViewMatrix = glm::rotate(ModelViewMatrix, turnRate_ , normalized); //Rotate the model by the right amount, and considering the current axis
		*/
	}

	glm::vec3 Orange::getDirection(glm::vec3 pos_) {

		glm::vec3 direction = pos_ * float(-1); //Direcção é oposta à posição inicial, de modo a percorrer a mesa e evitar que saia logo
		direction.y = 0; //Não há movimento vertical

		direction = normalize(direction);
		int temp = MAX_ORANGE_RANDOM_ANGLE;
		float rotAngle = rand() % (temp*2 - temp + 1) + temp; //int randNum = rand()%(max-min + 1) + min;
		direction = rotateY(direction, rotAngle); //Dar direcção aleatória

		return direction;
	}

	glm::vec3 Orange::getRandomPosition() { //gera posicao para a laranja fazer spawn

		bool side1 = rand() < 0.5;
		bool side2 = rand() < 0.5;

		int lw = levelWidth;
		int lh = levelHeight;

		float x;
		float z;
		
		if (side1) { 
			z = (side2 ? levelHeight : -levelHeight) / 2; // Começa ou no topo ou em baixo
			//x = ((Math.random() * this.levelWidth * 2) - this.levelWidth) / 2;
			////int randNum = rand()%(max-min + 1) + min;
			//x = ((rand() * levelWidth * 2) - levelWidth) / 2;
			x = rand() % (lw - (-lw) + 1) + lw;
		}
		else { 
			x = (side2 ? levelWidth : -levelWidth) / 2; // Começa a esquerda ou a direita
			//z = ((Math.random() * this.levelHeight * 2) - this.levelHeight) / 2;
			//z = ((rand() * levelHeight * 2) - levelHeight) / 2;
			z = rand() % (lh - (-lh) + 1) + lh;
		}

		return glm::vec3(x, 0, z);
	}

	void Orange::setOrientation(glm::vec3 orientation_) {
		movementOrientation = orientation_;
	}

	/* TODO Stuff for collision detection
	get type() {   //Para saber que tipo de colisão se trata
	return TYPE.ORANGE;
	}

	getBoundingVolume(){ //Raio da caixa para colisao
        return new Circle(this.getPosition(),ORANGE_DEFAULT_RADIUS);
    }
	*/

	void Orange::reset() {
		DynamicEntity::reset();

		position = initialPos;
		//orangeRotation(-rotationAccum); // roda no sentido contrario da soma de todas as rotacoes, ou seja, volta ao inicial

		velocity = getRandomRate() * 10;
		setPosition(getRandomPosition());
		position.y = ORANGE_DEFAULT_RADIUS;
		setOrientation(getDirection(getPosition()));
		increaseSpeedTimer = TEMPO_ACELERAR_LARANJAS;
	}

	void Orange::kill() {
		//orangeRotation(-rotationAccum);
		setPosition(getRandomPosition());
		position.y = ORANGE_DEFAULT_RADIUS;
		setOrientation(getDirection(getPosition()));
		dead = true;
		visible = false;
		respawnTimer = TEMPO_REAPARECER_LARANJAS;
	}

	AABB Orange::getBoundingBox() {
		auto position = node->position;
		return AABB(
			position.x - 1.5f, position.x + 1.5f,
			position.y - 1.f, position.y + 1.f,
			position.z - 1.5f, position.z + 1.5f);
	}

	bool Orange::handleCarCollision(Car* car) {
		std::cout << "Orange collision\n";

		//stop car
		Application::getInstance()->getGameState().lives--;
		car->reset();
		return false;
	}

}
