#pragma once

#include <glm/glm.hpp>
#include "Entity.h"

namespace AVTEngine
{

	class Wall
	{

	protected:


	private:


	public:

		Wall(int minX_, int minY_, int minZ_, int maxX_, int maxY_, int maxZ_);

		int minX, minY, minZ, maxX, maxY, maxZ;

		AABB getBoundingBox();
		bool handleCarCollision(Car* car);
	};
}

