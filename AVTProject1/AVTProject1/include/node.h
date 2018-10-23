#pragma once

#include "Material.h"
#include "Shader.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

/* TODO uncomment
#include "graphics\material.hpp"
#include "graphics\texture.hpp"
#include "graphics\mesh.hpp"
#include "graphics\globalLight.hpp"
#include "graphics\camera\camera.hpp"
*/

namespace AVTEngine
{

	struct NodeTexture
	{
		std::string key;
		//Texture *texture; TODO uncomment
	};

	class Mesh;
	class Material;
	class Entity;

	/**
	*	A scene graph node. Can have it's shader, mesh and modelMatrix. Houses child nodes.
	*/
	class SceneNode
	{
	public:
		bool dirty = false;

		SceneNode* parentNode;
		std::vector<SceneNode*> childNodes;

		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;
		glm::mat4 transform;

		Mesh* mesh;
		Material* material;
		Entity* entity;

		std::vector<NodeTexture> textureArray;
		std::vector<std::string> uniformiArray;
		//std::map<std::string, int> uniformiMap;
		bool isEnabled = true;

		

	protected:
		Shader* nodeShader;
		glm::mat4 resultMatrix;

	public:
		//TODO uncomment
		SceneNode(Mesh* mesh, Material* material);
		SceneNode(Entity* entity, Mesh* mesh, Material* material);
		//SceneNode(Mesh *mesh);
		SceneNode();
		
		void addChild(SceneNode *node_);
		
		//void addTexture(std::string key_, Texture *texture_); TODO uncomment
		void addUniformi(std::string key_, int value_);
		void setUniformi(std::string key_, int value_);

		void enable();
		void disable();

		//void setMesh(Mesh *mesh_); //TODO uncomment
		void setShader(Shader *shader_);
		//void setMaterial(Material *material_); //TODO uncomment

		glm::mat4 getTransform();

		inline int getChildCount() { return childNodes.size(); };
		inline SceneNode* getChildByIndex(int i) { return childNodes[i]; };

		void updateTransform();

		void cleanup();

		//Transformation functions
		void setPosition(glm::vec3 _position);
		void setRotation(glm::quat _rotation);
		void setScale(glm::vec3 _scale);


	private:
		

		Shader *getCurrentShader(SceneNode *parent_);

		//TODO uncomment
		//Material *getCurrentMaterial(SceneNode *parent_);
		//void drawSelf(Shader *shader_, Material *material_);
	};
}

