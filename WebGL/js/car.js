"use strict"

class Car extends DinamicEntity{
	constructor(node, startPosition, rotation){
		super(node, startPosition, CAR_MAX_VELOCITY, CAR_MAX_TURNRATE);

		this.acceleration = 20; // Aceleracao para a frente
		this.deceleration = 10; // Aceleracao para tras
		this.initialPos = startPosition;

		//Car creation
		/*
		addBodyPiece(this.object, (0-4.625)+1.25, 2.75-2.5, 0, 2.5, 1.5, 4, DARK_RED) //front piece 			//addBodyPiece(obj, x, y, z, lenght, height, width, colorCode)
		addBodyPiece(this.object, (2.25-4.625)+1.25, 2.75-2.5, 0, 2, 1.5, 2, DARK_RED) //middle piece
		addRamp(this.object, (2.75-4.625)+0.75, 3.75-2.5, 0, 2, 0.5, 2, LIGHT_BLUE) //front mirror
		addBodyPiece(this.object, (5.25-4.625)+1.25, 3-2.5, 0, 4, 2, 4, DARK_RED) //back piece
		addSpoilerSupport(this.object, (6.5-4.625)+1, 4.25-2.5, 1, LIGHT_GREY)  // spoiler support 1
		addSpoilerSupport(this.object, (6.5-4.625)+1, 4.25-2.5, -1, LIGHT_GREY) // spoiler support 2
		addRamp(this.object, (7-4.625)+0.5, 4.75-2.5, 0,6,0.5,2, DARK_RED) //spoiler
		addWheel(this.object, (0-4.625)+1.25, 2-2.5, 2.25); 	//function addWheel(obj, x, y, z) {
		addWheel(this.object, (0-4.625)+1.25, 2-2.5, -2.25);
		addWheel(this.object, (5.5-4.625)+1.25, 2-2.5, 2.25);
		addWheel(this.object, (5.5-4.625)+1.25, 2-2.5, -2.25);	
		
		//Car spotlights
		this.spotLight1Target = new THREE.Object3D();
		this.spotLight2Target = new THREE.Object3D();
		this.spotLight1Target.position.set((0-4.625)+0.25,1.25,2);
		this.spotLight2Target.position.set((0-4.625)+0.25,1.25,-2);

		this.spotLight1 = new THREE.SpotLight(0xa0a0a0);
		this.spotLight2 = new THREE.SpotLight(0xa0a0a0);
		this.spotLight1.position.set((0-4.625)+1.25,1.75,2);
		this.spotLight2.position.set((0-4.625)+1.25,1.75,-2);
		this.spotLight1.target = this.spotLight1Target;
		this.spotLight2.target = this.spotLight2Target;

		this.spotLight1.angle = 0.6;
		this.spotLight2.angle = 0.6;

		this.object.add(this.spotLight1Target);
		this.object.add(this.spotLight2Target);
		this.object.add(this.spotLight1);
		this.object.add(this.spotLight2);

		//addSphere(this.object,0,0,0,5.5,DARK_RED)

		node.add(this.object);
	*/


		this.setPosition(startPosition);
		//this.object.position.setY(2.5); //Distance from table
		this.position.setY(2.5); //Distance from table
		this.rotate(rotation);

		this.object.name="car";
	}

	reset(){
		super.reset();
		this.rotate(-this.rotationAccum); // roda no sentido contrario da soma de todas as rotacoes, ou seja, volta ao inicial
		this.setPosition(this.initialPos); //Voltar à posição inicial do carro
	}

	update(delta){

		var turnRate = 0;

		/* 	TODO check keyboard input method names
		if(keyboard.isKeyPressed(TECLA_VIRAR_ESQUERDA)){
			turnRate = this.maxTurnRate;
		} else if(keyboard.isKeyPressed(TECLA_VIRAR_DIREITA)){
			turnRate = - this.maxTurnRate;
		}

		var accel = 0;
		if(keyboard.isKeyPressed(TECLA_ACELERAR)){
			accel = this.acceleration;
		}
		else if(keyboard.isKeyPressed(TECLA_DESACELERAR)){
			accel = - this.deceleration;
		}

		if(keyboard.isKeyPressed(TECLA_H)){
			keyboard.unpressKey(TECLA_H);
			this.spotLight1.intensity = 1 - this.spotLight1.intensity;
			this.spotLight2.intensity = 1 - this.spotLight2.intensity;
		}

		//Update
		auto oldPos = getPosition();
		super.integrate(accel, turnRate, delta);
		*/
	}

