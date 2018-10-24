#include "Butter.h"
#include "Car.h"


namespace AVTEngine
{

	Butter::Butter(SceneNode *node_, glm::vec3 startPos_) : DynamicEntity::DynamicEntity(node_, startPos_) {
	};

	/* TODO Stuff for collision detection
	get type() {   //Para saber que tipo de colisão se trata
	return TYPE.CHEERIO;
	}

	getBoundingVolume() { //Raio da caixa para colisao
	return new Circle(this.getPosition(), 1.75);
	}
	*/

	void Butter::update(float delta_) {
		//Do nothing
	}

	AABB Butter::getBoundingBox() {
		auto position = node->position;
		return AABB(
			position.x - 1.5f, position.x + 1.5f,
			position.y - 1.f, position.y + 1.f,
			position.z - 1.5f, position.z + 1.5f);
	}

	bool Butter::handleCarCollision(Car* car) {
		std::cout << "butter collision\n";
		
		//stop car
		car->velocity = 0;
		return true;
	}
}
