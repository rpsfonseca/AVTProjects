#include "TextureLoader.h"

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <FreeImage.h>

#include <iostream>

namespace AVTEngine
{
	// --------------------------------------------------------------------------------------------
	Texture* TextureLoader::loadTexture(std::string path, GLenum target, GLenum internalFormat, bool srgb)
	{
		Texture* texture = new Texture();
		texture->target = target;
		texture->internalFormat = internalFormat;
		
		int width, height, nrComponents;

		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP *dib(0);
		//pointer to the image data
		BYTE* bits(0);
		//image width and height
		//unsigned int width(0), height(0);
		//OpenGL's image ID to map to
		GLuint gl_texID;

		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(path.c_str(), 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
		{
			fif = FreeImage_GetFIFFromFilename(path.c_str());
		}
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
		{
			return nullptr;
		}

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, path.c_str());
		//if the image failed to load, return failure
		if (!dib)
			return nullptr;

		//retrieve the image data
		bits = FreeImage_GetBits(dib);
		unsigned int pitch = FreeImage_GetPitch(dib);
		//get the image width and height
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		//if this somehow one of these failed (they shouldn't), return failure
		if ((bits == 0) || (width == 0) || (height == 0))
			return nullptr;


		FREE_IMAGE_COLOR_TYPE type;
		type = FreeImage_GetColorType(dib);

		texture->generate(width, height, texture->internalFormat, GL_RGB, GL_UNSIGNED_BYTE, bits);

		texture->width = width;
		texture->height = height;

		FreeImage_Unload(dib);

		return texture;
	}

	// WORKAROUND TO BROKEN TEXTURE LOADER THAT DOESN'T SUPPORT TEXTURES WITH ALPHA
	Texture* TextureLoader::loadTextureWithAlpha(std::string path, GLenum target, GLenum internalFormat, bool srgb)
	{
		Texture* texture = new Texture();
		texture->target = target;
		texture->internalFormat = internalFormat;

		int width, height, nrComponents;

		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP *dib(0);
		//pointer to the image data
		BYTE* bits(0);
		//image width and height
		//unsigned int width(0), height(0);
		//OpenGL's image ID to map to
		GLuint gl_texID;

		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(path.c_str(), 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
		{
			fif = FreeImage_GetFIFFromFilename(path.c_str());
		}
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
		{
			return nullptr;
		}

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, path.c_str());
		//if the image failed to load, return failure
		if (!dib)
			return nullptr;

		//retrieve the image data
		bits = FreeImage_GetBits(dib);
		unsigned int pitch = FreeImage_GetPitch(dib);
		//get the image width and height
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		//if this somehow one of these failed (they shouldn't), return failure
		if ((bits == 0) || (width == 0) || (height == 0))
			return nullptr;


		FREE_IMAGE_COLOR_TYPE type;
		type = FreeImage_GetColorType(dib);

		texture->generateWithAlpha(width, height, texture->internalFormat, GL_RGBA, GL_UNSIGNED_BYTE, bits);

		texture->width = width;
		texture->height = height;

		FreeImage_Unload(dib);

		return texture;
	}
}