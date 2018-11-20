#pragma once

#include "Entity.h"

namespace AVTEngine
{
	enum BillboardMovement
	{
		CYLINDRICAL,
		SPHERICAL
	};

	class Billboard : public Entity
	{
	public:
		BillboardMovement movementType = BillboardMovement::CYLINDRICAL;

	public:
		Billboard();
		~Billboard();

	private:

	};
}