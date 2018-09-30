#pragma once


#include <string>
#include <map>

namespace AVTEngine
{
	class Shader;

	class ResourcesManager
	{
	private:
		static std::string resourcesPath;
		static std::map<std::string, Shader> shaders;

	private:
		ResourcesManager();

	public:
		static void init();
		static Shader* loadShader(std::string shaderName);
	};
}