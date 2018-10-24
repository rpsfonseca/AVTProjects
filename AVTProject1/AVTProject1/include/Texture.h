#pragma once

#include "GL/glew.h"

namespace AVTEngine
{
	/*

	Texture

	*/
	class Texture
	{
	public:
		unsigned int id;
		// TODO(Joey): these should be private and only accessed w/ getters/setters s.t. we can 
		// directly change the texture state where relevant from within the setters.
		GLenum target = GL_TEXTURE_2D;           // what type of texture we're dealing with
		GLenum internalFormat = GL_RGBA;                 // number of color components
		GLenum format = GL_RGBA;                 // the format each texel is stored in
		GLenum type = GL_UNSIGNED_BYTE;
		GLenum filterMin = GL_LINEAR_MIPMAP_LINEAR; // what filter method to use during minification
		GLenum filterMax = GL_LINEAR;               // what filter method to use during magnification
		GLenum wrapS = GL_REPEAT;               // wrapping method of the S coordinate
		GLenum wrapT = GL_REPEAT;               // wrapping method of the T coordinate
		GLenum wrapR = GL_REPEAT;               // wrapping method of the R coordinate
		bool mipmapping = true;

		unsigned int width = 0;
		unsigned int height = 0;
		unsigned int depth = 0;
	private:
	public:
		Texture();
		~Texture();

		// 2D texture generation
		void generate(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum type, void* data);

		// resizes the texture; allocates new (empty) texture memory
		void resize(unsigned int width, unsigned int height = 0, unsigned int depth = 0);

		void bind(int unit = -1);
		void unbind();

		// update relevant texture state
		void setWrapMode(GLenum wrapMode, bool bind = false);
		void setFilterMin(GLenum filter, bool bind = false);
		void setFilterMax(GLenum filter, bool bind = false);
	};
}