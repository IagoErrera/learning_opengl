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
	void update() const;
	
	void rotate(float x, float y, float z);
	void rotate(glm::vec3 rotation);
	void setRotate(glm::vec3 rotation);
	
	void translate(float x, float y, float z);
	void translate(glm::vec3 translation);
	void setTranslate(glm::vec3 translation);
	
	void scale(float x, float y, float z);
	void scale(glm::vec3 scalling);
	void setScale(glm::vec3 scalling);

	glm::mat4 getTransform() const;
	glm::vec3 getRotate() const;
	glm::vec3 getTranslate() const;
	glm::vec3 getScale() const;
};

#endif
