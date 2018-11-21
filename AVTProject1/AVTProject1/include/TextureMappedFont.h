#pragma once

#include <string>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "Shader.h"

namespace AVTEngine
{
	class TextureMappedFont
	{
	public:
		TextureMappedFont(const std::string& fontTexture, Shader& shader, float fontSize = 16.0f);
		~TextureMappedFont(void);

		bool Init();
		void DrawString(float x, float y, const std::string& string, bool selected = false);

	private:
		GLuint _textureID, _vaoID;

		GLuint _texCoordBuffer;
		GLuint _vertexBuffer;
		float _fontSize;

		glm::mat4 P; //orthographic projection matrix
		Shader& _shader;
	};
}