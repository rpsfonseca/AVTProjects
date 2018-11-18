#include "Wall.h"
#include "Car.h"
#include "Orange.h"


namespace AVTEngine
{

	Wall::Wall(int minX_, int minY_, int minZ_, int maxX_, int maxY_, int maxZ_) {
			minX = minX_;
			minY = minY_;
			minZ = minZ_;
			maxX = maxX_;
			maxY = maxY_;
			maxZ = maxZ_;
	};

	AABB Wall::getBoundingBox() {
		return AABB(
			minX,
			maxX,
			minY,
			maxY,
			minZ,
			maxZ
		);
	}

	bool Wall::handleCarCollision(Car* car) {
		std::cout << "Wall collision\n";

		//stop car
		Application::getInstance()->getGameState().lives--;
		car->reset();
		return false;
	}

}
