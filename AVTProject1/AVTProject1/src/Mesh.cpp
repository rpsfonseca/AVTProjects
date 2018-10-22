#include "Mesh.h"
#include "GL\glew.h"

#include <iostream>
#include <sstream>

namespace AVTEngine
{
	Mesh::Mesh()
	{
	}

	Mesh::Mesh(std::vector<glm::vec3> _vertices)
		: vertices(_vertices)
	{
		worldPosition = glm::vec3(0);
		worldRotation = 0.0f;
		usingIndices = false;
		setupMesh();
	}

	Mesh::Mesh(std::vector<glm::vec3> _vertices, std::vector<unsigned int> _indices)
		: vertices(_vertices), indices(_indices)
	{
		worldPosition = glm::vec3(0);
		worldRotation = 0.0f;
		setupMesh();
	}

	Mesh::Mesh(std::vector<glm::vec3> _vertices, std::vector<glm::vec3> _normals, std::vector<glm::vec2> _uvs)
		: vertices(_vertices), normals(_normals), uvs(_uvs)
	{
		worldPosition = glm::vec3(0);
		worldRotation = 0.0f;
		usingIndices = false;
		setupMesh();
	}

	Mesh::~Mesh()
	{

	}

	void Mesh::setupMesh()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);

		if (usingIndices)
		{
			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	unsigned int Mesh::getVao()
	{
		return vao;
	}

	unsigned int Mesh::getVbo()
	{
		return vbo;
	}

	unsigned int Mesh::getEbo()
	{
		return ebo;
	}

	void Mesh::setUbo(unsigned int uboId)
	{
		ubo = uboId;
	}

	unsigned int Mesh::getIndicesSize()
	{
		return indices.size();
	}

	unsigned int Mesh::getVerticesSize()
	{
		return vertices.size();
	}

	unsigned int Mesh::getNormalsSize()
	{
		return normals.size();
	}

	unsigned int Mesh::getUVsSize()
	{
		return uvs.size();
	}

	glm::vec3 Mesh::getPosition()
	{
		return worldPosition;
	}

	void Mesh::setPosition(glm::vec3& pos)
	{
		worldPosition = glm::vec3(pos);
	}

	float Mesh::getRotation()
	{
		return worldRotation;
	}

	void Mesh::setRotation(float rot)
	{
		worldRotation = rot;
	}


	glm::vec3 Mesh::get3DRotation()
	{
		return world3DRotation;
	}

	void Mesh::set3DRotation(glm::vec3 angle)
	{
		world3DRotation = angle;
	}

	glm::vec3 Mesh::getScale()
	{
		return worldScale;
	}

	void Mesh::setScale(glm::vec3& sc)
	{
		worldScale = glm::vec3(sc);
	}


	glm::vec4 Mesh::getColor()
	{
		return topColor;
	}

	void Mesh::setColor(glm::vec4& sc)
	{
		topColor = glm::vec4(sc);
	}
}