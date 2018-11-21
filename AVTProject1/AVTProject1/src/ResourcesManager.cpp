#include "ResourcesManager.h"

#include "FileSystem.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "Shader.h"
#include "TextureLoader.h"

namespace AVTEngine
{
	std::string ResourcesManager::resourcesPath = "";
	std::map<std::string, Shader> ResourcesManager::shaders = std::map<std::string, Shader>();
	std::map<std::string, Mesh*> ResourcesManager::meshes = std::map<std::string, Mesh*>();
	std::map<std::string, Texture*> ResourcesManager::textures = std::map<std::string, Texture*>();

	void ResourcesManager::init()
	{
		resourcesPath = FileSystem::getResourcesDirectory();
	}

	Shader* ResourcesManager::loadShader(std::string shaderName)
	{
		std::cout << "SHADER NAME: " << shaderName << std::endl;
		if (!(shaders.find(shaderName) != shaders.end()))
		{
			std::string shaderPath = resourcesPath + "shaders\\";
			std::string vsShaderPath = shaderPath + shaderName + ".vs";
			std::string fsShaderPath = shaderPath + shaderName + ".fs";
			std::cout << vsShaderPath << std::endl;
			shaders.insert(std::pair<std::string, Shader>(shaderName, Shader(vsShaderPath.c_str(), fsShaderPath.c_str())));
		}
		return &shaders[shaderName];
	}

	Mesh* ResourcesManager::loadOBJ(std::string filename)
	{
		std::string modelPath = resourcesPath + "models\\";
		modelPath += filename + ".obj";
		OBJLoader loader = OBJLoader(modelPath);
		return loader.toMesh();
	}

	Texture* ResourcesManager::loadTexture(std::string textureName, std::string path, GLenum target, GLenum format, bool srgb)
	{
		// if texture already exists, return that handle
		/*if (ResourcesManager::textures.find(textureName) != ResourcesManager::textures.end())
			return &ResourcesManager::textures[textureName];*/
		path = resourcesPath + path;
		Texture* texture = TextureLoader::loadTexture(path, target, format, srgb);

		// make sure texture got properly loaded
		if (texture->width > 0)
		{
			ResourcesManager::textures[textureName] = texture;
			return ResourcesManager::textures[textureName];
		}
		else
		{
			return nullptr;
		}
	}

	// WORKAROUND TO BROKEN TEXTURE LOADER THAT DOESN'T SUPPORT TEXTURES WITH ALPHA
	Texture* ResourcesManager::loadTextureWithAlpha(std::string textureName, std::string path, GLenum target, GLenum format, bool srgb)
	{
		// if texture already exists, return that handle
		/*if (ResourcesManager::textures.find(textureName) != ResourcesManager::textures.end())
			return &ResourcesManager::textures[textureName];*/
		path = resourcesPath + path;
		Texture* texture = TextureLoader::loadTextureWithAlpha(path, target, format, srgb);

		// make sure texture got properly loaded
		if (texture->width > 0)
		{
			ResourcesManager::textures[textureName] = texture;
			return ResourcesManager::textures[textureName];
		}
		else
		{
			return nullptr;
		}
	}
}