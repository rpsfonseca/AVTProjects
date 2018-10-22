#pragma once

#include "Application.h"

namespace AVTEngine
{
	#define MAX_KEYS 1024
	#define MAX_BUTTONS 3
	class Input
	{
	public:
		enum
		{
			MOUSE_LEFT,
			MOUSE_MIDDLE,
			MOUSE_RIGHT
		};

	private:
		static bool keys[MAX_KEYS];
		static bool mouseButtons[MAX_BUTTONS];
		static float mouseCoords[2];

	private:
		Input();
		~Input();

	public:
		static bool isKeyDown(unsigned char key);
		static bool isButtonDown(int button);
		static inline float getMouseX();
		static inline float getMouseY();

		static void keyPressCallback(unsigned char key, int x, int y);
		static void keyReleaseCallback(unsigned char key, int x, int y);
		static void mouseMovementCallback(int x, int y);
		static void mouseButtonsCallback(int button, int state, int x, int y);
	};
}