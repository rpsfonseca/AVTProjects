#include "scene.h"
#include "node.h"
#include "Mesh.h"
#include "Material.h"
#include "ResourcesManager.h"

#include "Renderer.h"

#include "Cube.h"
#include "Car.h"
#include "Cheerio.h"
#include "Orange.h"
#include "Butter.h"
#include "Tree.h"

#include <glm/glm.hpp>
#include <GL/glew.h>


namespace AVTEngine
{
	SceneNode* Scene::rootSceneNode = new SceneNode(); /** The root node of our node hierarchy */
	int Scene::nodeCounterId; /** Counter to keep track of the current node id to give to a new node */

	Scene::Scene()
	{
		nodes = std::map<std::string, SceneNode*>();
		entities = std::map<std::string, Entity*>();
		walls = std::map<std::string, Wall*>();
		testboolean = true;
	}

	// Creates a new scene node and inits it with a model.
	SceneNode* Scene::createSceneNode(std::string name, Mesh* mesh, Material* material)
	{
		SceneNode* node = new SceneNode(name, mesh, material);

		return node;
	}

	Car* Scene::createCar(SceneNode* node_, glm::vec3 startPos_, float rotation_)
	{
		Car* car = new Car(node_, startPos_, rotation_);

		return car;
	}

	Entity* Scene::createCheerio(SceneNode* node_, glm::vec3 startPos_)
	{
		Entity* cheerio = new Cheerio(node_, startPos_);

		return cheerio;
	}

	Entity* Scene::createOrange(SceneNode* node_, float levelWidth_, float levelHeight_)
	{
		Entity* orange = new Orange(node_, levelWidth_, levelHeight_);

		return orange;
	}

	Entity* Scene::createButter(SceneNode* node_, glm::vec3 startPos_)
	{
		Entity* butter = new Butter(node_, startPos_);

		return butter;
	}

	int wallId = 0;
	void Scene::createWall(int minX_, int minY_, int minZ_, int maxX_, int maxY_, int maxZ_)
	{
		Wall* wall = new Wall(minX_, minY_, minZ_, maxX_, maxY_, maxZ_);

		std::string id = "wall" + std::to_string(wallId);
		wallId++;

		walls.insert(std::pair<std::string, Wall*>(id, wall));
	}

	// Sets up the scene manager.
	// Takes care of creating the uniform block for the shader and creating the scene nodes.
	void Scene::setupSceneManager()
	{

		//Walls
		createWall(-100, 0, -68, 100, 10, -68);
		createWall(-100, 0, 68, 100, 10, 68);
		createWall(-80, 0, -68, -80, 10, 68);
		createWall(80, 0, -68, 80, 10, 68);

		//Mesa
		Mesh* testMesh = ResourcesManager::loadOBJ("table");
		SceneNode* planeNode = Scene::createSceneNode("table", testMesh, renderer->getMaterial("table"));
		planeNode->material->setAmbient(glm::vec3(1.f, 0.5f, 0.31f));
		planeNode->material->setDiffuse(glm::vec3(1.0f, 0.5f, 0.31f));
		planeNode->material->setSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		planeNode->material->setShininess(32.f);
		planeNode->setPosition(glm::vec3(0.0f, -1.0f, 0.0f));
		planeNode->setScale(glm::vec3(10, 1, 10));
		planeNode->setMirrored(false); 
		rootSceneNode->addChild(planeNode);

		//Trees
		insertTree(0, 5, 0);
		insertTree(25, 5, 25);
		insertTree(25, 5, -25);
		insertTree(-25, 5, 25);
		insertTree(-25, 5, -25);

		//TODO teste com o carro
		//Carro
		Mesh* testMesh2 = ResourcesManager::loadOBJ("car_with_wheels");
		SceneNode* planeNode2 = Scene::createSceneNode("car", testMesh2, new Material("basic"));
		glm::vec3 startPos = glm::vec3(0, 0, -50);
		car = Scene::createCar(planeNode2, startPos, 0);

		planeNode2->material->setAmbient(glm::vec3(0.f, 0.8f, 1.f));
		planeNode2->material->setDiffuse(glm::vec3(0.0f, 0.8f, 1.f));
		planeNode2->material->setSpecular(glm::vec3(0.0f, 0.8f, 1.f));
		planeNode2->material->setShininess(100.f);
		rootSceneNode->addChild(planeNode2);
		
		nodes.insert(std::pair<std::string, SceneNode*>("plane2", planeNode2));
		entities.insert(std::pair<std::string, Entity*>("car", car));


		//Track
		
		//Outter Lines
		createStraightLine(-70, 70, -60, -60, 1);
		/*createStraightLine(-70, 70, 60, 60, 1);
		createStraightLine(-70, -70, -60, 60, 0);
		createStraightLine(70, 70, -60, 60, 0);
		
		//Inner Lines
		createStraightLine(-50, 50, -40, -40, 1);
		createStraightLine(-50, 50, 40, 40, 1);
		createStraightLine(-50, -50, -40, 40, 0);
		createStraightLine(50, 50, -40, 40, 0);
		*/

		
		//Butters
		insertButter(10, 1, 10);
		insertButter(-20, 1, -30);
		insertButter(-20, 1, 30);
		insertButter(20, 1, -30);
		insertButter(20, 1, 30);

		//Oranges
		for (int j = 0; j < NUM_ORANGES; j++) {
			insertOrange(LEVEL_WIDTH, LEVEL_HEIGHT);
		}

		
	}


