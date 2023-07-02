#pragma once

#include <functional>

#include <glm\glm.hpp>
#include <GLFW/glfw3.h>

namespace Playground
{
	class Camera
	{
	public:
		enum Movement
		{
			FORWARD = GLFW_KEY_W,
			BACKWARD = GLFW_KEY_S,
			LEFT = GLFW_KEY_A,
			RIGHT = GLFW_KEY_D,
			UP = GLFW_KEY_E,
			DOWN = GLFW_KEY_Q,
		};

	public:
		Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

		float GetFov() const { return _fov; }

		glm::mat4 LookAt() const;
		void Move(const Movement movement);
		void ProcessMouseOffset(const double xOffset, const double yOffset);
		void Zoom(const double yOffset);
		void Reset();

	public:		// SLOTS
		void OnInputReceive(int key);

	private:
		glm::vec3 GetRightVector() const;

	private:
		float _speed = 0.05f;
		glm::vec3 _pos;
		glm::vec3 _front;
		glm::vec3 _up;

		float _pitch = 0.0f;
		float _yaw = -90.0f;
		float _roll = 0.0f;

		float _fov = 45.0f;

		double _deltaTime = 0.0f;
		double _lastFrameTime = 0.0f;
	};
}

