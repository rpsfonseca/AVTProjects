"use strict"

class DinamicEntity extends Entity{

	//Car Constructor
	constructor(node, startPos, maxVelocity, maxTurnRate){
		super(node);

		this.setPosition(startPos);
		//this.orientation = (1, 0, 0); TODO

		this.orientation = new THREE.Vector3(1,0,0);
		this.minDrag = 10; // Forca minima de fricao

		this.maxVelocity = maxVelocity;  // Velocidade maxima
		this.maxTurnRate = maxTurnRate;  // Velocidade maxima de rotação

		this.velocity = 0;	// Velocidade inicial
		this.minVelocity = 0.1; // Velocidade para qual o algoritmo arredonda para 0
	}

	//TODO Orange Constructor

	//TODO Butter Constructor
	/* 	
	//Butter
	DynamicEntity::DynamicEntity(SceneNode *node_, glm::vec3 startPos_) : Entity(node_) {
		setPosition(startPos_);
	};
	*/

	integrate(accel,turnRate,delta){

		//Calculate Rotation
		var rotateAmount = (turnRate * delta * (this.velocity / this.maxVelocity));
		super.rotate(rotateAmount); // Tells the Entity class to tell the Node class that the node needs to update

		//Calculate Speed
		this.velocity += accel * delta;
		//console.log("Delta: " + delta);
		if(this.isMoving()){
			this.velocity *= 0.995;	// Aplica forca de atrito para desacelarar 
		}

		if(Math.abs(this.velocity) < Math.abs(this.minVelocity)){
			this.velocity = 0;
		}
		if(Math.abs(this.velocity) > Math.abs(this.maxVelocity)){
			this.velocity = this.maxVelocity;
		}


		//Calculo da alteraçao da posição consoante a velocidade
		//É preciso pegar no vector de orientaçao, multiplica-lo pela velocidade actual, e adicionar o resultado à posição actual do carro
		var ori = this.orientation.clone();
		var velocityVector = ori.multiplyScalar(this.velocity * delta);

		this.position.add(velocityVector);
		super.setPosition(this.position); //Tells the Entity class to tell the Node class that the node needs to update
	}

	reset(){
		this.accel = 0;
		this.velocity = 0;
	}

	getRandomRate(){
    var min = 1;
    var max = 5;
    return Math.floor(Math.random() * (max - min)) + min;
	}

	isMoving(){
		return Math.abs(this.velocity) > this.minVelocity;
	}
}