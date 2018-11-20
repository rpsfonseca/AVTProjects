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
		glm::vec3 arcBallOffset = glm::vec3(0);

		glm::vec3 up;
		glm::vec3 right;

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

		virtual void updateCameraVectors() = 0;
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

		void updateCameraVectors() override
		{
			// Calculate the new Front vector
			glm::vec3 front;
			front = glm::normalize(position);
			// Also re-calculate the Right and Up vector
			right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			up = glm::vec3(0, 1, 0);
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

		void updateCameraVectors() override
		{
			// Calculate the new Front vector
			glm::vec3 front;
			front = (position + arcBallOffset) - position;
			front = glm::normalize(front);
			// Also re-calculate the Right and Up vector
			right = glm::normalize(glm::cross(front, glm::vec3(0,1,0)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			up = glm::normalize(glm::cross(right, front));
		}
	};
}