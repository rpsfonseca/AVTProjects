#include "Texture.h"

#include <assert.h>
#include <iostream>

namespace AVTEngine
{
	// --------------------------------------------------------------------------------------------
	Texture::Texture()
	{

	}
	// --------------------------------------------------------------------------------------------
	Texture::~Texture()
	{

	}
	// --------------------------------------------------------------------------------------------
	void Texture::generate(unsigned int _width, unsigned int _height, GLenum _internalFormat, GLenum _format, GLenum _type, void* data)
	{
		glGenTextures(1, &id);

		width = _width;
		height = _height;
		depth = 0;
		internalFormat = _internalFormat;
		format = _format;
		type = _type;

		//assert(target == GL_TEXTURE_2D);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, id);
		bind();
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
		glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_BGR, type, data);
		if (mipmapping)
			glGenerateMipmap(target);
		unbind();
	}
	// WORKAROUND TO BROKEN TEXTURE LOADER THAT DOESN'T SUPPORT TEXTURES WITH ALPHA
	void Texture::generateWithAlpha(unsigned int _width, unsigned int _height, GLenum _internalFormat, GLenum _format, GLenum _type, void* data)
	{
		glGenTextures(1, &id);

		width = _width;
		height = _height;
		depth = 0;
		internalFormat = _internalFormat;
		format = _format;
		type = _type;

		//assert(target == GL_TEXTURE_2D);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, id);
		bind();
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
		glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_BGRA, type, data);
		if (mipmapping)
			glGenerateMipmap(target);
		unbind();
	}
	// --------------------------------------------------------------------------------------------
	void Texture::resize(unsigned int _width, unsigned int _height, unsigned int _depth)
	{
		bind();
		if (target == GL_TEXTURE_2D)
		{
			assert(height > 0);
			glTexImage2D(target, 0, internalFormat, _width, _height, 0, format, type, 0);
		}
	}
	// --------------------------------------------------------------------------------------------
	void Texture::bind(int unit)
	{
		if (unit >= 0)
			glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(target, id);
	}
	// --------------------------------------------------------------------------------------------
	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// --------------------------------------------------------------------------------------------
	void Texture::setWrapMode(GLenum wrapMode, bool _bind)
	{
		if (_bind)
		{
			bind();
		}
		if (target == GL_TEXTURE_1D)
		{
			wrapS = wrapMode;
			glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapMode);
		}
		else if (target == GL_TEXTURE_2D)
		{
			wrapS = wrapMode;
			wrapT = wrapMode;
			glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapMode);
			glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapMode);
		}
		else if (target == GL_TEXTURE_3D)
		{
			wrapS = wrapMode;
			wrapT = wrapMode;
			wrapR = wrapMode;
			glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapMode);
			glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapMode);
			glTexParameteri(target, GL_TEXTURE_WRAP_R, wrapMode);
		}
	}
	// --------------------------------------------------------------------------------------------
	void Texture::setFilterMin(GLenum filter, bool _bind)
	{
		if (_bind)
			bind();
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter);
	}
	// --------------------------------------------------------------------------------------------
	void Texture::setFilterMax(GLenum filter, bool _bind)
	{
		if (_bind)
			bind();
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter);
	}
}
