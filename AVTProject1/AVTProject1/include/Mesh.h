#pragma once

#include <glm/glm.hpp>

#include "GL\glew.h"
#include <vector>

namespace AVTEngine
{
	enum TOPOLOGY
	{
		POINTS,
		LINES,
		LINE_STRIP,
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
	};

	class Mesh
	{
	public:
		bool usingIndices = true;
		bool hasNormals = false;
		bool hasTextures = false;
		TOPOLOGY topology = TRIANGLES;
		
		Mesh();
		Mesh(std::vector<glm::vec3> vertices);
		Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
		Mesh(std::vector<glm::vec3> _vertices, std::vector<glm::vec3> _normals, std::vector<glm::vec2> _uvs);
		Mesh(std::vector<glm::vec3> _vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> _uvs);
		~Mesh();

		unsigned int getVao();
		inline unsigned int getVbo();
		unsigned int getEbo();

		void setUbo(unsigned int uboId);

		int getIndicesSize();
		int getVerticesSize();
		int getNormalsSize();
		int getUVsSize();

		glm::vec3 getPosition();
		void setPosition(glm::vec3& pos);

		float getRotation();
		void setRotation(float angle);

		glm::vec3 get3DRotation();
		void set3DRotation(glm::vec3 angle);

		glm::vec3 getScale();
		void setScale(glm::vec3& sc);

		glm::vec4 getColor();
		void setColor(glm::vec4& sc);

	protected:
		unsigned int vao, vbo, ebo, ubo;
		unsigned int vbos[3];
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<unsigned int> indices;

		glm::vec3 worldPosition;
		float worldRotation;
		glm::vec3 world3DRotation;
		glm::vec3 worldScale;

		glm::vec4 topColor;

		void setupMesh();
	};
}