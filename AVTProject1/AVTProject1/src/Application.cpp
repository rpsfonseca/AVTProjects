#include "Application.h"
#include "ResourcesManager.h"
#include "Input.h"
#include "Renderer.h"
#include "scene.h"

#include <iostream>
#include <sstream>
#include <time.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

namespace AVTEngine
{ 
	unsigned int Application::windowHandle = 0;
	int Application::frameCount = 0;
	int Application::windowWidth = WINDOW_WIDTH;
	int Application::windowHeight = WINDOW_HEIGHT;
	int Application::initialTime = time(NULL);
	int Application::finalTime;
	std::string Application::framesPerSecond = "0";
	//Renderer* Application::renderer = nullptr;
//	Scene* Application::scene = nullptr;
	Application* Application::instance = 0;
	void(*Application::cleanupFunction)() = nullptr;
	void(*Application::renderFunction)() = nullptr;


	Application::Application()
	{
	}

	Application::~Application()
	{
		scene->cleanup();
		renderer->cleanup();
		delete renderer;
		delete scene;
	}

	Application* Application::getInstance()
	{
		if (instance == 0)
		{
			instance = new Application();
		}

		return instance;
	}

	void Application::init(int argc, char* argv[])
	{
		ResourcesManager::init();

		scene = new Scene();
		renderer = new Renderer();

		scene->setRenderer(renderer);

		setupGLUT(argc, argv);
		setupGLEW();

		scene->setupSceneManager();

		setupOpenGL();
		setupCallbacks();


		hud = new HUD();
	}

	void Application::mainLoop()
	{
		glutMainLoop();
	}

	void Application::incrementFrameCounter()
	{
		frameCount++;
	}

	void Application::setCleanupFunction(void(*func)())
	{
		cleanupFunction = func;
	}

	void Application::setRenderFunction(void(*func)())
	{
		renderFunction = func;
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

		renderer->setupRenderer();

		/*glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
		glDepthRange(0.0, 1.0);
		glClearDepth(1.0);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);*/

		scene->pushToRender();
	}

	void Application::setupCallbacks()
	{
		glutCloseFunc(cleanupFunction);
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutKeyboardFunc(Input::keyPressCallback);
		glutKeyboardUpFunc(Input::keyReleaseCallback);
		glutMouseFunc(Input::mouseButtonsCallback);
		glutMotionFunc(Input::mouseMovementCallback);
		glutTimerFunc(1000 * INV_FPS, timer, 0);
	}

	void Application::updateFramesPerSecond()
	{
		frameCount++;
		finalTime = time(NULL);
		if (finalTime - initialTime > 0)
		{
			std::ostringstream oss;
			oss << frameCount / (finalTime - initialTime);
			framesPerSecond = oss.str();

			frameCount = 0;
			initialTime = finalTime;
		}
	}

	void Application::display()
	{
		getInstance()->renderer->setProjectionMatrix(getInstance()->currentCamera->getProjection());
		getInstance()->renderer->setViewMatrix(getInstance()->currentCamera->getView());

		getInstance()->renderer->preDraw();
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/*if (renderFunction != nullptr)
		{
			renderFunction();
		}*/
		getInstance()->renderer->renderPushedCommands();
		getInstance()->renderer->postDraw();

		getInstance()->hud->draw();

		glutSwapBuffers();

		updateFramesPerSecond();
	}

	void Application::reshape(int w, int h)
	{
		windowWidth = w;
		windowHeight = h;
		glViewport(0, 0, windowWidth, windowHeight);
	}

	void Application::timer(int value)
	{
		std::ostringstream oss;
		oss << WINDOW_TITLE << ": " << framesPerSecond << " FPS @ (" << windowWidth << "x" << windowHeight << ")";
		std::string s = oss.str();
		glutSetWindow(windowHandle);
		glutSetWindowTitle(s.c_str());
		glutPostRedisplay();
		glutTimerFunc(1000 * INV_FPS, timer, 0);
	}

	unsigned int Application::getWindowHandle()
	{
		return windowHandle;
	}

	void Application::changeCamera(int cameraNum) {
		switch (cameraNum) {
		case 1: this->currentCamera = &topOrtoCamera; break;
		case 2: this->currentCamera = &topPerspectiveCamera; break;
		case 3: this->currentCamera = &followCamera; break;
		}
	}
}