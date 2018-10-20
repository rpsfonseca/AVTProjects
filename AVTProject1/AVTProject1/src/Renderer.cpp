#include "Renderer.h"
#include "Mesh.h"
#include "RenderCommand.h"
#include "CommandBuffer.h"
#include "Material.h"
#include "OpenGLError.h"

#include "GL\glew.h"

#include <ctime>
#include <iostream>

namespace AVTEngine
{
	glm::vec3 Renderer::CLEAR_COLOR = glm::vec3(0.1f, 0.1f, 0.1f);

	// Default constructor.
	// Does nothing other than constructing a variable of its type.
	// Its setup is called from setupApp in the Application class.
	Renderer::Renderer()
	{
		commandBuffer = new CommandBuffer(this);
	}

	Renderer::~Renderer()
	{
		delete commandBuffer;
	}

	// As the name implies, sets up the renderer.
	// - Prints OpenGL version to console.
	// - Creates its current shader and gets the uniform blcok binding from it.
	// - Sets up a few gl options, in terms of rendering.
	void Renderer::setupRenderer()
	{
		/*currentShader = Shader("../../projects/engine/src/vertex_shader.glsl", "../../projects/engine/src/frag_shader.glsl");
		uboBp = currentShader.uniformBlockBinding();*/

		glClearColor(CLEAR_COLOR.x, CLEAR_COLOR.y, CLEAR_COLOR.z, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
		glDepthRange(0.0, 1.0);
		glClearDepth(1.0);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	// As the name implies, it runs before the draw method.
	// For now it just:
	// - Clears screen and depth buffer
	// - Binds the uniform buffer
	// - Activates the currentShader
	void Renderer::preDraw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*glBindBuffer(GL_UNIFORM_BUFFER, uboId);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &viewMatrix);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &projectionMatrix);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);*/
	}

	void Renderer::renderPushedCommands()
	{
		std::vector<RenderCommand> renderCommands = commandBuffer->getRenderCommands();

		for (unsigned int i = 0; i < renderCommands.size(); ++i)
		{
			renderCommand(&renderCommands[i], nullptr);
		}

		OpenGLError::checkOpenGLError("ERROR: Could not draw scene.");
	}

	// As the name implies, it runs after the draw method.
	// For now it just unbinds the shader program and the vertex array.
	void Renderer::postDraw()
	{
		glUseProgram(0);
		glBindVertexArray(0);
	}

	void Renderer::setProjectionMatrix(const glm::mat4& mat)
	{
		projectionMatrix = mat;
	}

	void Renderer::setViewMatrix(const glm::mat4& mat)
	{
		viewMatrix = mat;
	}

	void Renderer::renderCommand(RenderCommand* command, Camera* camera)
	{
		Material* material = command->material;
		Mesh* mesh = command->mesh;

		material->getShader()->use();

		material->getShader()->setMat4("transform", command->transform);

		renderMesh(mesh);
	}

	void Renderer::renderMesh(Mesh* mesh)
	{
		glBindVertexArray(mesh->getVao());
		if (mesh->usingIndices > 0)
		{
			glDrawElements(mesh->topology == TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, mesh->getIndicesSize(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(mesh->topology == TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, 0, mesh->getVerticesSize());
		}
	}
}