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
	glUseProgram(0);
	shader->deleteProgram();

	OpenGLError::checkOpenGLError("ERROR: Could not destroy shaders.");
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs


void createBufferObjects()
{
	//app.scene->setupSceneManager();
	//rectangle = new Mesh(vectorOfVertices, indices);

	/*glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(4, VboId);

	//vertex coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTEX_COORD_ATTRIB);
	glVertexAttribPointer(VERTEX_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, 0);

	//normals buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboId[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL_ATTRIB);
	glVertexAttribPointer(NORMAL_ATTRIB, 3, GL_FLOAT, 0, 0, 0);

	//texture coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB);
	glVertexAttribPointer(TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, 0, 0, 0);

	//index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faceIndex), faceIndex, GL_STATIC_DRAW);

	// unbind the VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
	/*glDisableVertexAttribArray(VERTEX_COORD_ATTRIB);
	glDisableVertexAttribArray(NORMAL_ATTRIB);
	glDisableVertexAttribArray(TEXTURE_COORD_ATTRIB);*/

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

	/*glDeleteBuffers(4, VboId);
	glDeleteVertexArrays(1, &VaoId);*/
	OpenGLError::checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}

/////////////////////////////////////////////////////////////////////// SCENE
glm::mat4 transform = glm::mat4(1);
glm::mat4 transform2 = glm::mat4(1);

void renderScene()
{
	glBindVertexArray(VaoId);
	shader->use();

	//shader->setMat4("modelMatrix", app.getCurrentCamera().getViewProjection());
	//glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_INT, (GLvoid*)0);

	shader->setMat4("modelMatrix", transform2);
	//glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_INT, (GLvoid*)0);

	glUseProgram(0);
	glBindVertexArray(0);

	OpenGLError::checkOpenGLError("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	destroyShaderProgram();
	destroyBufferObjects();
}

/////////////////////////////////////////////////////////////////////// SETUP

void init(int argc, char* argv[])
{
	transform = glm::rotate(glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f)), 50.f, glm::vec3(1.f, 0.3f, 0.6f));
	transform2 = glm::translate(transform2, glm::vec3(-1.0f, -1.0f, 0.0f));

	createShaderProgram();
	createBufferObjects();
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