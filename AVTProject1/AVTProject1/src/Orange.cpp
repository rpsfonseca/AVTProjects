#include "Orange.h"


namespace AVTEngine
{

	Orange::Orange(SceneNode *node_, Shader *shader_, Mesh *mesh_, float levelWidth_, float levelHeight_){

		DynamicEntity::DynamicEntity(node_, shader_, mesh_, glm::vec3(1, 0, 0), ORANGE_MAX_VELOCITY, ORANGE_MAX_TURNRATE);

		Entity::Entity(shader_, mesh_, 100, 3, glm::vec3(1, 0, 0));

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

		
		//Node.add(this); Adicionar o carro � cena?

		position = pos;
		position.y = ORANGE_DEFAULT_RADIUS; //Set minimum height, so the orange isn't inside the table

		//name = "orange"; Not needed?
							
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
		
		ModelViewMatrix = glm::rotate(ModelViewMatrix, turnRate_ , normalized); //Rotate the model by the right amount, and considering the current axis
	}

	glm::vec3 Orange::getDirection(glm::vec3 pos_) {

		glm::vec3 direction = pos_ * float(-1); //Direc��o � oposta � posi��o inicial, de modo a percorrer a mesa e evitar que saia logo
		direction.y = 0; //N�o h� movimento vertical

		direction = normalize(direction);
		int temp = MAX_ORANGE_RANDOM_ANGLE;
		float rotAngle = rand() % (temp*2 - temp + 1) + temp; //int randNum = rand()%(max-min + 1) + min;
		direction = rotateY(direction, rotAngle); //Dar direc��o aleat�ria

		return direction;
	}

	glm::vec3 Orange::getRandomPosition() { //gera posicao para a laranja fazer spawn

		bool side1 = rand() < 0.5;
		bool side2 = rand() < 0.5;

		float x;
		float z;
		
		if (side1) { 
			z = (side2 ? levelHeight : -levelHeight) / 2; // Come�a ou no topo ou em baixo
			//x = ((Math.random() * this.levelWidth * 2) - this.levelWidth) / 2;
			x = ((rand() * levelWidth * 2) - levelWidth) / 2;
		}
		else { 
			x = (side2 ? levelWidth : -levelWidth) / 2; // Come�a a esquerda ou a direita
			//z = ((Math.random() * this.levelHeight * 2) - this.levelHeight) / 2;
			z = ((rand() * levelHeight * 2) - levelHeight) / 2;
		}

		return glm::vec3(x, 0, z);
	}

	void Orange::setOrientation(glm::vec3 orientation_) {
		movementOrientation = orientation_;
	}

	/* TODO Stuff for collision detection
	get type() {   //Para saber que tipo de colis�o se trata
	return TYPE.ORANGE;
	}

	getBoundingVolume(){ //Raio da caixa para colisao
        return new Circle(this.getPosition(),ORANGE_DEFAULT_RADIUS);
    }
	*/

	void Orange::reset() {
		DynamicEntity::reset();

		position = initialPos;
		orangeRotation(-rotationAccum); // roda no sentido contrario da soma de todas as rotacoes, ou seja, volta ao inicial

		velocity = getRandomRate() * 10;
		setPosition(getRandomPosition());
		position.y = ORANGE_DEFAULT_RADIUS;
		setOrientation(getDirection(getPosition()));
		increaseSpeedTimer = TEMPO_ACELERAR_LARANJAS;
	}

	void Orange::kill() {
		orangeRotation(-rotationAccum);
		setPosition(getRandomPosition());
		position.y = ORANGE_DEFAULT_RADIUS;
		setOrientation(getDirection(getPosition()));
		dead = true;
		visible = false;
		respawnTimer = TEMPO_REAPARECER_LARANJAS;
	}

}
