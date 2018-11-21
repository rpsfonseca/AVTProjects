#pragma once

#include <vector>
#include <string>
#include <map>

#include "Entity.h"
#include "Car.h"
#include "Wall.h"

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

		static SceneNode* rootSceneNode; /** The root node of our node hierarchy */
		static int nodeCounterId; /** Counter to keep track of the current node id to give to a new node */

		std::map<std::string, SceneNode*> nodes; /** Hashtable to store all scene nodes */
		std::map<std::string, Entity*> entities; /** Hashtable to store all entities */
		std::map<std::string, Wall*> walls; /** Hashtable to store all walls */

		Car* car;

		Renderer* renderer;
		Entity* entity;

		bool testboolean;
		bool testboolean2 = true;
		

	public:

		Scene();

		static SceneNode* createSceneNode(std::string name, Mesh* mesh, Material* material);
		static Entity* createCheerio(SceneNode* node_, glm::vec3 startPos_);
		static Car* createCar(SceneNode* node_, glm::vec3 startPos_, float rotation_);
		static Entity* createOrange(SceneNode* node_, float levelWidth_, float levelHeight_);
		static Entity* createButter(SceneNode* node_, glm::vec3 startPos_);

		Car* getCar() { return car; }


		void setupSceneManager();
		void pushToRender();
		void draw();
		void cleanup();

		void setRenderer(Renderer* _renderer);

		void updateEntities(float delta_);
		void createStraightLine(int xin, int xfin, int zin, int zfin, int dir);
		void insertCheerio(int x, int y, int z);
		void insertOrange(float levelWidth_, float levelHeight_);
		void insertButter(int x, int y, int z);
		void createWall(int minX_, int minY_, int minZ_, int maxX_, int maxY_, int maxZ_);
		void insertTree(int x, int y, int z);
	
	};
}
