#include "Application.h"
#include "ResourcesManager.h"

#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>

namespace AVTEngine
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::init(int argc, char* argv[])
	{
		setupGLUT(argc, argv);
		setupGLEW();
		setupOpenGL();

		ResourcesManager::init();
	}

	void Application::mainLoop()
	{
		glutMainLoop();
	}

	void Application::incrementFrameCounter()
	{
		frameCount++;
	}

	void Application::setupGLUT(int argc, char* argv[])
	{
		glutInit(&argc, argv);

		glutInitContextVersion(3, 3);
		glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
		glutInitContextProfile(GLUT_CORE_PROFILE);

		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		windowHandle = glutCreateWindow(WINDOW_TITLE);
		if (windowHandle < 1) {
			std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	void Application::setupGLEW()
	{
		glewExperimental = GL_TRUE;
		GLenum result = glewInit();
		if (result != GLEW_OK)
		{
			std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
			exit(EXIT_FAILURE);
		}
		GLenum err_code = glGetError();
		printf("Vendor: %s\n", glGetString(GL_VENDOR));
		printf("Renderer: %s\n", glGetString(GL_RENDERER));
		printf("Version: %s\n", glGetString(GL_VERSION));
		printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	void Application::setupOpenGL()
	{
		std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
		glDepthRange(0.0, 1.0);
		glClearDepth(1.0);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	void Application::setupCallbacks()
	{
		/*glutCloseFunc(cleanup);
		glutDisplayFunc(display);
		glutIdleFunc(idle);
		glutReshapeFunc(reshape);
		glutTimerFunc(0, timer, 0);*/
	}

	unsigned int Application::getWindowHandle()
	{
		return windowHandle;
	}
}