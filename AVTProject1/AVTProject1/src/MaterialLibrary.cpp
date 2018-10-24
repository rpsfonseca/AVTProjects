#include "MaterialLibrary.h"

#include "ResourcesManager.h"

#include "Material.h"

namespace AVTEngine
{
	// --------------------------------------------------------------------------------------------
	MaterialLibrary::MaterialLibrary()
	{
		generateDefaultMaterials();
	}
	// --------------------------------------------------------------------------------------------
	MaterialLibrary::~MaterialLibrary()
	{
		for (auto it = defaultMaterials.begin(); it != defaultMaterials.end(); ++it)
		{
			delete it->second;
		}
		for (unsigned int i = 0; i < materials.size(); ++i)
		{
			delete materials[i];
		}
		//delete debugLightMaterial;
	}
	// --------------------------------------------------------------------------------------------    
	void MaterialLibrary::generateDefaultMaterials()
	{
		// default render material (deferred path)
		Material* defaultMat = new Material("basic");
		//defaultMat->Type = MATERIAL_DEFAULT;
		defaultMat->setTexture("TexAlbedo", ResourcesManager::loadTexture("default albedo", "textures/checkerboard.png", GL_TEXTURE_2D, GL_RGB), 3);
		defaultMat->setTexture("TexNormal", ResourcesManager::loadTexture("default normal", "textures/norm.png"), 4);
		defaultMat->setTexture("TexMetallic", ResourcesManager::loadTexture("default metallic", "textures/black.png"), 5);
		defaultMat->setTexture("TexRoughness", ResourcesManager::loadTexture("default roughness", "textures/checkerboard.png"), 6);
		defaultMaterials["basic"] = defaultMat;
	}
}