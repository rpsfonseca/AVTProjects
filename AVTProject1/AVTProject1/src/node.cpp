
//#include "utils\error.hpp"
#include "node.h"

#define NODE_TAG "Scene Node"

namespace AVTEngine
{
	/* TODO uncomment
	Node::Node(Mesh *mesh_, Shader *shader_) :
		nodeMesh(mesh_), nodeShader(shader_) {};

	Node::Node(Mesh *mesh_) : Node(mesh_, nullptr) {}

	Node::Node(Shader *shader_) : Node(nullptr, shader_) {}
	*/
	

	/* Handles draw order and result matrices */
	void Node::draw(Node *parentNode_)
	{
		if (!isEnabled)
		{
			return;
		}

		resultMatrix = parentNode_->resultMatrix * modelMatrix;


		Shader *currentShader = nullptr;
		//Material *currentMaterial = nullptr; TODO uncomment

		currentShader = getCurrentShader(parentNode_);
		//currentMaterial = getCurrentMaterial(parentNode_); TODO uncomment

		//drawSelf(currentShader, currentMaterial); TODO uncomment

		// Draw Child
		for (Node *n : nodeArray)
		{
			n->draw(this);
		}

		// Reset Parent Shader
		if (nodeShader != nullptr && parentNode_->nodeShader != nullptr)
		{
			/* 
			nodeShader->unbind();
			parentNode_->nodeShader->bind();

				TODO o shader é suposto ter 2 métodos bind e unbind, que fazem o seguinte:

				void ShaderProgram::bind()
				{
					glUseProgram(id);
				}

				void ShaderProgram::unbind()
				{
					glUseProgram(0);
				}

			*/
		}
	}

	Shader *Node::getCurrentShader(Node *parent_)
	{
		// If node has a shader
		if (nodeShader != nullptr)
		{
			return nodeShader;
		}
		else
		{
			return parent_->nodeShader;
		}
	}

	/* TODO uncomment
	Material *Node::getCurrentMaterial(Node *parent_)
	{
		// If node has a material
		if (material != nullptr)
		{
			return material;
		}
		else
		{
			return parent_->material;
		}
	}
	*/

	/* TODO uncomment
	void Node::drawSelf(ShaderProgram *shader_, Material *material_)
	{
		for (auto t : textureArray)
		{
			shader_->setTexture(t.key, t.texture);
		}

		if (nodeMesh != nullptr)
		{
			if (shader_ == nullptr)
			{
				logError(NODE_TAG, "No shader bound to node on mesh draw.");
			}
			if (material_ == nullptr)
			{
				logError(NODE_TAG, "No material bound to node on mesh draw");
			}

			shader_->bind();
			shader_->setMatrix4(SHADER_MODEL_MATRIX, resultMatrix);
			material_->updateUniforms(shader_);
			environment->camera->updateUniforms(shader_);
			environment->globalLight->updateUniforms(shader_, environment->camera);

			// Update integer uniforms
			for (auto key : uniformiArray)
			{
				shader_->setInteger(key, uniformiMap[key]);
			}

			nodeMesh->draw();
		}

		for (auto t : textureArray)
		{
			t.texture->unbind();
		}
	}
	*/

	void Node::rotate(float angle_, const glm::vec3 &axis_)
	{
		modelMatrix = glm::rotate(modelMatrix, angle_, axis_);
	}

	void Node::translate(float x_, float y_, float z_)
	{
		modelMatrix = glm::translate(modelMatrix, glm::vec3(x_, y_, z_));
	}

	void Node::scale(float x_, float y_, float z_)
	{
		modelMatrix = glm::scale(modelMatrix, glm::vec3(x_, y_, z_));
	}

	void Node::addNode(Node *node_)
	{
		node_->environment = environment;
		nodeArray.push_back(node_);
	}
	
	/* TODO uncomment
	void Node::addTexture(std::string key_, Texture *texture_)
	{
		textureArray.push_back(NodeTexture{ key_, texture_ });
	}
	*/

	void Node::enable()
	{
		isEnabled = true;
	}

	void Node::disable()
	{
		isEnabled = false;
	}

	/* TODO Uncomment
	void Node::setMesh(Mesh *mesh_)
	{
		nodeMesh = mesh_;
	}
	*/

	void Node::setShader(Shader *shader_)
	{
		nodeShader = shader_;
	}

	/* TODO uncomment
	void Node::setMaterial(Material *material_)
	{
		material = material_;
	}
	*/

	glm::mat4 Node::getModelMatrix()
	{
		return modelMatrix;
	}

	void Node::addUniformi(std::string key_, int value_)
	{
		//uniformiMap[key_] = value_;
		uniformiArray.push_back(key_);
	}

	void Node::setUniformi(std::string key_, int value_)
	{
		//uniformiMap[key_] = value_;
	}
}