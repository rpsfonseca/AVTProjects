#pragma once

#include "Texture.h"

#include <map>
#include "glm\glm.hpp"

namespace AVTEngine
{
	class Shader;

	class Material
	{
	private:
		Shader* shader;
		glm::vec3 ambient = glm::vec3(1.f);
		glm::vec3 diffuse = glm::vec3(1.f);
		glm::vec3 specular = glm::vec3(1.f);
		float shininess = 32.f;
		
	public:
		Material();
		Material(std::string shaderName);
		Material(Shader* _shader);

		void setTexture(std::string name, Texture* value, unsigned int unit = 0);

		inline Shader* getShader() { return shader; };
		inline glm::vec3 getAmbient() { return ambient; }
		inline glm::vec3 getDiffuse() { return diffuse; }
		inline glm::vec3 getSpecular() { return specular; }
		inline float getShininess() { return shininess; }
		inline void setAmbient(glm::vec3 ambient) { this->ambient = ambient; }
		inline void setDiffuse(glm::vec3 diffuse) { this->diffuse = diffuse; }
		inline void setSpecular(glm::vec3 specular) { this->specular = specular; }
		inline void setShininess(float shininess) { this->shininess = shininess; }
	};
}