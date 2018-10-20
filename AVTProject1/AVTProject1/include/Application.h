#pragma once

#include "Camera.h"

#include <string>
#include <glm/gtc/matrix_transform.hpp>

namespace AVTEngine
{
	#define FPS 60
	#define INV_FPS 1/FPS
	#define WINDOW_WIDTH 640
	#define WINDOW_HEIGHT 480
	#define WINDOW_TITLE "MICRO MACHINES RECREATION"

	class Renderer;

	class Application
	{
	private:
		static unsigned int windowHandle;
		static int frameCount;
		Camera
			topOrtoCamera = Camera(glm::ortho(0, 2, 2, 0), glm::mat4(1)),
			topPerspectiveCamera = Camera(glm::perspective(70.f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.f, 1000.f), glm::mat4(1)),
			followCamera = Camera(glm::ortho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0), glm::mat4(1));
		Camera* currentCamera = &topOrtoCamera;

		static int windowWidth;
		static int windowHeight;

		static int initialTime;
		static int finalTime;

		static std::string framesPerSecond;

		static Renderer* renderer;

	public:
		Application();
		~Application();

		void init(int argc, char* argv[]);
		void mainLoop();
		void incrementFrameCounter();

		void setCleanupFunction(void(*func)());
		void setRenderFunction(void(*func)());

		unsigned int getWindowHandle();
		Camera& getCurrentCamera() { return *currentCamera; }

	private:
		void setupGLUT(int argc, char* argv[]);
		void setupGLEW();
		void setupOpenGL();
		void setupCallbacks();

		static void updateFramesPerSecond();

		static void(*cleanupFunction)();
		static void(*renderFunction)();
		static void display();
		static void reshape(int w, int h);
		static void timer(int value);
	};
}