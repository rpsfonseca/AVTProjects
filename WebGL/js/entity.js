"use strict"

// Superclasse de todos os objectos que se movem
class Entity{

	constructor(node){
		this.object = new THREE.Object3D();
		this.rotationAccum = 0;
		this.node = node;
		this.enabled = true;

		this.orientation = orientation2; 
		this.movementOrientation = orientation2;	
	}

	disable(){
        this.enabled = false;
    }

    enable(){
        this.enabled = true;
    }

    // uma entidade disabled nao "existe" no mapa, ou seja, nao sofre colisoes e nao e atualizada (apesar de ainda poder aparecer)
    isDisabled(){
    	return !this.enabled;
    }

	getOrientation(){
		return this.orientation.clone();
	}

	getPosition(){
		//return this.object.position.clone();
		return this.position.clone();
	}

	setPosition(position){
		//this.object.position.copy(position);
		this.position.copy(position);
		//TODO this.node.setPosition(position); //Tell node to change position
	}

	rotate(angle){
		this.rotationAccum += angle;


		//Rotate model 		NOT SURE IF THIS IS CURRENTLY RIGHT
		this.rotation.rotateOnAxis(Y_AXIS, angle);
		//TODO this.node.setRotation(this.rotation)


		//Also update orientation, for movement calculation purposes
		this.orientation.applyAxisAngle(Y_AXIS, angle);	
	}

	orangeRotate(angle, axis) {

		this.rotationAccum += angle;

		//Rotate model
		this.rotation.rotateOnAxis(axis, angle);
		//TODO this.node.setRotation(this.rotation)

		//Also update orientation, for movement calculation purposes
		this.orientation.applyAxisAngle(axis, angle);	
	}

	//TODO setMesh
	//TODO setMaterial
}