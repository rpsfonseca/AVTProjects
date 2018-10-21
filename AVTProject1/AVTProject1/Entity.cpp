#include "Entity.h"


namespace AVTEngine
{

	Entity::Entity(Shader *shader_, Mesh *mesh_, float maxVelocity_, float orientation_) :
		shader(shader_), mesh(mesh_), maxVelocity(maxVelocity_), orientation(orientation_){
		
		velocity = 0;	// Velocidade inicial
		accel = 0;
		minVelocity = 0.1; // Velocidade para qual o algoritmo arredonda para 0
		minDrag = MIN_DRAG; // Forca minima de fricao
		enabled = true;
		rotationAccum = 0;
	};

	


	void Entity::integrate(float accel_, float turnRate_, float delta_) { //Delta makes it fps independent
		//this.rotate(turnRate * delta * (this.velocity / this.maxVelocity));

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

		//var orientation = this.orientation.clone();
		//var velocityVector = orientation.multiplyScalar(this.velocity * delta);
		//this.object.position.add(velocityVector);
	}

	

	void Entity::disable() {
		enabled = false;
	};

	void Entity::enable() {
		enabled = true;
	};

	// uma entidade disabled nao "existe" no mapa, ou seja, nao sofre colisoes e nao e atualizada (apesar de ainda poder aparecer)
	bool Entity::isDisabled() {
		return !enabled;
	}

	bool Entity::isMoving() {
		return abs(velocity) > minVelocity;
	}

	float Entity::getOrientation() {
		return orientation;
	}

	glm::vec3 Entity::getPosition() {
		return position;
	}

	void Entity::setPosition(glm::vec3 position_) {
		position = position_;
	}

	//Reformular isto para C++
	//Aplicar rotaçao na matriz de entidade
	void Entity::rotate(float angle_) {
		rotationAccum += angle_;
		//this.object.rotateOnAxis(yAxis, angle);
		//this.orientation.applyAxisAngle(yAxis, angle);
	}

	void Entity::reset() {
		accel = 0;
		velocity = 0;
	}

	//Reformular isto para C++
	int Entity::getRandomRate() {
		/* 
		var min = 1;
		var max = 5;
		return Math.floor(Math.random() * (max - min)) + min;
		*/
	}

	
}