	get type(){
		return TYPE.CAR;
	}

	getBoundingVolume(){
		return new Circle(this.getPosition(),5.5);
	}


}

// Funcoes auxiliares para criar a geometria do carro
function addBodyPiece(obj, x, y, z, lenght, height, width, colorCode) {
	var geometry = createRectangle(lenght, height, width);
	var material_phong = new THREE.MeshPhongMaterial({color: colorCode, wireframe: false });
	var basicMaterial = new THREE.MeshBasicMaterial({color: colorCode, wireframe: false});
	var material_Lambert = new THREE.MeshLambertMaterial({color: colorCode, wireframe:false});
	var mesh = new THREE.Mesh(geometry, basicMaterial);
	mesh.material_phong = material_phong;
	mesh.material_Lambert = material_Lambert;
	mesh.basicMaterial = basicMaterial;
	mesh.position.set(x, y, z);
	obj.add(mesh);
	material_phong.needsUpdate=true;
}

function addSpoilerSupport(obj, x, y, z, colorCode){
	var geometry = createPrismTrapezoid(0.5,1, 0.5, 0.5);
	var material_phong = new THREE.MeshPhongMaterial({color: colorCode, wireframe: false });
	var material_Lambert = new THREE.MeshLambertMaterial({color: colorCode, wireframe:false});
	var basicMaterial = new THREE.MeshBasicMaterial({color: colorCode, wireframe: false});
	var mesh = new THREE.Mesh(geometry, basicMaterial);
	mesh.material_phong = material_phong;
	mesh.material_Lambert = material_Lambert;
	mesh.basicMaterial = basicMaterial;
	mesh.position.set(x, y, z);
	obj.add(mesh);
	material_phong.needsUpdate=true;
}

function addRamp(obj,x,y,z,lenght, height, width,colorCode){
	var geometry = createRamp(lenght, height, width);
	var material_phong = new THREE.MeshPhongMaterial({color: colorCode, wireframe: false });
	var material_Lambert = new THREE.MeshLambertMaterial({color: colorCode, wireframe:false});
	var basicMaterial = new THREE.MeshBasicMaterial({color: colorCode, wireframe: false});
	var mesh = new THREE.Mesh(geometry, basicMaterial);
	mesh.material_phong = material_phong;
	mesh.material_Lambert = material_Lambert;
	mesh.basicMaterial = basicMaterial;
	mesh.position.set(x, y, z);
	obj.add(mesh);
	material_phong.needsUpdate=true;
}

function addWheel(obj, x, y, z) {
	var geometry =createPrismGeometry(16,1,0.5);
	var material_phong = new THREE.MeshPhongMaterial({color: DARK_GREY, wireframe: false });
	material_phong.specular = new THREE.Color(0xffffff); //646464
	material_phong.emissive = new THREE.Color(0xc0b0b);
	material_phong.shininess = 30;
	material_phong.reflectivity = 0.2;
	var material_Lambert = new THREE.MeshLambertMaterial({color: DARK_GREY, wireframe:false});
	var basicMaterial = new THREE.MeshBasicMaterial({color: DARK_GREY, wireframe: false});
	var mesh = new THREE.Mesh(geometry, basicMaterial);
	mesh.material_phong = material_phong;
	mesh.material_Lambert = material_Lambert;
	mesh.basicMaterial = basicMaterial;
	mesh.position.set(x, y, z);
	obj.add(mesh);
	material_phong.needsUpdate=true;
}
	

