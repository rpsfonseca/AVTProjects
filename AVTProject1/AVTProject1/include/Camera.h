#pragma once

#include "glm\glm.hpp"

namespace AVTEngine
{
	class Camera {
	private:
		glm::mat4 projection;
		glm::mat4 view;

	public:
		Camera(glm::mat4&& projection, glm::mat4&& view) : projection(projection), view(view) { }

		glm::mat4 getProjection() { return projection; }
		glm::mat4 getView() { return view; }

		glm::mat4 getViewProjection() { return projection * view; }

		void setProjection(glm::mat4&& projection) { this->projection = projection; }
		void setView(glm::mat4&& view) { this->view = view; }
	};
}