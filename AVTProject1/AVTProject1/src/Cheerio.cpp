#include "Cheerio.h"
#include "Car.h"

namespace AVTEngine
{

	Cheerio::Cheerio(SceneNode *node_, glm::vec3 startPos_) : DynamicEntity::DynamicEntity(node_, startPos_, CHEERIO_MAX_VELOCITY, CHEERIO_MAX_TURNRATE) {

		initialPos = startPos_;

		//TODO not sure if needed
		minVelocity = 0.1; // Velocidade para qual o algoritmo arredonda para 0
		minDrag = MIN_DRAG; // Forca minima de fricao

	};

	/* TODO Stuff for collision detection
	get type() {   //Para saber que tipo de colisão se trata
	return TYPE.CHEERIO;
	}

	getBoundingVolume() { //Raio da caixa para colisao
	return new Circle(this.getPosition(), 1.75);
	}
	*/

	void Cheerio::update(float delta_) { //
		//Update
		DynamicEntity::integrate(0, 0, delta_);
	}

	void Cheerio::reset() {
		DynamicEntity::reset();
		setPosition(initialPos); //Voltar à posição inicial do cheerio
	}

	AABB Cheerio::getBoundingBox() {
		auto position = node->position;
		return AABB(
			position.x - 1.f, position.x + 1.f,
			position.y - 1.f, position.y + 1.f,
			position.z - 1.f, position.z + 1.f);
	}

	bool Cheerio::handleCarCollision(Car* car) {
		std::cout << "cheerio collision\n";
		// move a little
		auto playerDirection = glm::normalize(this->getPosition() - car->getPosition());
		this->setPosition(this->getPosition() + playerDirection);
		return true;
	}
}
