#include "scene.h"

namespace AVTEngine
{
	Scene::Scene()
	{
		//sceneEnvironment.globalLight = &globalLight;
		environment = &sceneEnvironment;
	}

	void Scene::draw()
	{
		resultMatrix = glm::mat4(1.0); //Identity Matrix

		/* TODO uncomment
		if (renderTarget != nullptr)
		{
			renderTarget->bind();
		}
		*/

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (Node *n : nodeArray)
		{
			n->draw(this);
		}

		/* TODO uncomment
		if (renderTarget != nullptr)
		{
			renderTarget->unbind();
		}
		*/
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
}