class Wall{
	constructor(xmin,xmax,ymin,ymax,zmin,zmax){
		this.bound = new AABBox(xmin,xmax,ymin,ymax,zmin,zmax);
	}

	getPosition(){
		return this.bound.center;
	}

	update(delta){
		return;	// Parede nao faz nada
	}

	get type(){
		return TYPE.WALL;
	}

	getBoundingVolume(){
		return this.bound;
	}

	isDisabled(){
		return false;
	}

	reset(){
		// nao faz nada, nao precisa
	}
}