#include "flyCamera.h"

FlyCamera::FlyCamera(
	glm::vec3 pos, glm::vec3 front, glm::vec3 up,
	float yaw, float pitch, float fov,
	float speed, float sensitivity
) : Camera(pos, front, up, yaw, pitch, fov),
	speed{speed}, sensitivity{sensitivity}
{}

FlyCamera::~FlyCamera() {}

void FlyCamera::movementHandle(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) move(DIRECTION::BACK, deltaTime * speed);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) move(DIRECTION::FORWARD, deltaTime * speed); 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) move(DIRECTION::LEFT, deltaTime * speed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) move(DIRECTION::RIGHT, deltaTime * speed);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) move(DIRECTION::UP, deltaTime * speed);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) move(DIRECTION::DOWN, deltaTime * speed);
}

void FlyCamera::mouseHandle(double xpos, double ypos) {
	float xoffset = (xpos - lastMouseX) * sensitivity;
	float yoffset = (ypos - lastMouseY) * sensitivity;
	lastMouseX = xpos; lastMouseY = ypos;

	rotate(ROTATE_TYPE::YAW,   xoffset);
	rotate(ROTATE_TYPE::PITCH, -yoffset);
}

void FlyCamera::scrollHandle(double yoffset) {
	fov -= (float)yoffset;
	if (fov < 1.0f) fov = 1.0;
    else if (fov > 45.0f) fov = 45.0f;
}

void FlyCamera::setSpeed(float value) { speed = value; }

void FlyCamera::setSensitivity(float value) { sensitivity = value; }
