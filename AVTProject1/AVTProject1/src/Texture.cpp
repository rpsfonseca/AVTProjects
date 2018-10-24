#include "Texture.h"

#include <assert.h>

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
		height = height;
		depth = 0;
		internalFormat = _internalFormat;
		format = _format;
		type = _type;

		assert(target == GL_TEXTURE_2D);
		bind();
		glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, data);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filterMin);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filterMax);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);
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
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, format, type, 0);
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
		glBindTexture(target, 0);
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
