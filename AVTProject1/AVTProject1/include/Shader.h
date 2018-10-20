#pragma once

#include "ShadingTypes.h"

#include "GL\glew.h"

#include "glm\glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace AVTEngine
{
	class Shader
	{
	private:
		std::string mName;

		std::vector<Uniform> uniforms;

	public:
		Shader();
		Shader(const GLchar* vertexSource, const GLchar* fragmentSource);
		~Shader();


		Shader& use();
		void deleteProgram();

		void setName(std::string name) { mName = name; }

		void setInteger(const GLchar* field, GLint value);
		void setFloat(const GLchar* field, GLfloat value);
		void setMat4(const GLchar* field, const glm::mat4& matrix);
		void setVec2(const GLchar* field, const glm::vec2& vector);
		void setVec3(const GLchar* field, const glm::vec3& vector);
		void setVec4(const GLchar* field, const glm::vec4& vector);

		void printCompileErrors(int vOrF, GLuint shader, GLchar* infoLog);
		void printLinkingErrors(GLchar* infoLog);
		GLuint shaderID;

		GLuint uniformBlockBinding();

	private:
		void compile(const GLchar* vsCode, const GLchar* fsCode);

		void fillAttributesAndUniforms();
	};
}