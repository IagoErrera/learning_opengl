#include "camera.h"

Camera::Camera(
	glm::vec3 pos, glm::vec3 front, glm::vec3 up,
	float yaw, float pitch, float fov 
) : position{pos}, front{front}, worldUp{up},
	yaw{yaw}, pitch{pitch}, fov{fov}
{
	updateCameraVectors();
}

Camera::~Camera() {}

void Camera::move(DIRECTION direction, float value) {
	switch (direction) {
		case DIRECTION::FORWARD:
			position += front * value;
			break;
		case DIRECTION::BACK:
			position -= front * value;
			break;
		case DIRECTION::UP:
			position += value * up;
			break;
		case DIRECTION::DOWN:
			position -= value * up;
			break;
		case DIRECTION::RIGHT:
			position += value * glm::normalize(glm::cross(front, up));
			break;
		case DIRECTION::LEFT:
			position -= value * glm::normalize(glm::cross(front, up));
			break;
	}
}

void Camera::rotate(ROTATE_TYPE type, float value) {
	switch (type) {
		case ROTATE_TYPE::YAW:
			yaw += value;
			break;
		case ROTATE_TYPE::PITCH:
			pitch += value;
			if (pitch > 90.0f) pitch = 90.0f;
			else if (pitch < -90) pitch = -90.0f;
			break;
	}
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, position + front, up);
}

void Camera::setPosition(glm::vec3 pos) {
	position = pos;
}

void Camera::setFront(glm::vec3 front) {
	this->front = front;
}

void Camera::setUp(glm::vec3 up) {
	this->up = up;
}

void Camera::setYaw(float value) {
	yaw = value;
}

void Camera::setPitch(float value) {
	pitch = value;
}

void Camera::setFov(float value) {
	fov = value;
}

void Camera::setNear(float value) {
	near = value;
}

void Camera::setFar(float value) {
	far = value;
}

glm::vec3 Camera::getPosition() const {
	return position;
}

glm::vec3 Camera::getFront() const {
	return front;
}

glm::vec3 Camera::getUp() const {
	return up;
}

float Camera::getYaw() const {
	return yaw;
}

float Camera::getPitch() const {
	return pitch;
}

float Camera::getFov() const {
	return fov;
}

void Camera::update(Shader shader, float aspectRatio, const char* viewName, const char* projName) const {
	shader.setMat4(viewName, getViewMatrix());
	shader.setMat4(projName, glm::perspective(glm::radians(fov), aspectRatio, near, far));		
}

void Camera::updateCameraVectors() {
	glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front       = glm::normalize(direction);

	right = glm::normalize(glm::cross(front, worldUp));
	up    = glm::normalize(glm::cross(right, front));
}
