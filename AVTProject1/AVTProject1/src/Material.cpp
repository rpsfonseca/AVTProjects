#include "Material.h"
#include "ResourcesManager.h"

#include "Shader.h"


AVTEngine::Material::Material()
{
}

AVTEngine::Material::Material(std::string shaderName)
{
	shader = ResourcesManager::loadShader(shaderName);

	glBindAttribLocation(shader->shaderID, 0, "in_Position");
}

AVTEngine::Material::Material(Shader * _shader)
{
}
