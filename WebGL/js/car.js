"use strict"

class Car extends DinamicEntity{
	constructor(node, startPosition, rotation){
		super(node, startPosition, CAR_MAX_VELOCITY, CAR_MAX_TURNRATE);

		this.acceleration = 15; // Aceleracao para a frente
		this.deceleration = 10; // Aceleracao para tras
		this.initialPos = startPosition;
		
		
		//Car spotlights
		//this.spotLight1Target = new THREE.Object3D();
		//this.spotLight2Target = new THREE.Object3D();
		//this.spotLight1Target.position.set((0-4.625)+0.25,1.25,2);
		//this.spotLight2Target.position.set((0-4.625)+0.25,1.25,-2);
		//this.spotLight1Target.position.set(0.25,1.25,2);
		//this.spotLight2Target.position.set(0.25,1.25,-2);
		//this.object.add(this.spotLight1Target);
		//this.object.add(this.spotLight2Target);

		/*
		this.spotLight1 = new THREE.SpotLight(0xa0a0a0);
		this.spotLight2 = new THREE.SpotLight(0xa0a0a0);
		//this.spotLight1.position.set((0-4.625)+1.25,1.75,2);
		//this.spotLight2.position.set((0-4.625)+1.25,1.75,-2);

		this.spotLight1.position.set(0,2,2);
		this.spotLight2.position.set(0,2,-2);


		this.spotLight1.target = this.spotLight1Target;
		this.spotLight2.target = this.spotLight2Target;

		this.spotLight1.angle = 0.6;
		this.spotLight2.angle = 0.6;

		
		this.object.add(this.spotLight1);
		this.object.add(this.spotLight2);
		*/

		this.setPosition(startPosition);
		//this.object.position.setY(2.5); //Distance from table
		//this.position.setY(2.5); //Distance from table
		this.rotate(rotation);
		this.object.name="car";
	}

	reset(){
		super.reset();
		this.rotate(-this.rotationAccum); // roda no sentido contrario da soma de todas as rotacoes, ou seja, volta ao inicial
		this.setPosition(this.initialPos); //Voltar à posição inicial do carro
		gameState.lives--;
	}

	update(delta){
		gameState.score++;
		//console.log("Car updated");
		var turnRate = 0;

		//TODO check keyboard input method names
		
		if(keyboard.isKeyPressed(TECLA_VIRAR_ESQUERDA)){
			turnRate = this.maxTurnRate;
		} else if(keyboard.isKeyPressed(TECLA_VIRAR_DIREITA)){
			turnRate = - this.maxTurnRate;
		}
		
		var accel = 0;
		if(keyboard.isKeyPressed(TECLA_ACELERAR)){
			accel = this.acceleration;
			//console.log("Acelerei");
			//console.log("Car position: " + this.position.x);
		}
		
		else if(keyboard.isKeyPressed(TECLA_DESACELERAR)){
			accel = - this.deceleration;
		}

		/*
		if(keyboard.isKeyPressed(TECLA_H)){
			keyboard.unpressKey(TECLA_H);
			//this.spotLight1.intensity = 1 - this.spotLight1.intensity;
			//this.spotLight2.intensity = 1 - this.spotLight2.intensity;
			this.spotLight1.intensity = 1;
			this.spotLight2.intensity = 1;
		}*/
		

		//Update
		//console.log(this.position);
		super.integrate(accel, turnRate, delta);	
	}

	doVrDemoMovement(delta) {
		var turnRate = 0;

		let left = Math.random() < 0.5;
		let right = Math.random() < 0.5;
		let ahead = Math.random() < 0.5;
		let back = Math.random() < 0.5;

		if(left) {
			turnRate = this.maxTurnRate;
		} else if(right) {
			turnRate = - this.maxTurnRate;
		}
		
		var accel = 0;
		if(ahead) {
			accel = this.acceleration;
		} else if(back) {
			accel = -this.deceleration;
		}

		super.integrate(accel, turnRate, delta);	
	}

	get type(){
		return TYPE.CAR;
	}

	getBoundingVolume(){
		return new Circle(this.getPosition(),2);
	}

	getInitialPosition(){
		return this.initialPos;
	}

}