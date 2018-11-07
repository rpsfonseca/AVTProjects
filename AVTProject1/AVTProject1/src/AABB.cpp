#include "AABB.h"

bool AABB::collidesWith(AABB other)
{
	return (this->xMax >= other.xMin && this->xMin <= other.xMax)
		&& (this->yMax >= other.yMin && this->yMin <= other.yMax)
		&& (this->zMax >= other.zMin && this->zMin <= other.zMax);
}
