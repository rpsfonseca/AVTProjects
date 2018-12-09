"use strict"

class Circle{
	constructor(center,radius){
		this.center = center;
		this.radius = radius;
	}

	isPointWithin(point){
		var centerToPoint = point.clone().sub(this.center);

		if(centerToPoint.lengthSq() <= this.radius * this.radius){
			return true;
		} else {
			return false;
		}
	 }

	// retorna o ponto dentro do circulo que esteja o mais proximo possivel do ponto dado
	 closestPoint(point){
	 	if(this.isPointWithin(point)){
	 		return point;
	 	} 

	 	var centerToPoint = point.clone().sub(this.center);

	 	centerToPoint.setLength(this.radius);

	 	var closePoint = centerToPoint.add(this.center);

	 	return closePoint;
	}
}

class AABBox{
	constructor(minX,maxX,minY,maxY,minZ,maxZ){
		this.minX = minX;
		this.maxX = maxX;
		this.minY = minY;
		this.maxY = maxY;
		this.minZ = minZ;
		this.maxZ = maxZ;

		this.center = new THREE.Vector3((this.minX + this.maxX) / 2,(this.minY + this.maxY) / 2,(this.minZ + this.maxZ) / 2);
	}

	isPointWithin(point){
		return (this.minX <= point.x) && (point.x <= this.maxX) && (this.minY <= point.y) && (point.y <= this.maxY) && (this.minZ <= point.z) && (point.z <= this.maxZ); 
	}

	// retorna o ponto dentro da caixa que esteja o mais proximo possivel do ponto dado
	closestPoint(point){
		if(this.isPointWithin(point)){
			return point;
		}

		var x = this.center.x;
		var y = this.center.y;
		var z = this.center.z;

		var centerToPoint = point.clone().sub(this.center);

		// forca os valores para estarem dentro da caixa
		centerToPoint.clamp(new THREE.Vector3(this.minX - x,this.minY - y,this.minZ - z),new THREE.Vector3(this.maxX - x,this.maxY - y,this.maxZ - z));

		var closePoint = centerToPoint.add(this.center);

		return closePoint;
	}
}

// Funcao que deteta colisoes
// para detetar colisoes entre caixas e circlos e entre elas proprias podemos usar um so algoritmo
// comecamos por calcular o ponto de bounding1 que esteja mais perto do centro de bounding2 e verificamos se esse ponto esta contido em bounding2
// se estiver e porque ocorreu colisao, se nao esperimentamos o mesmo, so que trocando bounding1 e bounding2. Se nesse caso tambem falhar entao e
// porque nao estao a colidir
// Nota: este algoritmo, atualmente, so funciona para Circulos e AABBox's (pois e muito facil calcular o ponto mais perto mas dentro neste tipo de volumes)
function detectCollision(bounding1,bounding2){
	if(bounding2.isPointWithin(bounding1.closestPoint(bounding2.center))){
		return true;
	} else if (bounding1.isPointWithin(bounding2.closestPoint(bounding1.center))){
		return true;
	}
	return false;
}