#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW			= -90.0f;
const float PITCH		= 0.0f;
const float SPEED		= 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM		= 45.0f;

class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(
		glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f), 
		float _yaw = YAW, 
		float _pitch = PITCH
	)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
		MovementSpeed(SPEED), 
		MouseSensitivity(SENSITIVITY), 
		Zoom(ZOOM) {

		Position = _position;
		WorldUp = _up;
		Yaw = _yaw;
		Pitch = _pitch;

		UpdateCameraVectors();
	}

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(Position, Position + Front, WorldUp);
	}

	void ProcessKeyboard(Camera_Movement direction, float DeltaTime) {
		float Velocity = MovementSpeed * DeltaTime;

		if (direction == FORWARD) {
			Position += Front * Velocity;
		} 
		
		if (direction == BACKWARD) {
			Position -= Front * Velocity;
		}

		if (direction == LEFT) {
			Position -= Right * Velocity;
		}

		if (direction == RIGHT) {
			Position += Right * Velocity;
		}
	}

	void ProcessMouseMovement(float xoffset, float yoffset) {
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (Pitch > 89.0f) {
			Pitch = 89.0f;
		}
		if (Pitch < -89.0f) {
			Pitch = -89.0f;
		}

		UpdateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset) {
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f) {
			Zoom = 1.0f;
		}
		if (Zoom > 45.0f) {
			Zoom = 45.0f;
		}
	}

private:
	void UpdateCameraVectors() {
		glm::vec3 TempFront;
		TempFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		TempFront.y = sin(glm::radians(Pitch));
		TempFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(TempFront);

		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};