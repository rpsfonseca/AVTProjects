#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <Shader.h>

/* TODO uncomment
#include "graphics\material.hpp"
#include "graphics\texture.hpp"
#include "graphics\mesh.hpp"
#include "graphics\globalLight.hpp"
#include "graphics\camera\camera.hpp"
*/

namespace AVTEngine
{
	/**
	*	Contains Global Scene Data.
	*/
	struct Environment
	{
		//TODO uncomment
		//Camera *camera;
		//GlobalLight *globalLight;
	};

	struct NodeTexture
	{
		std::string key;
		//Texture *texture; TODO uncomment
	};

	/**
	*	A scene graph node. Can have it's shader, mesh and modelMatrix. Houses child nodes.
	*/
	class Node
	{
	public:
		//TODO uncomment
		//Node(Mesh *mesh, ShaderProgram *shader_);
		//Node(Mesh *mesh);
		Node(Shader *shader_);
		Node() = default;

		void draw(Node *parentNode_);

		// Transformations
		void rotate(float angle_, const glm::vec3 &axis_);
		void translate(float x_, float y_, float z_);
		void scale(float x_, float y_, float z_);

		void addNode(Node *node_);
		//void addTexture(std::string key_, Texture *texture_); TODO uncomment
		void addUniformi(std::string key_, int value_);
		void setUniformi(std::string key_, int value_);

		void enable();
		void disable();

		//void setMesh(Mesh *mesh_); //TODO uncomment
		void setShader(Shader *shader_);
		//void setMaterial(Material *material_); //TODO uncomment
		glm::mat4 getModelMatrix();

	protected:
		Shader *nodeShader;
		glm::mat4 resultMatrix;
		std::vector<Node*> nodeArray;
		Environment *environment;

	private:
		glm::mat4 modelMatrix = glm::mat4(1.0); //Identity Matrix

		//TODO uncomment
		//Mesh *nodeMesh;
		//Material *material;

		std::vector<NodeTexture> textureArray;
		std::vector<std::string> uniformiArray;
		//std::map<std::string, int> uniformiMap;
		bool isEnabled = true;

		Shader *getCurrentShader(Node *parent_);

		//TODO uncomment
		//Material *getCurrentMaterial(Node *parent_);
		//void drawSelf(Shader *shader_, Material *material_);
	};
}

