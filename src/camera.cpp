#include "../include/camera.h"

#include <glm/gtc/matrix_transform.hpp>

const float SENSITIVITY = 0.1f;
const float BASE_SPEED = 0.2f;
const float CROUCH_SPEED = 0.05f;
const float SPRINT_SPEED = 0.8f;

Camera::Camera(float yaw, float pitch, glm::vec3 position, glm::vec3 direction, glm::vec3 upwards, glm::mat4 projection) {
	this->yaw = yaw;
	this->pitch = pitch;
	this->position = position;
	this->direction = direction;
	this->upwards = upwards;
	this->projection = projection;
}

void Camera::handleMouseMovement(float xOffset, float yOffset) {
	yaw += xOffset * SENSITIVITY;
	pitch += yOffset * SENSITIVITY;

	// Clamp pitch
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);
	this->direction = direction;
}

void Camera::handleKeyboard(glm::vec3 direction, float deltaTime) {
	glm::vec3 lastPos = position;

	direction = glm::normalize(direction);
	float velocity = 50.0f * deltaTime;
	direction *= velocity;

	float moveSpeed;
	if (sprint) {
		moveSpeed = SPRINT_SPEED;
	}
	else if (crouch) {
		moveSpeed = CROUCH_SPEED;
	}
	else {
		moveSpeed = BASE_SPEED;
	}


	position -= glm::normalize(this->direction) * direction.z * moveSpeed;

	//right
	glm::vec3 right = glm::normalize(glm::cross(this->direction, upwards));
	position += right * direction.x * moveSpeed;

	//up
	position += glm::normalize(upwards) * direction.y * moveSpeed;

	printf("deltaPos: %f\n", glm::length(position - lastPos));
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + direction, upwards);
}

glm::mat4 Camera::getProjectionMatrix() {
	return projection;
}

glm::vec3 Camera::getPosition() {
	return position;
}

glm::vec3 Camera::getDirection() {
	return direction;
}

void Camera::setSprint(bool sprint) {
	this->sprint = sprint;
}

void Camera::setCrouch(bool crouch) {
	this->crouch = crouch;
}
