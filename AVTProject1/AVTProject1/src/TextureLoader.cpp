#include "TextureLoader.h"

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace AVTEngine
{
	// --------------------------------------------------------------------------------------------
	Texture TextureLoader::loadTexture(std::string path, GLenum target, GLenum internalFormat, bool srgb)
	{
		Texture texture;
		texture.target = target;
		texture.internalFormat = internalFormat;
		if (texture.internalFormat == GL_RGB || texture.internalFormat == GL_SRGB)
			texture.internalFormat = srgb ? GL_SRGB : GL_RGB;
		if (texture.internalFormat == GL_RGBA || texture.internalFormat == GL_SRGB_ALPHA)
			texture.internalFormat = srgb ? GL_SRGB_ALPHA : GL_RGBA;

		// flip textures on their y coordinate while loading
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			if (target == GL_TEXTURE_2D)
				texture.generate(width, height, texture.internalFormat, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			stbi_image_free(data);
			return texture;
		}
		texture.width = width;
		texture.width = height;

		return texture;
	}

}