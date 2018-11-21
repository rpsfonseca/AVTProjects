#include "node.h"
#include "Material.h"
#include "Entity.h"

#define NODE_TAG "Scene SceneNode"

#include <glm/gtx/quaternion.hpp>

namespace AVTEngine
{
	
	SceneNode::SceneNode()
	{
		parentNode = NULL;
		transform = glm::mat4(1);
		position = glm::vec3(0.0);
		rotation = glm::quat();
		scale = glm::vec3(1, 1, 1);

		mirrorScale = glm::vec3(1, -1, 1);

		dirty = false;
	}


	SceneNode::SceneNode(std::string _name, Mesh* _mesh, Material* _material)
	{
		nodeName = _name;
		mesh = _mesh;
		material = _material;

		transform = glm::mat4(1);
		position = glm::vec3(0.0);
		rotation = glm::quat();
		scale = glm::vec3(1, 1, 1);
		mirrorScale = glm::vec3(1, -1, 1);

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
		mirrorScale = glm::vec3(1, -1, 1);

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

	void SceneNode::enable()
	{
		isEnabled = true;
	}

	void SceneNode::disable()
	{
		isEnabled = false;
	}

	void SceneNode::setShader(Shader *shader_)
	{
		nodeShader = shader_;
	}

	glm::mat4 SceneNode::getTransform()
	{
		return transform;
	}

	glm::mat4 SceneNode::getMirrorTransform()
	{
		if (nodeName == "tree")
		{
			mirrorTransform = glm::translate(getTransform(), glm::vec3(0, -2, 0)); //Move reflection downwards
		}
		else if (nodeName == "butter")
		{
			mirrorTransform = glm::translate(getTransform(), glm::vec3(0, -1.5, 0)); //Move reflection downwards
		}
		else
		{
			mirrorTransform = glm::translate(getTransform(), glm::vec3(0, -1, 0)); //Move reflection downwards
		}
		mirrorTransform = glm::scale(mirrorTransform, mirrorScale); //Invert Y axis
		return mirrorTransform;
	}

	void SceneNode::updateTransform()
	{
		
		// we only do this if the node itself or its parent is flagged as dirty
		if (dirty)
		{
			transform = glm::mat4(1);
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
		node->parentNode = this;
		childNodes.push_back(node);
	}

	void SceneNode::setPosition(glm::vec3 _position)
	{
		position = _position;
		dirty = true;
	}

	void SceneNode::setRotation(glm::quat _rotation)
	{
		rotation = _rotation;
		dirty = true;
	}

	void SceneNode::setScale(glm::vec3 _scale)
	{
		scale = _scale;
		dirty = true;
	}

	//Should object be reflected?
	void SceneNode::setMirrored(bool _mirrored)
	{
		mirrored = _mirrored;
		dirty = true;
	}

	void SceneNode::addUniformi(std::string key_, int value_)
	{
		uniformiArray.push_back(key_);
	}

	void SceneNode::setUniformi(std::string key_, int value_)
	{

	}
}