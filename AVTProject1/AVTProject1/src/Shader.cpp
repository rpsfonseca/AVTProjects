#include "Shader.h"

namespace AVTEngine
{
	Shader::Shader() {}

	Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		std::string vertexSource;
		std::string fragmentSource;
		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		// Ensures ifstream objects can throw exceptions
		vertexShaderFile.exceptions(std::ifstream::badbit);
		vertexShaderFile.exceptions(std::ifstream::badbit);

		try
		{
			vertexShaderFile.open(vertexPath);
			fragmentShaderFile.open(fragmentPath);

			std::stringstream vertexShaderStream;
			std::stringstream fragmentShaderStream;
			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();

			vertexShaderFile.close();
			fragmentShaderFile.close();

			// Convert stream into GLchar array
			vertexSource = vertexShaderStream.str();
			fragmentSource = fragmentShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const GLchar* vertexShaderSource = vertexSource.c_str();
		const GLchar* fragmentShaderSource = fragmentSource.c_str();

		compile(vertexShaderSource, fragmentShaderSource);
	}


	Shader::~Shader()
	{
	}

	void Shader::compile(const GLchar* vsCode, const GLchar* fsCode)
	{
		GLuint vertex, fragment;
		GLchar infoLog[512];
		
		std::cout << vsCode << std::endl;
		std::cout << fsCode << std::endl;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vsCode, NULL);
		glCompileShader(vertex);
		printCompileErrors(0, vertex, infoLog);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fsCode, NULL);
		glCompileShader(fragment);
		printCompileErrors(1, fragment, infoLog);

		shaderID = glCreateProgram();
		glAttachShader(shaderID, vertex);
		glAttachShader(shaderID, fragment);
		glLinkProgram(shaderID);
		printLinkingErrors(infoLog);

		glDetachShader(shaderID, vertex);
		glDetachShader(shaderID, fragment);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Shader::fillAttributesAndUniforms()
	{
		//int nAttrib;
		int nUniform;
		//glGetProgramiv(shaderID, GL_ACTIVE_ATTRIBUTES, &nAttrib);
		glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &nUniform);

		//attributes.resize(nAttrib);
		uniforms.resize(nUniform);

		char buffer[128];
		/*for (int i = 0; i < nAttrib; i++)
		{
			GLenum glType;
			glGetActiveAttrib(shaderID, i, sizeof(buffer), 0, &attributes[i].size, &glType, buffer);

			attributes[i].name = std::string(buffer);
			//attributes[i].type = std::string(buffer);
			attributes[i].location = glGetAttribLocation(shaderID, buffer);
		}*/

		for (int i = 0; i < nUniform; i++)
		{
			GLenum glType;
			glGetActiveUniform(shaderID, i, sizeof(buffer), 0, &uniforms[i].size, &glType, buffer);

			uniforms[i].name = std::string(buffer);
			//uniforms[i].type = std::string(buffer);
			uniforms[i].location = glGetUniformLocation(shaderID, buffer);
		}
	}

	Shader& Shader::use()
	{
		glUseProgram(shaderID);
		return *this;
	}

	void Shader::deleteProgram()
	{
		glDeleteProgram(shaderID);
	}

	void Shader::setInteger(const GLchar* field, GLint value)
	{
		GLint loc = glGetUniformLocation(shaderID, field);
		glUniform1i(loc, value);
	}

	void Shader::setFloat(const GLchar* field, GLfloat value)
	{
		GLfloat loc = glGetUniformLocation(shaderID, field);
		glUniform1f(loc, value);
	}

	void Shader::setMat4(const GLchar* field, const glm::mat4& mat)
	{
		GLint loc = glGetUniformLocation(shaderID, field);
		glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::setVec2(const GLchar* field, const glm::vec2& vector)
	{
		GLint loc = glGetUniformLocation(shaderID, field);
		glUniform2f(loc, vector.x, vector.y);
	}

	void Shader::setVec3(const GLchar* field, const glm::vec3& vector)
	{
		GLint loc = glGetUniformLocation(shaderID, field);
		glUniform3f(loc, vector.x, vector.y, vector.z);
	}

	void Shader::setVec4(const GLchar* field, const glm::vec4& vector)
	{
		GLint loc = glGetUniformLocation(shaderID, field);
		glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::printCompileErrors(int vOrF, GLuint shader, GLchar* infoLog)
	{
		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			if (vOrF == 0)
			{
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
			else
			{
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
		}
	}

	void Shader::printLinkingErrors(GLchar* infoLog)
	{
		GLint success = 0;
		glGetProgramiv(shaderID, GL_LINK_STATUS, (int *)&success);
		if (success == GL_FALSE)
		{
			glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}

	GLuint Shader::uniformBlockBinding()
	{
		GLuint test = 0;
		GLint uboID = glGetUniformBlockIndex(shaderID, "SharedMatrices");
		glUniformBlockBinding(shaderID, uboID, test);
		return test;
	}
}