///////////////////////////////////////////////////////////////////////
//
// 
// (c) 2014 by João Madeiras Pereira
//
///////////////////////////////////////////////////////////////////////

#define GLEW_STATIC

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>



//#include "Cube.h"
#include "Shader.h"
#include "FileSystem.h"
#include "ResourcesManager.h"
//#include "Input.h"
#include "OpenGLError.h"
//#include "Scene.h"
#include "Application.h"
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

using namespace AVTEngine;
Shader* shader;

#define VERTEX_COORD_ATTRIB 0
#define NORMAL_ATTRIB 1
#define TEXTURE_COORD_ATTRIB 2

GLuint VaoId, VboId[4];
GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId;

std::string runningDirectory;

/////////////////////////////////////////////////////////////////////// SHADERs

void createShaderProgram()
{
	/*shader = ResourcesManager::loadShader("basic");

	glBindAttribLocation(shader->shaderID, VERTEX_COORD_ATTRIB, "in_Position");*/

	OpenGLError::checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{
	OpenGLError::checkOpenGLError("ERROR: Could not destroy shaders.");
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs


void createBufferObjects()
{
	OpenGLError::checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void destroyBufferObjects()
{
	glDisableVertexAttribArray(VERTEX_COORD_ATTRIB);
	glDisableVertexAttribArray(NORMAL_ATTRIB);
	glDisableVertexAttribArray(TEXTURE_COORD_ATTRIB);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	OpenGLError::checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}

/////////////////////////////////////////////////////////////////////// SCENE
glm::mat4 transform = glm::mat4(1);
glm::mat4 transform2 = glm::mat4(1);

void renderScene()
{
	glBindVertexArray(VaoId);
	shader->use();

	glUseProgram(0);
	glBindVertexArray(0);

	OpenGLError::checkOpenGLError("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	destroyBufferObjects();
}

/////////////////////////////////////////////////////////////////////// SETUP

void init(int argc, char* argv[])
{
	transform = glm::rotate(glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f)), 50.f, glm::vec3(1.f, 0.3f, 0.6f));
	transform2 = glm::translate(transform2, glm::vec3(-1.0f, -1.0f, 0.0f));

}

int main(int argc, char* argv[])
{
	runningDirectory = FileSystem::getRunningDirectory(argv[0]);

	Application* app = Application::getInstance();

	app->getInstance()->setCleanupFunction(cleanup);
	app->getInstance()->setRenderFunction(renderScene);
	app->getInstance()->init(argc, argv);
	init(argc, argv);
	app->getInstance()->mainLoop();

	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////