
//#include "utils\error.hpp"
#include "node.h"
#include "Material.h"

#define NODE_TAG "Scene SceneNode"

#include <glm/gtx/quaternion.hpp>

namespace AVTEngine
{
	/* TODO uncomment
	SceneNode::SceneNode(Mesh *mesh_, Shader *shader_) :
		nodeMesh(mesh_), nodeShader(shader_) {};

	SceneNode::SceneNode(Mesh *mesh_) : SceneNode(mesh_, nullptr) {}

	SceneNode::SceneNode(Shader *shader_) : SceneNode(nullptr, shader_) {}
	*/

	SceneNode::SceneNode()
	{
		parentNode = NULL;
		transform = glm::mat4(1);
		position = glm::vec3(0.0);
		rotation = glm::quat();
		scale = glm::vec3(1, 1, 1);
		dirty = false;
	}


	SceneNode::SceneNode(Mesh* _mesh, Material* _material)
	{
		mesh = _mesh;
		material = _material;

		transform = glm::mat4(1);
		position = glm::vec3(0.0);
		rotation = glm::quat();
		scale = glm::vec3(1, 1, 1);

		dirty = false;
	}

	SceneNode::SceneNode(Entity* _entity, Mesh* _mesh, Material* _material)
	{
		//passar para o mesh
		entity = _entity;
		entity->setMesh(_mesh);
		entity->setMaterial(_material);

		transform = glm::mat4(1);
		position = glm::vec3(0.0);
		rotation = glm::quat();
		scale = glm::vec3(1, 1, 1);

		dirty = false;
	}
	
	
	Shader *SceneNode::getCurrentShader(SceneNode *parent_)
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
	Material *SceneNode::getCurrentMaterial(SceneNode *parent_)
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
	void SceneNode::drawSelf(ShaderProgram *shader_, Material *material_)
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
	
	/* TODO uncomment
	void SceneNode::addTexture(std::string key_, Texture *texture_)
	{
		textureArray.push_back(NodeTexture{ key_, texture_ });
	}
	*/

	void SceneNode::enable()
	{
		isEnabled = true;
	}

	void SceneNode::disable()
	{
		isEnabled = false;
	}

	/* TODO Uncomment
	void SceneNode::setMesh(Mesh *mesh_)
	{
		nodeMesh = mesh_;
	}
	*/

	void SceneNode::setShader(Shader *shader_)
	{
		nodeShader = shader_;
	}

	/* TODO uncomment
	void SceneNode::setMaterial(Material *material_)
	{
		material = material_;
	}
	*/

	glm::mat4 SceneNode::getTransform()
	{
		return transform;
	}

	void SceneNode::updateTransform()
	{
		// we only do this if the node itself or its parent is flagged as dirty
		if (dirty)
		{
			// first scale, then rotate, then translation
			transform = glm::translate(transform, position);
			transform = glm::scale(transform, scale); // TODO: order is off here for some reason, figure out why
			transform = transform * glm::toMat4(rotation);

			if (parentNode)
			{
				transform = parentNode->transform * transform;
			}
		}
		for (int i = 0; i < childNodes.size(); ++i)
		{
			if (dirty)
			{
				childNodes[i]->dirty = true;
			}
			childNodes[i]->updateTransform();
		}
		dirty = false;
	}

	void SceneNode::cleanup()
	{
		delete mesh;
		delete material;
	}

	void SceneNode::addChild(SceneNode* node)
	{
		/*if (node->parentNode != NULL)
		{
			node->parentNode->removeChild(node->nodeId);
		}*/

		node->parentNode = this;
		childNodes.push_back(node);
	}

	void SceneNode::setPosition(glm::vec3 _position)
	{
		position = _position;
		dirty = true;
	}


	void SceneNode::addUniformi(std::string key_, int value_)
	{
		//uniformiMap[key_] = value_;
		uniformiArray.push_back(key_);
	}

	void SceneNode::setUniformi(std::string key_, int value_)
	{
		//uniformiMap[key_] = value_;
	}
}