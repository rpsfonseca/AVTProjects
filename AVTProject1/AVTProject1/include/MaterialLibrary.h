#pragma once

#include <string>
#include <vector>
#include <map>

namespace AVTEngine
{
	class Material;
	class Renderer;
	class Shader;

	/*

	Manages and maintains a list of common render materials, either for storing a template list
	of common materials or for storing internal renderer materials.

	*/
	class MaterialLibrary
	{
		friend Renderer;
	private:
		// holds a list of default material templates that other materials can derive from
		std::map<std::string, Material*> defaultMaterials;
		// stores all generated/copied materials
		std::vector<Material*> materials;

		Material *debugLightMaterial;
	public:
		MaterialLibrary();
		~MaterialLibrary();

	private:
		// generate all default template materials
		void generateDefaultMaterials();
		// generate all internal materials used by the renderer; run in MaterialLibrary to improve readability.
		//void generateInternalMaterials();
	};
}