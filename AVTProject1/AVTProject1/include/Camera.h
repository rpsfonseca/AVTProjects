#pragma once

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

namespace AVTEngine
{
	class Camera {
	public:
		glm::mat4 projection;
		glm::mat4 view;
		glm::vec3 position = glm::vec3(0, 0, -1);
		glm::vec3 arcBallOffset = glm::vec3(5);

	public:
		Camera(glm::mat4&& projection, glm::mat4&& view) : projection(projection), view(view) { }

		glm::mat4 getProjection() { return projection; }
		virtual glm::mat4 getView() = 0;
		virtual glm::vec3 getPosition() = 0;

		glm::mat4 getViewProjection() { return getProjection() * getView(); }

		void setProjection(glm::mat4&& projection) { this->projection = projection; }
		void setView(glm::mat4&& view) { this->view = view; }
		void setPosition(glm::vec3&& position) { this->position = position; }
		void setArcballOffset(glm::vec3&& offset) { this->arcBallOffset = offset; }
	};

	class FixedViewCamera : public Camera {
	public:
		using Camera::Camera;
		glm::mat4 getView() override {
			return view;
		}
		glm::vec3 getPosition() override {
			return view[3];
		}
	};

	class ArcballCamera : public Camera {
	public:
		using Camera::Camera;
		glm::mat4 getView() override {
			return glm::lookAt(position + arcBallOffset, position, glm::vec3(0, 1, 0));
		}
		glm::vec3 getPosition() override {
			return position + arcBallOffset;
		}
	};
}