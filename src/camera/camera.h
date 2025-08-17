#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#include "shader.h"

enum class DIRECTION {
	FORWARD,
	BACK,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum class ROTATE_TYPE {
	YAW,
	PITCH
};

class Camera {
protected:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;
	float fov;

	void updateCameraVectors();

	float near = 0.1;
	float far  = 100.0;
public:
	Camera(
		glm::vec3 pos, glm::vec3 front, glm::vec3 up,
		float yaw, float pitch, float fov 
	);
	~Camera();

	void setPosition(glm::vec3 pos);
	void setFront(glm::vec3 fron);
	void setUp(glm::vec3 up);

	void setYaw(float value);
	void setPitch(float value);
	void setFov(float value);

	void setNear(float value);
	void setFar(float value);

	void move(DIRECTION direction, float value);
	void rotate(ROTATE_TYPE type, float value);

	glm::mat4 getViewMatrix() const;
		
	glm::vec3 getPosition() const;	
	glm::vec3 getFront() const;	
	glm::vec3 getUp() const;	

	float getYaw() const;
	float getPitch() const;
	float getFov() const;

	void update(Shader shader, float astpectRatio, const char* viewName, const char* projName) const;
};

#endif
