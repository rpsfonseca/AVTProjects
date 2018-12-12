"use strict"

/******* CONSTANTS OLD PROJECT ********/
const WHITE = 0xffffff;
const DARK_RED = 0xc14545;
const DARK_GREY = 0x14191b;
const LIGHT_GREY = 0x535254;
const LIGHT_BLUE = 0x5cb1f2;
const DARK_BLUE = 0x0e4eb5;
const ORANGE = 0xf79f11;
const GREEN = 0x0c6806;
const DARK_GREEN = 0x0b5106;
const BROWN = 0xCD853F;
const LIGHT_YELLOW = 0xFFFF66

const NUM_OR = 3;
const NUM_VEL = 6;

var CAMERA = {
    ORTHOGRAPHIC:0,
    PERSPECTIVE:1,
    PERSPECTIVE_FOLLOW:2
}

var TYPE = {
	CAR: 0,
	CHEERIO: 1,
	ORANGE: 2,
	BUTTER: 3,
	WALL: 4
}

//Light constants
var LIGHT = {
	light: true,
	phong: true,
	lamb: false,
	velas: false,
	spotLight: false
}

var velas = new Array(NUM_VEL);
for(var i = 0; i < NUM_VEL; i++){	
	velas[i]= new THREE.PointLight( 0xff23b9, 0.4, 0, 300 );  // 0xff23b9
	velas[i].castShadow = true;
}

velas[0].position.set(35.0, 5.0, -35.0);
velas[1].position.set(35.0, 5.0, 35.0);
velas[2].position.set(-35.0, 5.0, -35.0);
velas[3].position.set(-35.0, 5.0, 35.0);
velas[4].position.set(0.0, 5.0, 15.0);	
velas[5].position.set(0.0, 5.0, -15.0);

var light1 = new THREE.DirectionalLight(0x505050);
light1.position.set(0, 10, 0);
light1.castShadow = true;
//light1.shadowCameraVisible = true; //ver efeito da luz

//var spotLight1 = new THREE.SpotLight(0xa0a0a0);
//var spotLight2 = new THREE.SpotLight(0xa0a0a0);
 

//Gamestate constants
var nVidasPerdidas = -1;




//Level constants
const LEVEL_WIDTH = 160
const LEVEL_HEIGHT = 135
const NUM_ORANGES = 3

const Y_AXIS = new THREE.Vector3(0,1,0);

//Keyboard Keybinds
const TECLA_ACELERAR = 81 // Q
const TECLA_DESACELERAR = 65 // W
const TECLA_VIRAR_ESQUERDA = 79 // O
const TECLA_VIRAR_DIREITA = 80 // P

//Camera Keybinds
const TECLA_1 = 49;
const TECLA_2 = 50;
const TECLA_3 = 51;


//Light keybinds
const TECLA_N = 78; //Directional Light
const TECLA_H = 72; //Spot Light
const TECLA_C = 67; //Point Light

//System Keybinds
const TECLA_S = 83; //Pause
const TECLA_V = 86; //Stereo Effect
const TECLA_F = 70; //Fog Effect
const TECLA_L = 76; //Shadow plane

//Entity constants
const MIN_DRAG = 10

//Car constants
const CAR_MAX_VELOCITY = 30
const CAR_MAX_TURNRATE = 2
const CAR_ACCELERATION = 10
const CAR_DECELERATION = 5

//Orange constants
const ORANGE_DEFAULT_RADIUS = 2
const TEMPO_REAPARECER_LARANJAS = 3 // 3 segundos
const TEMPO_ACELERAR_LARANJAS = 5  // 5 segundos
const MAX_ORANGE_RANDOM_ANGLE = (Math.PI / 6); //isto veio de JS
const ORANGE_MAX_VELOCITY = 20
const ORANGE_MAX_TURNRATE = 3

//Cheerio constants
const CHEERIO_MAX_VELOCITY = 100
const CHEERIO_MAX_TURNRATE = 0

