#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

class Transform {
private:
	Shader* shader;
	std::string shader_property;
	
	glm::mat4 transform;
	
	float rotate_x;
	float rotate_y;
	float rotate_z;

	float translate_x;
	float translate_y;
	float translate_z;

	float scale_x;
	float scale_y;
	float scale_z;

	glm::vec3 vRotate;
	glm::vec3 vTranslate;
	glm::vec3 vScale;
public:	
	Transform(Shader* shader, const std::string property);
	~Transform();
	
	void reset();
	void rotate(float x, float y, float z);
	void translate(float x, float y, float z);
	void scale(float x, float y, float z);
	void apply() const;

	glm::mat4 getTransform() const;
	glm::vec3 getRotate() const;
	glm::vec3 getTranslate() const;
	glm::vec3 getScale() const;
};

#endif
