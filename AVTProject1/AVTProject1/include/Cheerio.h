#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Constants.h"
#include "DynamicEntity.h"
//#include "Texture.h"
#include "Input.h"
#include <glm/glm.hpp>

namespace AVTEngine
{

	class Cheerio : public DynamicEntity
	{

	protected:


	private:


	public:

		Cheerio(SceneNode *node_, glm::vec3 startPos_);
		Cheerio();

		glm::vec3 initialPos;

		void reset();
		AABB getBoundingBox() override;
		void update(float delta);
		bool handleCarCollision(Car* car) override;
	};
}

