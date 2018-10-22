#pragma once

#include <map>

namespace AVTEngine
{
	class Shader;

	class Material
	{
	private:
		Shader* shader;
		
	public:
		Material();
		Material(std::string shaderName);
		Material(Shader* _shader);

		inline Shader* getShader() { return shader; };
	};
}