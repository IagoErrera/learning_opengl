#ifndef FLY_CAMERA_H
#define FLY_CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"

class FlyCamera : public Camera {
private:
	float speed;
	float sensitivity;

	float lastMouseX, lastMouseY;

public:
	FlyCamera(
		glm::vec3 pos, glm::vec3 front, glm::vec3 up,
		float yaw, float pitch, float fov,
		float speed, float sensitivity
	);
    ~FlyCamera();	
	
	void movementHandle(GLFWwindow* window, float deltaTime);
	void mouseHandle(double xpos, double ypos);
	void scrollHandle(double yoffset);	

	void setSpeed(float value);
	void setSensitivity(float value);
};

#endif
