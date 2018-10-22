#pragma once

#include "Mesh.h"
#include "Shader.h"

#include <glm/glm.hpp>

#include <vector>

namespace AVTEngine
{
	class Mesh;
	class SceneNode;
	class Camera;
	class CommandBuffer;
	struct RenderCommand;

	/**
	This class represents the engine renderer.
	As a renderer it is responsible for drawing the models to the screen.
	*/
	class Renderer
	{
	public:

		static glm::vec3 CLEAR_COLOR;
		Shader currentShader;
		glm::mat4 modelMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;

		unsigned int uboBp; // Uniform block pointer used to retrieve uniform block ID
		unsigned int uboId; // The actual uniform block ID
	
	private:
		CommandBuffer* commandBuffer;

	public:
		/**
		Default constructor.
		Does nothing other than constructing a variable of its type.
		Its setup is called from setupApp in the Application class.
		*/
		Renderer();
		~Renderer();

		/**
		As the name implies, sets up the renderer.
		- Prints OpenGL version to console.
		- Creates its current shader and gets the uniform blcok binding from it.
		- Sets up a few gl options, in terms of rendering.
		*/
		void setupRenderer();

		void pushRenderables(SceneNode* sceneNode);

		/**
		As the name implies, it runs before the draw method.
		For now it just:
		- Clears screen and depth buffer
		- Binds the uniform buffer
		- Activates the currentShader
		*/
		void preDraw();

		/**
		Draw method. The one currently being used.
		The pattern here is that we send the model of a SceneNode to be drawn from the SceneManager, along with its transform.
		*/
		void renderPushedCommands();

		/**
		As the name implies, it runs after the draw method.
		For now it just unbinds the shader program and the vertex array.
		*/
		void postDraw();

		/**

		*/
		void update();

		void cleanup();

		void setProjectionMatrix(const glm::mat4& mat);
		void setViewMatrix(const glm::mat4& mat);

	private:
		void renderCommand(RenderCommand* command, Camera* camera);
		void renderMesh(Mesh* mesh);
	};
}