function createPrismGeometry(sides,radius,width){
	var halfWidth = width / 2;
	var geometry = new THREE.Geometry();

	function createFaceVertices(z){
		geometry.vertices.push(new THREE.Vector3(0,0,z));	// os verices centrais tem index 0 e (sides+1)
		var currentVertice = new THREE.Vector3(0,radius,z);
		for(var i = 0; i < sides; i++){
			geometry.vertices.push(currentVertice.clone());
			currentVertice.applyAxisAngle(zAxis,((2*Math.PI)/sides));
		}
	}

	createFaceVertices(halfWidth);
	createFaceVertices(-halfWidth);

	for(var i = 0; i < sides-1; i++){
		geometry.faces.push(new THREE.Face3(0,i+1,i+2));
		geometry.faces.push(new THREE.Face3(sides+3+i,sides+2+i,sides+1));
	}
	geometry.faces.push(new THREE.Face3(1,0,sides)); // conects the last triangle
	geometry.faces.push(new THREE.Face3(sides+2,sides*2+1,sides+1)); // conects the last triangle

	for(var i = 1; i < sides; i++){
		geometry.faces.push(new THREE.Face3(sides+1+i,i+1,i));
	}
	geometry.faces.push(new THREE.Face3(sides*2 + 1,1,sides)); // conects the last triangle

	for(var i = 1; i < sides; i++){
		geometry.faces.push(new THREE.Face3(sides+1+i,sides+2+i,i+1));
	}
	geometry.faces.push(new THREE.Face3(1,sides*2+1,sides+2)); // conects the last triangle

	//geometry.computeBoundingSphere();
	geometry.computeFaceNormals();

	return geometry;
}

function createRectangle(width,height,length){
	return createPrismTrapezoid(width,width,height,length);
}

// baseWidth == topWidth => rectangulo
function createPrismTrapezoid(baseWidth,topWidth,height,length){
	var geometry = new THREE.Geometry();

	function addFaceVertices(width,left,bottom,near){
		geometry.vertices.push(new THREE.Vector3(left,bottom,near));
		geometry.vertices.push(new THREE.Vector3(left+width,bottom,near));
		geometry.vertices.push(new THREE.Vector3(left+width,bottom,near+length));
		geometry.vertices.push(new THREE.Vector3(left,bottom,near+length));
	}

	addFaceVertices(baseWidth,-baseWidth/2,-height/2,-length/2);
	addFaceVertices(topWidth,-topWidth/2,height/2,-length/2);

	geometry.faces.push(new THREE.Face3(0,1,2));
	geometry.faces.push(new THREE.Face3(0,2,3));
	geometry.faces.push(new THREE.Face3(5,4,6));
	geometry.faces.push(new THREE.Face3(6,4,7));

	geometry.faces.push(new THREE.Face3(1,0,4));
	geometry.faces.push(new THREE.Face3(1,4,5));

	geometry.faces.push(new THREE.Face3(2,1,5));
	geometry.faces.push(new THREE.Face3(2,5,6));

	geometry.faces.push(new THREE.Face3(3,2,6));
	geometry.faces.push(new THREE.Face3(3,6,7));

	geometry.faces.push(new THREE.Face3(0,3,7));
	geometry.faces.push(new THREE.Face3(0,7,4));

	geometry.computeFaceNormals();

	return geometry;
}

// creates a 90 degree piramyd
function createRamp(width,height,length){
	var geometry = new THREE.Geometry();

	width /= 2;
	height /= 2;
	length /= 2;

	geometry.vertices.push(new THREE.Vector3(-width,-height,-length));
	geometry.vertices.push(new THREE.Vector3(width,-height,-length));
	geometry.vertices.push(new THREE.Vector3(-width,height,-length));
	geometry.vertices.push(new THREE.Vector3(width,height,-length));
	geometry.vertices.push(new THREE.Vector3(-width,-height,length));
	geometry.vertices.push(new THREE.Vector3(width,-height,length));

	geometry.faces.push(new THREE.Face3(0,1,4));
	geometry.faces.push(new THREE.Face3(4,1,5));

	geometry.faces.push(new THREE.Face3(1,0,2));
	geometry.faces.push(new THREE.Face3(1,2,3));

	geometry.faces.push(new THREE.Face3(2,0,4));
	geometry.faces.push(new THREE.Face3(1,3,5));

	geometry.faces.push(new THREE.Face3(3,2,4));
	geometry.faces.push(new THREE.Face3(4,5,3));

	geometry.rotateY(-Math.PI/2);

	geometry.computeFaceNormals();

	return geometry;
}