#pragma once

namespace AVTEngine {

	//Level constants
	#define LEVEL_WIDTH 700
	#define LEVEL_HEIGHT 300

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
	#define MAX_ORANGE_RANDOM_ANGLE = (Math.PI / 6); //isto veio de JS
}