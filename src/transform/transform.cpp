#include "transform.h"

Transform::Transform(Shader* shader, const std::string property) : 
	shader{shader}, shader_property{property},
	transform{glm::mat4(1.0f)},
	vRotate{glm::vec3(0.0f,0.0f,0.0f)},
	vTranslate{glm::vec3(0.0f,0.0f,0.0f)},
	vScale{glm::vec3(1.0f,1.0f,1.0f)}
{};

Transform::~Transform() {};

void Transform::reset() {
	transform = glm::mat4(1.0f);
	
	vRotate = glm::vec3(0.0,0.0,0.0);
	vTranslate = glm::vec3(0.0,0.0,0.0);
	vScale = glm::vec3(1.0,1.0,1.0);
}

void Transform::rotate(float x, float y, float z) {
	vRotate += glm::vec3(x,y,z);
	
	if (x != 0) transform = glm::rotate(transform, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	if (y != 0) transform = glm::rotate(transform, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	if (z != 0) transform = glm::rotate(transform, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Transform::translate(float x, float y, float z) {	
	glm::vec3 translation(x,y,z);
	vTranslate += translation;

	transform = glm::translate(transform, translation);
}

void Transform::scale(float x, float y, float z) {
	glm::vec3 scalling(x, y, z);
	vScale += scalling;

	transform = glm::scale(transform, scalling);
};

void Transform::apply() const {
	shader->setMat4(shader_property, transform);
};

glm::mat4 Transform::getTransform() const {
	return transform;
}

glm::vec3 Transform::getRotate() const {
	return vRotate;
}

glm::vec3 Transform::getTranslate() const {
	return vTranslate;
}

glm::vec3 Transform::getScale() const {
	return vScale;
}
