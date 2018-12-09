"use strict"

class Butter extends DinamicEntity{

	constructor(node, startPos){
		super(node, startPos);
	}

	// nao faz nada
	update(delta){
		return 
	}

	get type(){
		return TYPE.BUTTER;
	}

	getBoundingVolume(){
		var position = this.getPosition();
		var x = position.x;
		var y = position.y;
		var z = position.z;
		return new AABBox(x-12.5,x+12.5,y-3.5,y+3.5,z-5,z+5);
	}
}