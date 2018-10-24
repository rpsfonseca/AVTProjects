#include "Butter.h"


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
}
