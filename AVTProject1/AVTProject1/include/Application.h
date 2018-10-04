#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

namespace AVTEngine
{
	#define WINDOW_WIDTH 640
	#define WINDOW_HEIGHT 480
	#define WINDOW_TITLE "MICRO MACHINES RECREATION"

	class Application
	{
	private:
		unsigned int windowHandle = 0;
		int frameCount;
		Camera
			topOrtoCamera = Camera(glm::ortho(0, 2, 2, 0), glm::mat4(1)),
			topPerspectiveCamera = Camera(glm::perspective(70.f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.f, 1000.f), glm::mat4(1)),
			followCamera = Camera(glm::ortho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0), glm::mat4(1));
		Camera* currentCamera = &topOrtoCamera;

	public:
		Application();
		~Application();

		void init(int argc, char* argv[]);
		void mainLoop();
		void incrementFrameCounter();
		unsigned int getWindowHandle();
		Camera& getCurrentCamera() { return *currentCamera; }

	private:
		void setupGLUT(int argc, char* argv[]);
		void setupGLEW();
		void setupOpenGL();
		void setupCallbacks();
	};
}