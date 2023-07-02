#pragma once
#include <glm\glm.hpp>

namespace Playground
{
	class Camera
	{
	public:
		enum Movement
		{
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT,
			UP,
			DOWN,
		};

	public:
		Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

		float GetFov() const { return _fov; }

		glm::mat4 LookAt() const;
		void Move(const Movement movement, const float deltaTime);
		void ProcessMouseOffset(const float xOffset, const float yOffset);
		void Zoom(const float yOffset);

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
	};
}

