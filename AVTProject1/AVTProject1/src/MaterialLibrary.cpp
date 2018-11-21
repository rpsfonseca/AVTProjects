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
		Material* defaultMat = new Material("basic");
		defaultMaterials["basic"] = defaultMat;

		Material* tableMat = new Material("table");
		tableMat->setTexture("lightwood", ResourcesManager::loadTextureWithAlpha("wood", "textures\\lightwood2.png"), 0);
		//tableMat->setTexture("checker", ResourcesManager::loadTextureWithAlpha("checker", "textures\\checker2.png"), 1);
		tableMat->setTexture("checker", ResourcesManager::loadTextureWithAlpha("checker", "textures\\lightwood2.png"), 1);
		defaultMaterials["table"] = tableMat;

		Material* treeMat = new Material("billboard");
		treeMat->setTexture("myTextureSampler", ResourcesManager::loadTextureWithAlpha("tree", "textures\\tree.tga", GL_TEXTURE_2D, GL_RGBA), 3);
		defaultMaterials["tree"] = treeMat;
	}
}