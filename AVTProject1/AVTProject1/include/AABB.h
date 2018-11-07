struct AABB {
	float xMin, xMax, yMin, yMax, zMin, zMax;

	AABB(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) :
		xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), zMin(zMin), zMax(zMax) {

	}

	bool collidesWith(AABB other);
};