#pragma once

#include "Texture.h"

#include <string>
#include <map>

namespace AVTEngine
{
	class Mesh;
	class Shader;

	class ResourcesManager
	{
	private:
		static std::string resourcesPath;
		static std::map<std::string, Shader> shaders;
		static std::map<std::string, Mesh*> meshes;
		static std::map<std::string, Texture> textures;

	private:
		ResourcesManager();

	public:
		static void init();
		static Shader* loadShader(std::string shaderName);
		static Mesh* loadOBJ(std::string modelName);
		static Texture* loadTexture(std::string name, std::string path, GLenum target = GL_TEXTURE_2D, GLenum format = GL_RGBA, bool srgb = false);
	};
}