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
	glBindAttribLocation(shader->shaderID, 1, "VertexNormal");
}

AVTEngine::Material::Material(Shader* _shader)
{
	shader = _shader;
}

void AVTEngine::Material::setTexture(std::string name, Texture* value, unsigned int unit)
{
	/*samplerUniforms[name].Unit = unit;
	samplerUniforms[name].Texture = value;

	switch (value->target)
	{
	case GL_TEXTURE_2D:
		samplerUniforms[name].Type = SHADER_TYPE_SAMPLER2D;
		break;
	}*/

	if (shader)
	{
		shader->use();
		shader->setInteger(name.c_str(), unit);
	}
}
