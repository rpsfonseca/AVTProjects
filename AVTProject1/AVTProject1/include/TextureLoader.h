#pragma once

#include "GL/glew.h"

#include <string>


namespace AVTEngine
{
	class Texture;

	/*

	Manages all custom logic for loading a variety of different texture files.

	*/
	class TextureLoader
	{
	public:
		static Texture* loadTexture(std::string path, GLenum target, GLenum internalFormat, bool srgb = false);
	};
}