#include "OBJLoader.h"

#include "Mesh.h"
#include "StringUtils.h"

#include <fstream>
#include <algorithm>
#include <map>
#include <iostream>

namespace AVTEngine
{
	static inline unsigned int parseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end);
	static inline float parseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end);

	OBJLoader::OBJLoader(std::string& filename)
	{
		/*std::ifstream file;
		file.open(filename);

		std::string line;
		if (file.is_open())
		{
			while (file.good())
			{
				std::getline(file, line);

				if (line.length() < 2)
				{
					continue;
				}

				const char* lineC;

				switch (line[0])
				{
				case 'v':
					if (line[1] == 't')
					{
						uvs.push_back(parseOBJVec2(line));
					}
					else if (line[1] == 'n')
					{
						normals.push_back(parseOBJVec3(line));
					}
					else if(line[1] == ' ' || line[1] == '\t')
					{
						vertices.push_back(parseOBJVec3(line));
					}
					break;
				case 'f':
					createOBJFace(line);
					break;
				default:
					break;
				}
			}
		}*/

		createMesh(filename);
	}


	OBJLoader::~OBJLoader()
	{
	}

	Mesh* OBJLoader::toMesh()
	{
		Mesh* result = new Mesh(vertices, normals, uvs);

		std::cout << "VERTICES SIZE: " << result->getVerticesSize() << std::endl;
		std::cout << "UVS SIZE: " << result->getUVsSize() << std::endl;
		if (result->getNormalsSize())
		{
			result->hasNormals = true;
		}
		if (result->getUVsSize())
		{
			result->hasTextures = true;
		}

		/*if (!hasNormals)
		{
			normalModel.calcNormals();

			for (unsigned int i = 0; i < result.positions.size(); i++)
			{
				result.normals[i] = normalModel.normals[indexMap[i]];
			}
		}*/

		return result;
	}

	/*unsigned int OBJLoader::findLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const Model& result)
	{
		unsigned int start = 0;
		unsigned int end = indexLookup.size();
		unsigned int current = (end - start) / 2 + start;
		unsigned int previous = start;

		while (current != previous)
		{
			OBJIndex* testIndex = indexLookup[current];

			if (testIndex->vertexIndex == currentIndex->vertexIndex)
			{
				unsigned int countStart = current;

				for (unsigned int i = 0; i < current; i++)
				{
					OBJIndex* possibleIndex = indexLookup[current - i];

					if (possibleIndex == currentIndex)
					{
						continue;
					}

					if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
					{
						break;
					}

					countStart--;
				}

				for (unsigned int i = countStart; i < indexLookup.size() - countStart; i++)
				{
					OBJIndex* possibleIndex = indexLookup[current + i];

					if (possibleIndex == currentIndex)
					{
						continue;
					}

					if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
					{
						break;
					}
					else if ((!hasUVs || possibleIndex->uvIndex == currentIndex->uvIndex) && (!hasNormals || possibleIndex->normalIndex == currentIndex->normalIndex))
					{
						glm::vec3 currentPosition = vertices[currentIndex->vertexIndex];
						glm::vec2 currentTexCoord;
						glm::vec3 currentNormal;

						if (hasUVs)
						{
							currentTexCoord = uvs[currentIndex->uvIndex];
						}
						else
						{
							currentTexCoord = glm::vec2(0.0f);
						}

						if (hasNormals)
						{
							currentNormal = normals[currentIndex->normalIndex];
						}
						else
						{
							currentNormal = glm::vec3(0.0f);
						}

						for (unsigned int j = 0; j < result.positions.size(); j++)
						{
							if (currentPosition == result.positions[j] && ((!hasUVs || currentTexCoord == result.texCoords[j]) && (!hasNormals || currentNormal == result.normals[j])))
							{
								return j;
							}
						}
					}
				}

				return -1;
			}
			else
			{
				if (testIndex->vertexIndex < currentIndex->vertexIndex)
				{
					start = current;
				}
				else
				{
					end = current;
				}
			}

			previous = current;
			current = (end - start) / 2 + start;
		}

		return -1;
	}*/

	void OBJLoader::createOBJFace(const std::string& line)
	{
		std::vector<std::string> tokens = splitString(line, ' ');

		objIndices.push_back(parseOBJIndex(tokens[1], hasUVs, hasNormals));
		objIndices.push_back(parseOBJIndex(tokens[2], hasUVs, hasNormals));
		objIndices.push_back(parseOBJIndex(tokens[3], hasUVs, hasNormals));

		if (tokens.size() > 4)
		{
			objIndices.push_back(parseOBJIndex(tokens[1], hasUVs, hasNormals));
			objIndices.push_back(parseOBJIndex(tokens[3], hasUVs, hasNormals));
			objIndices.push_back(parseOBJIndex(tokens[4], hasUVs, hasNormals));
		}
	}

	bool OBJLoader::compareOBJIndexPtr(const OBJIndex* a, const OBJIndex* b)
	{
		return a->vertexIndex < b->vertexIndex;
	}

	OBJIndex OBJLoader::parseOBJIndex(const std::string& token, bool& hasUVs, bool& hasNormals)
	{
		unsigned int tokenLength = token.length();

		unsigned int vertexIndexStart = 0;
		unsigned int vertexIndexEnd = findNextChar(vertexIndexStart, token, tokenLength, '/');

		OBJIndex result;
		result.vertexIndex = parseOBJIndexValue(token, vertexIndexStart, vertexIndexEnd);
		result.uvIndex = 0;
		result.normalIndex = 0;

		if (vertexIndexEnd >= tokenLength)
		{
			return result;
		}

		if (token[2] != '/')
		{
			vertexIndexStart = vertexIndexEnd + 1;
			vertexIndexEnd = findNextChar(vertexIndexStart, token, tokenLength, '/');

			result.uvIndex = parseOBJIndexValue(token, vertexIndexStart, vertexIndexEnd);
			hasUVs = true;

			if (vertexIndexEnd >= tokenLength)
			{
				return result;
			}

			vertexIndexStart = vertexIndexEnd + 1;
			vertexIndexEnd = findNextChar(vertexIndexStart, token, tokenLength, '/');
		}
		else
		{
			vertexIndexStart = vertexIndexEnd + 2;
			vertexIndexEnd = findNextChar(vertexIndexStart, token, tokenLength, '/');
		}

		result.normalIndex = parseOBJIndexValue(token, vertexIndexStart, vertexIndexEnd);
		hasNormals = true;

		return result;
	}

	glm::vec2 OBJLoader::parseOBJVec2(const std::string & line)
	{
		unsigned int tokenLength = line.length();

		unsigned int vertexIndexStart = 3;

		while (vertexIndexStart < tokenLength)
		{
			if (line[vertexIndexStart] != ' ')
			{
				break;
			}
			vertexIndexStart++;
		}

		unsigned int vertexIndexEnd = findNextChar(vertexIndexStart, line, tokenLength, ' ');

		float x = parseOBJFloatValue(line, vertexIndexStart, vertexIndexEnd);

		vertexIndexStart = vertexIndexEnd + 1;
		vertexIndexEnd = findNextChar(vertexIndexStart, line, tokenLength, ' ');

		float y = parseOBJFloatValue(line, vertexIndexStart, vertexIndexEnd);

		return glm::vec2(x, y);
	}

	glm::vec3 OBJLoader::parseOBJVec3(const std::string& line)
	{
		unsigned int tokenLength = line.length();

		unsigned int vertexIndexStart = 2;

		while (vertexIndexStart < tokenLength)
		{
			if (line[vertexIndexStart] != ' ')
			{
				break;
			}
			vertexIndexStart++;
		}

		unsigned int vertexIndexEnd = findNextChar(vertexIndexStart, line, tokenLength, ' ');

		float x = parseOBJFloatValue(line, vertexIndexStart, vertexIndexEnd);

		vertexIndexStart = vertexIndexEnd + 1;
		vertexIndexEnd = findNextChar(vertexIndexStart, line, tokenLength, ' ');

		float y = parseOBJFloatValue(line, vertexIndexStart, vertexIndexEnd);

		vertexIndexStart = vertexIndexEnd + 1;
		vertexIndexEnd = findNextChar(vertexIndexStart, line, tokenLength, ' ');

		float z = parseOBJFloatValue(line, vertexIndexStart, vertexIndexEnd);

		return glm::vec3(x, y, z);
	}

	static inline unsigned int parseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end)
	{
		return atoi(token.substr(start, end - start).c_str()) - 1;
	}

	static inline float parseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end)
	{
		return atof(token.substr(start, end - start).c_str()) - 1;
	}

	void OBJLoader::parseVertex(std::stringstream& sin)
	{
		glm::vec3 v;
		sin >> v.x >> v.y >> v.z;
		vertexData.push_back(v);
	}

	void OBJLoader::parseTexcoord(std::stringstream& sin)
	{
		glm::vec2 t;
		sin >> t.x >> t.y;
		texcoordData.push_back(t);
	}

	void OBJLoader::parseNormal(std::stringstream& sin)
	{
		glm::vec3 n;
		sin >> n.x >> n.y >> n.z;
		normalData.push_back(n);
	}

	void OBJLoader::parseFace(std::stringstream& sin)
	{
		std::string token;
		for (int i = 0; i < 3; i++) {
			std::getline(sin, token, '/');
			if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
			std::getline(sin, token, '/');
			if (token.size() > 0) texcoordIdx.push_back(std::stoi(token));
			std::getline(sin, token, ' ');
			if (token.size() > 0) normalIdx.push_back(std::stoi(token));
		}
	}

	void OBJLoader::parseLine(std::stringstream& sin)
	{
		std::string s;
		sin >> s;
		if (s.compare("v") == 0) parseVertex(sin);
		else if (s.compare("vt") == 0) parseTexcoord(sin);
		else if (s.compare("vn") == 0) parseNormal(sin);
		else if (s.compare("f") == 0) parseFace(sin);
	}

	void OBJLoader::loadMeshData(std::string& filename)
	{
		std::ifstream ifile(filename);
		std::string line;
		std::stringstream streamLine;
		while (std::getline(ifile, line))
		{
			streamLine = std::stringstream(line);
			parseLine(streamLine);
		}
		hasUVs = (texcoordIdx.size() > 0);
		hasNormals = (normalIdx.size() > 0);
	}

	void OBJLoader::processMeshData()
	{
		for (unsigned int i = 0; i < vertexIdx.size(); i++)
		{
			unsigned int vi = vertexIdx[i];
			glm::vec3 v = vertexData[vi - 1];
			vertices.push_back(v);
			if (hasUVs) {
				unsigned int ti = texcoordIdx[i];
				glm::vec2 t = texcoordData[ti - 1];
				uvs.push_back(t);
			}
			if (hasNormals) {
				unsigned int ni = normalIdx[i];
				glm::vec3 n = normalData[ni - 1];
				normals.push_back(n);
			}
		}
	}

	void OBJLoader::freeMeshData()
	{
		vertexData.clear();
		texcoordData.clear();
		normalData.clear();
		vertexIdx.clear();
		texcoordIdx.clear();
		normalIdx.clear();
	}

	const void OBJLoader::createMesh(std::string& filename)
	{
		loadMeshData(filename);
		processMeshData();
		freeMeshData();
	}

}