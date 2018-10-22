#pragma once

namespace AVTEngine {

	//Level constants
	#define _USE_MATH_DEFINES
	#define LEVEL_WIDTH 700
	#define LEVEL_HEIGHT 300

	#define Y_AXIS glm::vec3(0,1,0);

	#define TECLA_ACELERAR = 38; // seta cima
	#define TECLA_DESACELERAR = 40; // seta baixo
	#define TECLA_VIRAR_ESQUERDA 37; // seta esquerda
	#define TECLA_VIRAR_DIREITA = 39; // seta direita

	//Entity constants
	#define MIN_DRAG 10

	//Car constants
	#define CAR_MAX_TURNRATE 6
	#define CAR_ACCELERATION 20;
	#define CAR_DECELERATION 10;

	//Orange constants
	#define ORANGE_DEFAULT_RADIUS 5;
	#define TEMPO_REAPARECER_LARANJAS 3; // 3 segundos
	#define TEMPO_ACELERAR_LARANJAS 5;  // 5 segundos
	#define MAX_ORANGE_RANDOM_ANGLE (M_PI / 6); //isto veio de JS

}