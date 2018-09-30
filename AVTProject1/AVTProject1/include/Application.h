#pragma once

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

	public:
		Application();
		~Application();

		void init(int argc, char* argv[]);
		void mainLoop();
		void incrementFrameCounter();
		unsigned int getWindowHandle();

	private:
		void setupGLUT(int argc, char* argv[]);
		void setupGLEW();
		void setupOpenGL();
		void setupCallbacks();
	};
}