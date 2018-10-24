#pragma once

#include <vector>
#include <string>
#include <map>

#include "Entity.h"
#include "Car.h"

/*
#include "graphics\camera\camera.hpp"
#include "graphics\globalLight.hpp"
#include "graphics\renderTarget.hpp"
*/

namespace AVTEngine
{
	class Entity;
	class SceneNode;
	class Mesh;
	class Material;
	class Renderer;
	class Car;

	/**
	*	Scene is a specific kind of node. It's the head of the scene graph. Houses a camera and a set of nodes.
	*/
	class Scene
	{
	public:
		/*
		Camera *sceneCamera;
		GlobalLight globalLight = GlobalLight(Vec3(0.f, 1.f, 0.f));
		RenderTarget *renderTarget;
		*/

		static SceneNode* rootSceneNode; /** The root node of our node hierarchy */
		static int nodeCounterId; /** Counter to keep track of the current node id to give to a new node */

		std::map<std::string, SceneNode*> nodes; /** Hashtable to store all scene nodes */
		std::map<std::string, Entity*> entities; /** Hashtable to store all entities */

		Car* car;

		Renderer* renderer;

		//TODO teste
		Entity* entity;
		

	public:

		Scene();

		static SceneNode* createSceneNode(Mesh* mesh, Material* material);
		//static Entity* createCar(SceneNode* node_, glm::vec3 startPos_, float rotation_);
		static Entity* createCheerio(SceneNode* node_, glm::vec3 startPos_);
		static Car* createCar(SceneNode* node_, glm::vec3 startPos_, float rotation_);

		Car* getCar() { return car; }


		void setupSceneManager();

		void pushToRender();

		void draw();

		void cleanup();

		/*
		void setCamera(Camera *camera_);
		void setLight(GlobalLight &light_);
		void setRenderTarget(RenderTarget *rendertarget_);
		RenderTarget *getRenderTarget();
		*/

		void setRenderer(Renderer* _renderer);

		void updateEntities(float delta_);
		void createStraightLine(int xin, int xfin, int zin, int zfin, int dir);
		void insertCheerio(int x, int y, int z);
	
	};
}
