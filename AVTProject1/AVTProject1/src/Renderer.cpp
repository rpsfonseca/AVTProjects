#include "Renderer.h"
#include "Mesh.h"
#include "RenderCommand.h"
#include "CommandBuffer.h"
#include "Material.h"
#include "Camera.h"
#include "node.h"
#include "MaterialLibrary.h"
#include "OpenGLError.h"
#include "Application.h"
#include "scene.h"

#include <glm/ext.hpp>

#include "GL\glew.h"

#include <ctime>
#include <stack>
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
		materialLibrary = new MaterialLibrary();
	}

	Renderer::~Renderer()
	{
		//delete commandBuffer;
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

	void Renderer::pushRenderables(SceneNode* sceneNode)
	{
		//TODO update entity here?

		// update transform(s) before pushing node to render command buffer
		sceneNode->updateTransform();

		// traverse through all the scene nodes and for each node: push its render state to the 
		// command buffer together with a calculated transform matrix.
		std::stack<SceneNode*> nodeStack;
		nodeStack.push(sceneNode);
		for (int i = 0; i < sceneNode->getChildCount(); ++i)
		{
			nodeStack.push(sceneNode->getChildByIndex(i));
		}
		while (!nodeStack.empty())
		{
			SceneNode* node = nodeStack.top();
			nodeStack.pop();
			// only push render command if the child isn't a container node.
			if (node->mesh)
			{
				commandBuffer->pushCommand(node->mesh, node->material, node->getTransform());
			}

			for (int i = 0; i < node->getChildCount(); ++i)
			{
				nodeStack.push(node->getChildByIndex(i));
			}
		}
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
			renderCommand(&renderCommands[i], currentCamera);
		}

		commandBuffer->clear();

		OpenGLError::checkOpenGLError("ERROR: Could not draw scene.");
	}

	// As the name implies, it runs after the draw method.
	// For now it just unbinds the shader program and the vertex array.
	void Renderer::postDraw()
	{
		glUseProgram(0);
		glBindVertexArray(0);
	}

	void Renderer::cleanup()
	{
		delete commandBuffer;
	}

	void Renderer::setProjectionMatrix(const glm::mat4& mat)
	{
		projectionMatrix = mat;

		//std::cout << "PROJECTION: " << glm::to_string(projectionMatrix) << std::endl;
	}

	void Renderer::setViewMatrix(const glm::mat4& mat)
	{
		viewMatrix = mat;

		//std::cout << "VIEW: " << glm::to_string(viewMatrix) << std::endl;
	}

	Material* Renderer::getMaterial(std::string matName)
	{
		return materialLibrary->defaultMaterials[matName];
	}

	void Renderer::renderCommand(RenderCommand* command, Camera* camera)
	{
		Material* material = command->material;
		Mesh* mesh = command->mesh;

		material->getShader()->use();

		// bind/active uniform sampler/texture objects
		auto* samplers = material->getSamplerUniforms();
		for (auto it = samplers->begin(); it != samplers->end(); ++it)
		{
			it->second.texture->bind(it->second.unit);
		}

		//material->getShader()->setInteger("lightwood", 0);

		// setup lights
		material->getShader()->setBool("dirLightEnabled", directionalLightOn);
		material->getShader()->setBool("pointLightsEnabled", pointLightsOn);
		material->getShader()->setBool("spotLightsEnabled", spotLightsOn);


		// setup view for light calculations
		if (camera != nullptr)
		{
			material->getShader()->setVec3("viewPos", camera->getPosition());
		}

		// setup material properties
		material->getShader()->setVec3("material.diffuse", material->getDiffuse());
		material->getShader()->setVec3("material.ambient", material->getAmbient());
		material->getShader()->setVec3("material.specular", material->getSpecular());
		material->getShader()->setFloat("material.shininess", material->getShininess());

		//if (material->getMaterialName() != "table")
		//{
			// setup lights
			glm::vec3 pointLightPositions[] = {
				glm::vec3(0.7f,  0.2f,  2.0f),
				glm::vec3(2.3f, -3.3f, -4.0f),
				glm::vec3(-4.0f,  2.0f, -12.0f),
				glm::vec3(0.0f,  0.0f, -3.0f),
				glm::vec3(5.0f,  3.0f, -7.0f),
				glm::vec3(-3.0f,  1.0f, -2.0f)
			};

			// point light 1
			material->getShader()->setVec3("pointLights[0].position", pointLightPositions[0]);
			material->getShader()->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
			material->getShader()->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
			material->getShader()->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
			material->getShader()->setFloat("pointLights[0].constant", 1.0f);
			material->getShader()->setFloat("pointLights[0].linear", 0.09);
			material->getShader()->setFloat("pointLights[0].quadratic", 0.032);
			// point light 2
			material->getShader()->setVec3("pointLights[1].position", pointLightPositions[1]);
			material->getShader()->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
			material->getShader()->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
			material->getShader()->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
			material->getShader()->setFloat("pointLights[1].constant", 1.0f);
			material->getShader()->setFloat("pointLights[1].linear", 0.09);
			material->getShader()->setFloat("pointLights[1].quadratic", 0.032);
			// point light 3
			material->getShader()->setVec3("pointLights[2].position", pointLightPositions[2]);
			material->getShader()->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
			material->getShader()->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
			material->getShader()->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
			material->getShader()->setFloat("pointLights[2].constant", 1.0f);
			material->getShader()->setFloat("pointLights[2].linear", 0.09);
			material->getShader()->setFloat("pointLights[2].quadratic", 0.032);
			// point light 4
			material->getShader()->setVec3("pointLights[3].position", pointLightPositions[3]);
			material->getShader()->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
			material->getShader()->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
			material->getShader()->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
			material->getShader()->setFloat("pointLights[3].constant", 1.0f);
			material->getShader()->setFloat("pointLights[3].linear", 0.09);
			material->getShader()->setFloat("pointLights[3].quadratic", 0.032);
			// point light 5
			material->getShader()->setVec3("pointLights[4].position", pointLightPositions[4]);
			material->getShader()->setVec3("pointLights[4].ambient", 0.05f, 0.05f, 0.05f);
			material->getShader()->setVec3("pointLights[4].diffuse", 0.8f, 0.8f, 0.8f);
			material->getShader()->setVec3("pointLights[4].specular", 1.0f, 1.0f, 1.0f);
			material->getShader()->setFloat("pointLights[4].constant", 1.0f);
			material->getShader()->setFloat("pointLights[4].linear", 0.09);
			material->getShader()->setFloat("pointLights[4].quadratic", 0.032);
			// point light 6
			material->getShader()->setVec3("pointLights[5].position", pointLightPositions[5]);
			material->getShader()->setVec3("pointLights[5].ambient", 0.05f, 0.05f, 0.05f);
			material->getShader()->setVec3("pointLights[5].diffuse", 0.8f, 0.8f, 0.8f);
			material->getShader()->setVec3("pointLights[5].specular", 1.0f, 1.0f, 1.0f);
			material->getShader()->setFloat("pointLights[5].constant", 1.0f);
			material->getShader()->setFloat("pointLights[5].linear", 0.09);
			material->getShader()->setFloat("pointLights[5].quadratic", 0.032);
			// spotLight
			//material->getShader()->setVec3("spotLight.position", glm::vec3(0));
			//material->getShader()->setVec3("spotLight.direction", glm::fastNormalize(glm::vec3(1)));
			//material->getShader()->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
			//material->getShader()->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
			//material->getShader()->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
			//material->getShader()->setFloat("spotLight.constant", 1.0f);
			//material->getShader()->setFloat("spotLight.linear", 0.09);
			//material->getShader()->setFloat("spotLight.quadratic", 0.032);
			//material->getShader()->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
			//material->getShader()->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
			//// spotLight 2
			//material->getShader()->setVec3("spotLight2.position", glm::vec3(0));
			//material->getShader()->setVec3("spotLight2.direction", glm::fastNormalize(glm::vec3(1)));
			//material->getShader()->setVec3("spotLight2.ambient", 0.0f, 0.0f, 0.0f);
			//material->getShader()->setVec3("spotLight2.diffuse", 1.0f, 1.0f, 1.0f);
			//material->getShader()->setVec3("spotLight2.specular", 1.0f, 1.0f, 1.0f);
			//material->getShader()->setFloat("spotLight2.constant", 1.0f);
			//material->getShader()->setFloat("spotLight2.linear", 0.09);
			//material->getShader()->setFloat("spotLight2.quadratic", 0.032);
			//material->getShader()->setFloat("spotLight2.cutOff", glm::cos(glm::radians(12.5f)));
			//material->getShader()->setFloat("spotLight2.outerCutOff", glm::cos(glm::radians(15.0f)));
		//}

		material->getShader()->setVec3("dirLight.direction", 0.2f, -0.1f, 0.3f);
		material->getShader()->setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
		material->getShader()->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		material->getShader()->setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
		
		//if (material->getMaterialName() != "table")
		//{

			auto* car = Application::getInstance()->scene->getCar();
			auto orientationNormalized = car->getOrientation();

			// spotLight
			material->getShader()->setVec3("spotLight.position", car->getPosition() + glm::rotateY(orientationNormalized, 90.f) * 1.2f + glm::vec3(0, .5f, 0));
			material->getShader()->setVec3("spotLight.direction", glm::fastNormalize(car->getOrientation()));
			material->getShader()->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
			material->getShader()->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
			material->getShader()->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
			material->getShader()->setFloat("spotLight.constant", 1.0f);
			material->getShader()->setFloat("spotLight.linear", 0.09);
			material->getShader()->setFloat("spotLight.quadratic", 0.032);
			material->getShader()->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
			material->getShader()->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
			// spotLight 2
			material->getShader()->setVec3("spotLight2.position", car->getPosition() + glm::rotateY(orientationNormalized, -90.f) * 1.2f + glm::vec3(0, .5f, 0));
			material->getShader()->setVec3("spotLight2.direction", glm::fastNormalize(car->getOrientation()));
			material->getShader()->setVec3("spotLight2.ambient", 0.0f, 0.0f, 0.0f);
			material->getShader()->setVec3("spotLight2.diffuse", 1.0f, 1.0f, 1.0f);
			material->getShader()->setVec3("spotLight2.specular", 1.0f, 1.0f, 1.0f);
			material->getShader()->setFloat("spotLight2.constant", 1.0f);
			material->getShader()->setFloat("spotLight2.linear", 0.09);
			material->getShader()->setFloat("spotLight2.quadratic", 0.032);
			material->getShader()->setFloat("spotLight2.cutOff", glm::cos(glm::radians(12.5f)));
			material->getShader()->setFloat("spotLight2.outerCutOff", glm::cos(glm::radians(15.0f)));
		//}

		material->getShader()->setMat4("projectionMatrix", projectionMatrix);
		material->getShader()->setMat4("viewMatrix", viewMatrix);
		material->getShader()->setMat4("modelMatrix", command->transform);
		//material->getShader()->setMat4("modelMatrix", camera->getViewProjection());

		renderMesh(mesh);

		if (material->getMaterialName() == "table")
		{
			//materialLibrary->defaultMaterials[material->getMaterialName()]->getSamplerUnit("texmap1")->unbind();
			for (auto it = samplers->begin(); it != samplers->end(); ++it)
			{
				it->second.texture->unbind();
			}
		}
	}

	void Renderer::renderMesh(Mesh* mesh)
	{
		glBindVertexArray(mesh->getVao());
		if (mesh->usingIndices)
		{
			glDrawElements(mesh->topology == TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, mesh->getIndicesSize(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(mesh->topology == TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, 0, mesh->getVerticesSize());
		}
	}
}