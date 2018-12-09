"use strict"

class Cheerio extends DinamicEntity{
	constructor(node, startPos){
		super(node, startPos, CHEERIO_MAX_VELOCITY, CHEERIO_MAX_TURNRATE);
		
		this.initialPos = startPos;
		this.minVelocity = 0.1; // Velocidade para qual o algoritmo arredonda para 0
		this.minDrag = MIN_DRAG; // Forca minima de fricao
	}

	update(delta){
		this.integrate(0, 0, delta);
	}

	/*get type(){
		return TYPE.CHEERIO;
	}*/

	reset(){ 
		super.reset();
		this.setPosition(this.initialPos);
	}

	getBoundingVolume(){
		return new Circle(this.getPosition(),1.25+0.5);
	}

	
}
