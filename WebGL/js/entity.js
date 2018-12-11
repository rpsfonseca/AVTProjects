"use strict"

// Superclasse de todos os objectos que se movem
class Entity{

	constructor(node){
		this.object = new THREE.Object3D();
		this.rotationAccum = 0;
		this.node = node;
		this.enabled = true;

		this.position = new THREE.Vector3(0,0,0);
		this.orientation = new THREE.Vector3(0,0,0);
		this.movementOrientation = new THREE.Vector3(0,0,0);
		this.rotation = new THREE.Quaternion(0, 0, 0, 0);
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
		return this.position.clone();
	}

	setPosition(position){
		this.object.position.copy(position);
		this.position.copy(position);
		this.node.position = this.position;
	}

	rotate(angle){
		this.rotationAccum += angle;

		//Rotate model
		this.object.rotateOnAxis(Y_AXIS, angle);
		this.object.getWorldQuaternion(this.rotation);
		this.node.rotation = this.rotation;

		//Also update orientation, for movement calculation purposes
		this.orientation.applyAxisAngle(Y_AXIS, angle);	
	}

	orangeRotate(angle, axis) {

		this.rotationAccum += angle;

		//Rotate model
		//this.rotation.rotateOnAxis(axis, angle);
		//TODO this.node.setRotation(this.rotation)

		//Also update orientation, for movement calculation purposes
		this.orientation.applyAxisAngle(axis, angle);	
	}



	/*
		.getWorldPosition ( target : Vector3 ) : Vector3
		target — the result will be copied into this Vector3. 

		Returns a vector representing the position of the object in world space.

		# .getWorldQuaternion ( target : Quaternion ) : Quaternion
		target — the result will be copied into this Quaternion. 

		Returns a quaternion representing the rotation of the object in world space.

		# .getWorldScale ( target : Vector3 ) : Vector3
		target — the result will be copied into this Vector3. 

		Returns a vector of the scaling factors applied to the object for each axis in world space.

		# .getWorldDirection ( target : Vector3 ) : Vector3
		target — the result will be copied into this Vector3. 

		Returns a vector representing the direction of object's positive z-axis in world space.
	*/
}