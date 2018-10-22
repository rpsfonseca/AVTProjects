#pragma once

#include "Model.h"

#include <glm/glm.hpp>

#include <vector>
#include <sstream>
#include <string>

namespace AVTEngine
{
	struct OBJIndex
	{
		unsigned int vertexIndex;
		unsigned int uvIndex;
		unsigned int normalIndex;

		bool operator<(const OBJIndex& right) const { return vertexIndex < right.vertexIndex; };
	};

	class Mesh;

	class OBJLoader
	{

	public:
		bool hasUVs = false;
		bool hasNormals = false;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;

		std::vector<glm::vec3> vertexData;
		std::vector<glm::vec2> texcoordData;
		std::vector<glm::vec3> normalData;

		std::vector <unsigned int> vertexIdx, texcoordIdx, normalIdx;
	public:
		OBJLoader(std::string& filename);
		~OBJLoader();

		Mesh* toMesh();

		void parseVertex(std::stringstream& sin);

		void parseTexcoord(std::stringstream& sin);

		void parseNormal(std::stringstream& sin);

		void parseFace(std::stringstream& sin);

		void parseLine(std::stringstream& sin);

		void loadMeshData(std::string& filename);

		void processMeshData();

		void freeMeshData();

		const void createMesh(std::string& filename);

	private:
		std::vector<OBJIndex> objIndices;
	private:
		void createOBJFace(const std::string& line);

		static bool compareOBJIndexPtr(const OBJIndex* a, const OBJIndex* b);

		OBJIndex parseOBJIndex(const std::string& token, bool &hasUVs, bool &hasNormals);
		glm::vec2 parseOBJVec2(const std::string& line);
		glm::vec3 parseOBJVec3(const std::string& line);
	};
}