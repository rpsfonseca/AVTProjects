#pragma once

#include "glm\glm.hpp"
#include "Shader.h"
#include "Material.h"
#include "ResourcesManager.h"

namespace AVTEngine {
	class LensFlare {
		struct FlareElement
		{
			FlareElement() {}
			FlareElement(Texture* texture, float fDistance, float fSize, unsigned int argb)
				: texture(texture), fDistance(fDistance), fSize(fSize), argb(argb) { }

			Texture* texture;

			float           fDistance;        // Distance along ray from source (0.0-1.0)
			float           fSize;            // Size relative to flare envelope (0.0-1.0)
			unsigned int    argb;            // ARGB for intensity mapping
		};

		float           fScale = 5;     // Scale factor for adjusting overall size of flare elements.
		float           fMaxSize = 0.25f;   // Max size of largest element, as proportion of screen width (0.0-1.0)
		int             nPieces = 4;    // Number of elements in use

		GLuint _textureID, _vaoID;

		GLuint _texCoordBuffer;
		GLuint _vertexBuffer;
		float _fontSize;

		FlareElement element[4];
		Shader* _shader = ResourcesManager::loadShader("lensflare");
		Material material = Material("lensflare");
		glm::vec3 lightPosition = glm::vec3(1.f);
		Mesh* mesh;

	public:
		LensFlare();
		void draw();
		void renderFlare(int lx, int ly, int cx, int cy);
	};
}