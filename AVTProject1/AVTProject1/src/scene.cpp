#include "scene.h"
#include "node.h"
#include "Mesh.h"
#include "Material.h"
#include "ResourcesManager.h"

#include "Renderer.h"

#include "Cube.h"
#include "Car.h"
#include "Cheerio.h"

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
	}

	// Creates a new scene node and inits it with a model.
	SceneNode* Scene::createSceneNode(Mesh* mesh, Material* material)
	{
		SceneNode* node = new SceneNode(mesh, material);

		return node;
	}

	Entity* Scene::createCar(SceneNode* node_, glm::vec3 startPos_, float rotation_)
	{
		Entity* car = new Car(node_, startPos_, rotation_);

		return car;
	}

	Entity* Scene::createCheerio(SceneNode* node_, glm::vec3 startPos_)
	{
		Entity* cheerio = new Cheerio(node_, startPos_);

		return cheerio;
	}

	// Sets up the scene manager.
	// Takes care of creating the uniform block for the shader and creating the scene nodes.
	void Scene::setupSceneManager()
	{
		//renderer->setupRenderer();

		/*glGenBuffers(1, &uniformBlockId);

		glBindBuffer(GL_UNIFORM_BUFFER, uniformBlockId);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(Mat4) * 2, 0, GL_STREAM_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, renderer->uboBp, uniformBlockId);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);*/

		// TODO: we could probably do
		// glGenBuffers(1, &renderer->uboId);
		// glBindBuffer(GL_UNIFORM_BUFFER, renderer->uboId);
		// glBufferData(GL_UNIFORM_BUFFER, sizeof(Mat4) * 2, 0, GL_STREAM_DRAW);
		// glBindBufferBase(GL_UNIFORM_BUFFER, renderer->uboBp, renderer->uboId);

		//renderer->uboId = uniformBlockId;


		//Mesh* testMesh = ResourcesManager::loadOBJ("untitled");
		Mesh* testMesh = ResourcesManager::loadOBJ("table");
		SceneNode* planeNode = Scene::createSceneNode(testMesh, new Material("basic"));
		planeNode->material->setAmbient(glm::vec3(1.f, 0.5f, 0.31f));
		planeNode->material->setDiffuse(glm::vec3(1.0f, 0.5f, 0.31f));
		planeNode->material->setSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		planeNode->material->setShininess(32.f);
		planeNode->setPosition(glm::vec3(0.0f, -10.0f, 0.0f));
		planeNode->setScale(glm::vec3(10, 1, 10));
		/*planeNode->setScale(Vec3(4.0f));
		planeNode->model->setPosition(Vec3(0, 0, -1.0f));
		planeNode->model->setRotation(0.0f);
		planeNode->model->setScale(Vec3(1.0f));*/
		rootSceneNode->addChild(planeNode);

		//rootSceneNode->childNodes = std::vector<SceneNode*>(1, planeNode);

		/*SceneNode* planeNode2 = Scene::createSceneNode(new Mesh(vectorOfVertices, indices), new Material("basic"));
		planeNode2->material->setAmbient(glm::vec3(1.f, 1.f, 0.3f));
		planeNode2->material->setDiffuse(glm::vec3(0.5f, 0.5f, 1.f));
		planeNode2->material->setSpecular(glm::vec3(1.f));
		planeNode2->material->setShininess(32.f);
		planeNode2->setPosition(glm::vec3(-1.0f, -1.0f, 0.0f));
		/*planeNode2->setScale(Vec3(3.0f, 1.5f, 1.0f));
		planeNode2->model->setPosition(Vec3(0.0f));
		planeNode2->model->setRotation(0.0f);
		planeNode2->model->setScale(Vec3(1.0f));
		rootSceneNode->addChild(planeNode2);*/


		//TODO teste com o carro
		Mesh* testMesh2 = ResourcesManager::loadOBJ("car_with_wheels");
		SceneNode* planeNode2 = Scene::createSceneNode(testMesh2, new Material("basic"));
		glm::vec3 teste = glm::vec3(0);
		Entity* car = Scene::createCar(planeNode2, teste, 0);

		planeNode2->material->setAmbient(glm::vec3(1.f, 0.5f, 0.31f));
		planeNode2->material->setDiffuse(glm::vec3(1.0f, 0.5f, 0.31f));
		planeNode2->material->setSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		planeNode2->material->setShininess(32.f);
		planeNode2->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		/*planeNode->setScale(Vec3(4.0f));
		planeNode->model->setPosition(Vec3(0, 0, -1.0f));
		planeNode->model->setRotation(0.0f);
		planeNode->model->setScale(Vec3(1.0f));*/
		rootSceneNode->addChild(planeNode2);
		
		//nodes.insert(std::pair<std::string, SceneNode*>("plane", planeNode));
		nodes.insert(std::pair<std::string, SceneNode*>("plane2", planeNode2));
		entities.insert(std::pair<std::string, Entity*>("car", car));


		//Teste Cheerios
		/*
		int x = 5;
		int y = 2;
		int z = 5;

		for (int i = 0; i < 2; i++) {
			Mesh* cheerioMesh = ResourcesManager::loadOBJ("torus");
			SceneNode* a = Scene::createSceneNode(cheerioMesh, new Material("basic"));
			glm::vec3 testeVec = glm::vec3(x, y, z);
			Entity* cheerio = Scene::createCheerio(a, testeVec);

			a->material->setAmbient(glm::vec3(1.f, 0.5f, 0.31f));
			a->material->setDiffuse(glm::vec3(1.0f, 0.5f, 0.31f));
			a->material->setSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
			a->material->setShininess(32.f);
			a->setPosition(testeVec);
			/*planeNode->setScale(Vec3(4.0f));
			planeNode->model->setPosition(Vec3(0, 0, -1.0f));
			planeNode->model->setRotation(0.0f);
			planeNode->model->setScale(Vec3(1.0f));
			rootSceneNode->addChild(a);
			nodes.insert(std::pair<std::string, SceneNode*>("cheerio", a));
			entities.insert(std::pair<std::string, Entity*>("cheerio", cheerio));

			x += 5;
			z += 5;
		} */

		createStraightLine(-20, 20, -10, -10, 0);

	}


	void Scene::pushToRender()
	{
		renderer->pushRenderables(rootSceneNode);
	}

	void Scene::draw()
	{
		//resultMatrix = glm::mat4(1.0); //Identity Matrix

		/* TODO uncomment
		if (renderTarget != nullptr)
		{
			renderTarget->bind();
		}
		*/
		renderer->renderPushedCommands();

		/*for (SceneNode* n : nodeArray)
		{
			n->draw(this);
		}*/

		/* TODO uncomment
		if (renderTarget != nullptr)
		{
			renderTarget->unbind();
		}
		*/
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

	/* TODO uncomment
	void Scene::setCamera(Camera *camera_)
	{
		sceneCamera = camera_;
		sceneEnvironment.camera = sceneCamera;
	}
	*/

	/* TODO uncomment
	void Scene::setLight(GlobalLight &light_)
	{
		globalLight = light_;
		sceneEnvironment.globalLight = &globalLight;
	}
	*/

	/* TODO uncomment
	void Scene::setRenderTarget(RenderTarget *renderTarget_)
	{
		renderTarget = renderTarget_;
	}
	*/

	/* TODO uncomment
	RenderTarget *Scene::getRenderTarget()
	{
		return renderTarget;
	}
	*/

	void Scene::updateEntities(float delta_) {
		for (std::map<std::string, Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			it->second->update(delta_);
		}
	}

	void Scene::createStraightLine(int xin, int xfin, int zin, int zfin, int dir) {
		int j = abs(xfin - xin) / 3; //i incrementa de 3 a 3
		int z = zin;

		for (int x = xin; x< xfin; x += 3) {
			insertCheerio(x, 0, z);
			z += (abs(zfin - zin) / j);
		}
	}

	void Scene::insertCheerio(int x, int y, int z) {

		Mesh* cheerioMesh = ResourcesManager::loadOBJ("torus");
		SceneNode* a = Scene::createSceneNode(cheerioMesh, new Material("basic"));
		glm::vec3 posVec = glm::vec3(x, y, z);
		Entity* cheerio = Scene::createCheerio(a, posVec);

		a->material->setAmbient(glm::vec3(1.f, 0.5f, 0.31f));
		a->material->setDiffuse(glm::vec3(1.0f, 0.5f, 0.31f));
		a->material->setSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		a->material->setShininess(32.f);
		a->setPosition(posVec);

		rootSceneNode->addChild(a);
		nodes.insert(std::pair<std::string, SceneNode*>("cheerio", a));
		entities.insert(std::pair<std::string, Entity*>("cheerio", cheerio));
	}
}