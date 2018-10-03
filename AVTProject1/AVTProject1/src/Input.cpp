#include "Input.h"

#include <iostream>

namespace AVTEngine
{
	bool Input::keys[MAX_KEYS];
	bool Input::mouseButtons[MAX_BUTTONS];
	float Input::mouseCoords[2];

	Input::Input()
	{
	}

	Input::~Input()
	{
	}

	bool Input::isKeyDown(unsigned char key)
	{
		return keys[key];
	}

	bool Input::isButtonDown(int button)
	{
		switch (button)
		{
		case MOUSE_LEFT:
			return mouseButtons[MOUSE_LEFT];
			break;
		case MOUSE_MIDDLE:
			return mouseButtons[MOUSE_MIDDLE];
			break;
		case MOUSE_RIGHT:
			return mouseButtons[MOUSE_RIGHT];
			break;
		default:
			return false;
			break;
		}
	}

	inline float Input::getMouseX()
	{
		return mouseCoords[0];
	}

	inline float Input::getMouseY()
	{
		return mouseCoords[1];
	}


	//////////////////////////////////
	/////////// CALLBACKS ////////////
	//////////////////////////////////

	void Input::keyPressCallback(unsigned char key, int x, int y)
	{
		keys[key] = true;
	}

	void Input::keyReleaseCallback(unsigned char key, int x, int y)
	{
		keys[key] = false;
	}

	void Input::mouseMovementCallback(int x, int y)
	{
		mouseCoords[0] = x;
		mouseCoords[1] = y;
	}

	void Input::mouseButtonsCallback(int button, int state, int x, int y)
	{
		switch (button)
		{
		case MOUSE_LEFT:
			mouseButtons[MOUSE_LEFT] = state;
			break;
		case MOUSE_MIDDLE:
			mouseButtons[MOUSE_MIDDLE] = state;
			break;
		case MOUSE_RIGHT:
			mouseButtons[MOUSE_RIGHT] = state;
			break;
		default:
			break;
		}
	}

}