	void Scene::pushToRender()
	{
		renderer->pushRenderables(rootSceneNode);
	}

	void Scene::draw()
	{
		renderer->renderPushedCommands();
	}

	void Scene::cleanup()
	{
		for (std::map<std::string, SceneNode*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			it->second->cleanup();
			delete it->second;
		}
		delete rootSceneNode;
	}

	void Scene::setRenderer(Renderer* _renderer)
	{
		renderer = _renderer;
	}

	void Scene::updateEntities(float delta_)
	{
		for (std::map<std::string, Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			it->second->update(delta_);
		}
	}

	void Scene::createStraightLine(int xin, int xfin, int zin, int zfin, int dir) {
		
		int z = zin;
		int x = xin;

		if (dir) { //De -x para +x
			for (x = xin; x< xfin; x += 3) {
				insertCheerio(x, 0, z);
			}
		}
		else { //De -z para +z
			for (z = zin; z < zfin; z += 3) {
				insertCheerio(x, 0, z);
			}
		}
		
	}

	int cheerioId = 0;
	void Scene::insertCheerio(int x, int y, int z) {

		Mesh* cheerioMesh = ResourcesManager::loadOBJ("torus");
		SceneNode* a = Scene::createSceneNode("cheerio", cheerioMesh, renderer->getMaterial("basic"));
		glm::vec3 posVec = glm::vec3(x, y, z);
		Entity* cheerio = Scene::createCheerio(a, posVec);

		a->material->setAmbient(glm::vec3(1.f, 1.f, 0.f));
		a->material->setDiffuse(glm::vec3(1.0f, 1.f, 0.0f));
		a->material->setSpecular(glm::vec3(1.f, 1.f,1.f));
		a->material->setShininess(64.f);
		a->setPosition(posVec);

		rootSceneNode->addChild(a);
		std::string id = "cheerio" + std::to_string(cheerioId);
		cheerioId++;
		nodes.insert(std::pair<std::string, SceneNode*>(id, a));
		entities.insert(std::pair<std::string, Entity*>(id, cheerio));
	}


	int orangeId = 0;
	void Scene::insertOrange(float levelWidth_, float levelHeight_) {

		Mesh* orangeMesh = ResourcesManager::loadOBJ("orange");
		SceneNode* a = Scene::createSceneNode("orange", orangeMesh, renderer->getMaterial("basic"));
		Entity* orange = Scene::createOrange(a, levelWidth_, levelHeight_);

		a->material->setAmbient(glm::vec3(1.f, 1.f, 0.f));
		a->material->setDiffuse(glm::vec3(1.0f, 1.f, 0.0f));
		a->material->setSpecular(glm::vec3(1.f, 1.f, 1.f));
		a->material->setShininess(64.f);

		rootSceneNode->addChild(a);
		std::string id = "orange" + std::to_string(orangeId);
		orangeId++;

		nodes.insert(std::pair<std::string, SceneNode*>(id, a));
		entities.insert(std::pair<std::string, Entity*>(id, orange));
	}


	int butterId = 0;
	void Scene::insertButter(int x, int y, int z) {

		Mesh* butterMesh = ResourcesManager::loadOBJ("untitled");
		SceneNode* a = Scene::createSceneNode("butter", butterMesh, renderer->getMaterial("basic"));
		glm::vec3 posVec = glm::vec3(x, y, z);
		Entity* butter = Scene::createButter(a, posVec);

		a->material->setAmbient(glm::vec3(1.f, 1.f, 0.f));
		a->material->setDiffuse(glm::vec3(1.0f, 1.f, 0.0f));
		a->material->setSpecular(glm::vec3(1.f, 1.f, 1.f));
		a->material->setShininess(90.f);

		a->setPosition(posVec);
		a->setScale(glm::vec3(1.8, 2, 3));

		rootSceneNode->addChild(a);
		std::string id = "butter" + std::to_string(butterId);
		butterId++;

		nodes.insert(std::pair<std::string, SceneNode*>(id, a));
		entities.insert(std::pair<std::string, Entity*>(id, butter));
	}

	int treeId = 0;
	void Scene::insertTree(int x, int y, int z) {

		Tree* tree = new Tree();
		SceneNode* treeNode = Scene::createSceneNode("tree", tree->getMesh(), renderer->getMaterial("tree"));
		treeNode->setPosition(glm::vec3(x, y, z));
		treeNode->setScale(glm::vec3(5.0f, 5.0f, 0.0f));
		treeNode->material->setAmbient(glm::vec3(1.f, 0.5f, 0.31f));
		treeNode->material->setDiffuse(glm::vec3(1.0f, 0.5f, 0.31f));
		treeNode->material->setSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		treeNode->material->setShininess(32.f);
		rootSceneNode->addChild(treeNode);

		std::string id = "tree" + std::to_string(treeId);
		treeId++;
		nodes.insert(std::pair<std::string, SceneNode*>("tree", treeNode));
	}
}