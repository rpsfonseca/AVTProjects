#include "Input.h"

#include <iostream>
#include <GL/freeglut.h>

namespace AVTEngine
{
	bool Input::keys[MAX_KEYS];
	bool Input::mouseButtons[MAX_BUTTONS];
	float Input::mouseCoords[2];

	//// Arcball camera tracking
	// Mouse Tracking Variables
	int startX, startY, tracking = 0;
	// Camera Spherical Coordinates
	float alpha = 39.0f, beta = 51.0f;
	float r = 5.0f; // distance to center

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

		switch (key) {
		// change camera
		case '1':
			Application::getInstance()->changeCamera(1);
			break;
		case '2':
			Application::getInstance()->changeCamera(2);
			break;
		case '3':
			Application::getInstance()->changeCamera(3);
			break;
		}
	}

	void Input::keyReleaseCallback(unsigned char key, int x, int y)
	{
		keys[key] = false;
	}

	void Input::mouseMovementCallback(int x, int y)
	{
		mouseCoords[0] = x;
		mouseCoords[1] = y;

		// mouse camera movement tracking
		int deltaX, deltaY;
		float alphaAux, betaAux;
		float rAux;

		deltaX = -x + startX;
		deltaY = y - startY;

		// left mouse button: move camera
		if (tracking == 1) {
			alphaAux = alpha + deltaX;
			betaAux = beta + deltaY;

			if (betaAux > 85.0f)
				betaAux = 85.0f;
			else if (betaAux < -85.0f)
				betaAux = -85.0f;
			rAux = r;
		}

		float offsetX = rAux * sin(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
		float offsetZ = rAux * cos(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
		float offsetY = rAux * sin(betaAux * 3.14f / 180.0f);
		Application::getInstance()->getCurrentCamera().setArcballOffset({ offsetX, offsetY, offsetZ });
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

		// mouse camera movement tracking
		if (button == GLUT_LEFT_BUTTON) {
			// start tracking the mouse
			if (state == GLUT_DOWN) {
				startX = x;
				startY = y;
				tracking = 1;
			}
			//stop tracking the mouse
			else if (state == GLUT_UP) {
				if (tracking == 1) {
					alpha -= (x - startX);
					beta += (y - startY);
				}
				tracking = 0;
			}
		}
	}

}