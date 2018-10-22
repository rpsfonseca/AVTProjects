#include "ResourcesManager.h"

#include "FileSystem.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "Shader.h"

namespace AVTEngine
{
	std::string ResourcesManager::resourcesPath = "";
	std::map<std::string, Shader> ResourcesManager::shaders = std::map<std::string, Shader>();

	void ResourcesManager::init()
	{
		resourcesPath = FileSystem::getResourcesDirectory();
	}

	Shader* ResourcesManager::loadShader(std::string shaderName)
	{
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
}