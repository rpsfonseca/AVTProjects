#pragma once

#include "node.h"
#include <vector>

/*
#include "graphics\camera\camera.hpp"
#include "graphics\globalLight.hpp"
#include "graphics\renderTarget.hpp"
*/

namespace AVTEngine
{

	/**
	*	Scene is a specific kind of node. It's the head of the scene graph. Houses a camera and a set of nodes.
	*/
	class Scene : public Node
	{
	public:

		Scene();

		void draw();

		/*
		void setCamera(Camera *camera_);
		void setLight(GlobalLight &light_);
		void setRenderTarget(RenderTarget *rendertarget_);
		RenderTarget *getRenderTarget();
		*/

	private:
		/*
		Camera *sceneCamera;
		GlobalLight globalLight = GlobalLight(Vec3(0.f, 1.f, 0.f));
		RenderTarget *renderTarget;
		*/
		Environment sceneEnvironment;
	};
}
