"use strict"

class Orange extends Entity{
	constructor(node, levelWidth, levelHeight){            
        super(node); //Este construtor é diferent do utilizado para o carro

        this.velocity = this.getRandomRate() * 2; //Oranges shouldn't all behave the same

        this.maxVelocity = ORANGE_MAX_VELOCITY;  // Velocidade maxima
        this.maxTurnRate = ORANGE_MAX_TURNRATE;  // Velocidade maxima de rotação

        //Margin for when orange exits table
        this.levelWidth = levelWidth - 2*(ORANGE_DEFAULT_RADIUS + 0.1);
        this.levelHeight = levelHeight - 2*(ORANGE_DEFAULT_RADIUS + 0.1);

        //Get a random position and direction
        var pos = this.getRandomPosition();
        var movOrientation = this.getDirection(pos);
        this.orientation = movOrientation;
        this.movementOrientation = movOrientation;

        this.increaseSpeedTimer = TEMPO_ACELERAR_LARANJAS;
        this.respawnTimer = 0;
        this.dead = false;

		this.position.copy(pos);
        this.setPosition(this.object.position);
        this.position.y = ORANGE_DEFAULT_RADIUS; //Set minimum height, so the orange isn't inside the table

		this.object.name="orange";
	}

    update(delta){
        this.increaseSpeedTimer -= delta;

        if(this.increaseSpeedTimer < 0){
            this.increaseSpeedTimer = TEMPO_ACELERAR_LARANJAS - this.increaseSpeedTimer; 
            
            this.velocity += (Math.floor(Math.random() * 2) + 1) * 5;
        }

        if(this.dead){
            this.respawnTimer -= delta;
            if(this.respawnTimer < 0){
                this.dead = false;
                this.visible = true; //this.object.visible = true;
            } else {
                return;
            }
        }


        this.orangeMovement(delta);
    }

    orangeMovement(delta){ 
        var temp = this.movementOrientation.clone();
        var velocityVector = temp.multiplyScalar(this.velocity*delta); //Calculate the speed vector
        this.position.add(velocityVector); //Add the speed vector to the current position
        this.setPosition(this.position); //Update node position

        // calcula quanto temos de rodar para coincidir com a velocidade atual
        var turnRate = (this.velocity*delta) / ORANGE_DEFAULT_RADIUS;
        //this.orangeRotation(turnRate);       
    }

    orangeRotation(turnRate){
        this.rotationAccum += turnRate;
        var normalized = this.movementOrientation.clone();
        normalized.normalize();
        normalized.applyAxisAngle(new THREE.Vector3(0,1,0), 90*(Math.PI/180)); //Rodar o vector para obter um eixo de rotacao adequado ao movimento
        
        //this.object.rotateOnAxis(temp, turnRate); //rotateOnAxis( Axis, Angle)   //angle em radianos
        super.orangeRotate(turnRate, normalized); //Tells the Entity class to tell the Node class that the node needs to update
    }

    getDirection(pos){
        var direction = pos.clone().multiplyScalar(-1); //Direcção é oposta à posição inicial, de modo a percorrer a mesa e evitar que saia logo
        direction.setY(0); //Não há movimento vertical

        direction = direction.normalize()
        direction.applyAxisAngle(Y_AXIS,(Math.random() * MAX_ORANGE_RANDOM_ANGLE * 2) - MAX_ORANGE_RANDOM_ANGLE)
        return direction;
    }

    getRandomPosition(){
        var side1 = Math.random() < 0.5;
        var side2 = Math.random() < 0.5;

        var x;
        var z;

        if(side1){ // Começa ou no topo ou em baixo
            z = (side2 ? this.levelHeight : -this.levelHeight) / 2; 
            x = ((Math.random() * this.levelWidth * 2) - this.levelWidth) / 2;
        } else { // Começa a esquerda ou a direita
            x = (side2 ? this.levelWidth : -this.levelWidth) / 2; 
            z = ((Math.random() * this.levelHeight * 2) - this.levelHeight) / 2;
        }

        return new THREE.Vector3(x,0,z);
    }

    getRandomRate(){
        var min = 1;
        var max = 5;
        return Math.floor(Math.random() * (max - min)) + min;
    }

    setOrientation(orientation){
        this.movementOrientation.copy(orientation);
    }

    reset(){
        //super.reset();
        this.accel = 0;
        this.velocity = 0;


        this.orangeRotation(-this.rotationAccum);

        this.velocity = this.getRandomRate() * 2.5;
        this.setPosition(this.getRandomPosition());
        
        //this.object.position.setY(ORANGE_DEFAULT_RADIUS);
        this.position.setY(ORANGE_DEFAULT_RADIUS);
        this.setOrientation(this.getDirection(this.getPosition()));
        this.increaseSpeedTimer = TEMPO_ACELERAR_LARANJAS;
    }

    kill(){
        this.dead = true;
        this.visible = false; //The node should be invisible while orange is respawning

        this.orangeRotation(-this.rotationAccum);
        this.setPosition(this.getRandomPosition());
        //this.object.position.setY(ORANGE_DEFAULT_RADIUS);
        this.position.setY(ORANGE_DEFAULT_RADIUS);
        this.setOrientation(this.getDirection(this.getPosition()));
        
        this.respawnTimer = TEMPO_REAPARECER_LARANJAS;
    }
   
    get type(){
        return TYPE.ORANGE;
    }

    getBoundingVolume(){
        return new Circle(this.getPosition(),ORANGE_DEFAULT_RADIUS);
    }
  
}