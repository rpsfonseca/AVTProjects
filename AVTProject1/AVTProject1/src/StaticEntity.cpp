#include "StaticEntity.h"


namespace AVTEngine
{
	StaticEntity::StaticEntity(){
	};

	StaticEntity::StaticEntity(SceneNode *node_, Shader *shader_, Mesh *mesh_, glm::vec3 startPos_){

		Entity::Entity(shader_, mesh_, 100, 3, glm::vec3(1, 0, 0));
		setPosition(startPos_);
		orientation = glm::vec3(1, 0, 0);
	};
}
