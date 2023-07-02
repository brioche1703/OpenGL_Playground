#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Playground
{
	Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
		:
		_pos(pos),
		_front(front),
		_up(up)
	{}
	glm::mat4 Camera::LookAt() const
	{
			return glm::lookAt(
				_pos,
				_pos + _front,
				_up
			);
	}
	void Camera::Move(const Movement movement, const float deltaTime)
	{
		switch (movement)
		{
		case FORWARD:
			_pos += _speed * _front;
			break;
		case BACKWARD:
			_pos -= _speed * _front;
			break;
		case LEFT:
			_pos -= _speed * GetRightVector();
			break;
		case RIGHT:
			_pos += _speed * GetRightVector();
			break;
		case UP:
			_pos += _speed * _up;
			break;
		case DOWN:
			_pos -= _speed * _up;
			break;
		}
	}
	void Camera::ProcessMouseOffset(const float xOffset, const float yOffset)
	{
		_yaw += xOffset;
		_pitch += yOffset;

		if (_pitch > 89.0f)
		{
			_pitch = 89.0f;
		}
		if (_pitch < -89.0f)
		{
			_pitch = -89.0f;
		}

		glm::vec3 newDirection(
			cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)),
			sin(glm::radians(_pitch)),
			sin(glm::radians(_yaw)) * cos(glm::radians(_pitch))
		);

		_front = glm::normalize(newDirection);
	}
	void Camera::Zoom(const float yOffset)
	{
		_fov -= yOffset;
		if (_fov < 1.0f)
		{
			_fov = 1.0f;
		}
		else if (_fov > 45.0f)
		{
			_fov = 45.0f;
		}
	}
	glm::vec3 Camera::GetRightVector() const
	{
		return glm::normalize(glm::cross(_front, _up));
	}
}
