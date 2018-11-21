#include "Material.h"
#include "ResourcesManager.h"

#include "Shader.h"


AVTEngine::Material::Material()
{
}

AVTEngine::Material::Material(std::string shaderName)
{
	matName = shaderName;
	shader = ResourcesManager::loadShader(shaderName);

	glBindAttribLocation(shader->shaderID, 0, "in_Position");
	glBindAttribLocation(shader->shaderID, 1, "VertexNormal");
	glBindAttribLocation(shader->shaderID, 2, "texCoord");
}

AVTEngine::Material::Material(Shader* _shader)
{
	shader = _shader;
}

void AVTEngine::Material::setTexture(std::string name, Texture* value, unsigned int unit)
{
	samplerUniforms[name].unit = unit;
	samplerUniforms[name].texture = value;

	if (shader)
	{
		shader->use();
		shader->setInteger(name.c_str(), unit);
	}
}
