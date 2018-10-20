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
		inline Shader* getShader() { return shader; };
	};
}