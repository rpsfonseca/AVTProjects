/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Original Author: Damiano Vitulli
 * Porting to OpenGL3.3: Movania Muhammad Mobeen
 * Shaders Functions: Movania Muhammad Mobeen
 *
 * This program is released under the BSD licence
 * By using this program you agree to licence terms on spacesimulator.net copyright page
 *
 */

#include "TextureMappedFont.h"
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "load_bmp.h"
#include "Application.h"
#include "FileSystem.h"
#include "ResourcesManager.h"
#include <cassert>
#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

namespace AVTEngine
{
	/*TextureMappedFont::TextureMappedFont(void)
	{
		_textureID = -1;
		_fontSize = 16;
	}*/

	TextureMappedFont::~TextureMappedFont(void)
	{
		glDeleteVertexArrays(1, &_vaoID);
		glDeleteBuffers(1, &_vertexBuffer);
		glDeleteBuffers(1, &_texCoordBuffer);
		glDeleteTextures(1, &_textureID);
	}

	TextureMappedFont::TextureMappedFont(const std::string& textureName, Shader& shader, float fontSize)
		: _shader(shader)
	{
		std::string path = FileSystem::getResourcesDirectory() + textureName;
		char* buf = new char[path.size() + 1];
		auto length = path.copy(buf, path.size());
		buf[length] = '\0';
		_textureID = LoadBMP(buf);
		delete[] buf;
		
		_shader.use();
		/*_shader.AddAttribute("vVertex");
		_shader.AddAttribute("vTexCoord");
		_shader.AddUniform("texture0");
		_shader.AddUniform("selected");*/
		_shader.setInteger("texture0", 2);
		_shader.setInteger("selected", 0);
		glUseProgram(0);
		_fontSize = fontSize;

		Init();
	}

	bool TextureMappedFont::Init()
	{
		float vertices[] = {
			0.0f, 0.0f,
			_fontSize, 0.0f,
			_fontSize, _fontSize,
			0.0f, _fontSize
		};

		GL_CHECK_ERRORS

			glGenVertexArrays(1, &_vaoID);
		glBindVertexArray(_vaoID);
		glGenBuffers(1, &_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(_shader["vVertex"]);
		glVertexAttribPointer(_shader["vVertex"], 2, GL_FLOAT, GL_FALSE, 0, 0);


		GL_CHECK_ERRORS

			//Just initialize with something for now, the tex coords are updated
			//for each character printed
			float texCoords[] = {
				0.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 0.0f
		};

		glGenBuffers(1, &_texCoordBuffer);
		GL_CHECK_ERRORS
			glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
		GL_CHECK_ERRORS
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, &texCoords[0], GL_DYNAMIC_DRAW);
		GL_CHECK_ERRORS
			glEnableVertexAttribArray(_shader["vTexCoord"]);
		GL_CHECK_ERRORS
		glVertexAttribPointer(_shader["vTexCoord"], 2, GL_FLOAT, GL_FALSE, 0, 0);

		GL_CHECK_ERRORS
			//set the orthographic projection matrix
			P = glm::ortho(0.f, float(WINDOW_WIDTH), 0.f, float(WINDOW_HEIGHT), -1.f, 1.f);
		return true;
	}



	void TextureMappedFont::DrawString(float x, float y, const std::string& str, bool sel)
	{
		// static float modelviewMatrix[16];
		 //static float projectionMatrix[16];

		GL_CHECK_ERRORS

			GLint test[1];
		glGetIntegerv(GL_DEPTH_TEST, test);
		glDisable(GL_DEPTH_TEST);

		_shader.use();

		float texCoords[8];

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _textureID);

		GL_CHECK_ERRORS

		glm::mat4 translate = glm::mat4(1), I = glm::mat4(1), MV = glm::mat4(1), oldMV, MVP = glm::mat4(1);
		//Position our text
		translate[3][0] = x;
		translate[3][1] = y;

		MV = I * translate;
		glBindVertexArray(_vaoID);
		// glTranslatef(x, y, 0.0); //Position our text
		for (std::string::size_type i = 0; i < str.size(); ++i)
		{
			MVP = P * MV;
			const float oneOverSixteen = 1.0f / 16.0f;

			int ch = int(str[i]);
			float xPos = float(ch % 16) * oneOverSixteen;
			float yPos = float(ch / 16) * oneOverSixteen;

			texCoords[0] = xPos;
			texCoords[1] = 1.0f - yPos - oneOverSixteen;

			texCoords[2] = xPos + oneOverSixteen;
			texCoords[3] = 1.0f - yPos - oneOverSixteen;

			texCoords[4] = xPos + oneOverSixteen;
			texCoords[5] = 1.0f - yPos - 0.001f;

			texCoords[6] = xPos;
			texCoords[7] = 1.0f - yPos - 0.001f;

			glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, &texCoords[0]);

			glUniformMatrix4fv(_shader("MVP"), 1, GL_FALSE, &MVP[0][0]);
			glUniform1i(_shader("selected"), sel);

			GL_CHECK_ERRORS

				glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

			GL_CHECK_ERRORS

				oldMV = MV;
			glm::mat4 t2 = glm::mat4(1);
			t2[3][0] = _fontSize * 0.8f;
			MV = oldMV * t2;

			GL_CHECK_ERRORS
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		GL_CHECK_ERRORS

			glUseProgram(0);

		GL_CHECK_ERRORS

			//if(test[0])
			glEnable(GL_DEPTH_TEST);
	}
}