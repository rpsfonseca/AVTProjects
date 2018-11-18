#pragma once

#include "Camera.h"
#include "GameState.h"
#include "HUD.h"

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
	class Scene;

	class Application
	{
	public:
		Renderer* renderer;
		Scene* scene;
	private:
		static unsigned int windowHandle;
		static int frameCount;
		FixedViewCamera
			topOrtoCamera = FixedViewCamera(glm::ortho(-80.f, 80.f, -60.f, 60.f, -50.f, 50.f), glm::lookAt(glm::vec3(0, 10, 0), glm::vec3(0), glm::vec3(0, 0, 1))),
			topPerspectiveCamera = FixedViewCamera(glm::perspective(70.f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 1000.f), glm::lookAt(glm::vec3(0, 100, -100), glm::vec3(0), glm::vec3(0, 1, 0)));
		ArcballCamera followCamera = ArcballCamera(glm::perspective(70.f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 1000.f), glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)));
		Camera* currentCamera = &topPerspectiveCamera;
		GameState gameState;
		HUD* hud;

		static int windowWidth;
		static int windowHeight;

		static int initialTime;
		static int finalTime;

		static std::string framesPerSecond;


	public:
		~Application();

		static Application* getInstance();

		void init(int argc, char* argv[]);
		void mainLoop();
		void incrementFrameCounter();

		void setCleanupFunction(void(*func)());
		void setRenderFunction(void(*func)());

		unsigned int getWindowHandle();
		void changeCamera(int cameraNum);
		Camera& getCurrentCamera() { return *currentCamera; }
		GameState& getGameState() { return gameState; }

	private:
		Application();

		static Application* instance;

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