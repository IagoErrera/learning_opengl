#include "transform.h"

Transform::Transform(Shader* shader, const std::string property) : 
	shader{shader}, shader_property{property},
	vRotate{glm::vec3(0.0f,0.0f,0.0f)},
	vTranslate{glm::vec3(0.0f,0.0f,0.0f)},
	vScale{glm::vec3(1.0f,1.0f,1.0f)}
{};

Transform::~Transform() {};

void Transform::reset() {
	vRotate = glm::vec3(0.0,0.0,0.0);
	vTranslate = glm::vec3(0.0,0.0,0.0);
	vScale = glm::vec3(1.0,1.0,1.0);
}

void Transform::rotate(float x, float y, float z) {
	vRotate += glm::vec3(x,y,z);
}

void Transform::rotate(glm::vec3 rotation) {
	vRotate += rotation;
}

void Transform::setRotate(glm::vec3 rotation) { vRotate = rotation; };

void Transform::translate(float x, float y, float z) {	
	glm::vec3 translation(x,y,z);
	vTranslate += translation;
}

void Transform::translate(glm::vec3 translation) {
	vTranslate += translation;
}

void Transform::setTranslate(glm::vec3 translation) { vTranslate = translation; }

void Transform::scale(float x, float y, float z) {
	glm::vec3 scalling(x, y, z);
	vScale += scalling;
};

void Transform::scale(glm::vec3 scalling) {
	vScale += scalling;
}

void Transform::setScale(glm::vec3 scale) { vScale = scale; }

void Transform::update() const {
	shader->setMat4(shader_property, getTransform());
};

glm::mat4 Transform::getTransform() const {
	glm::mat4 transform(1.0f);
			
	transform = glm::rotate(transform, vRotate.x, glm::vec3(1.0f, 0.0f, 0.0f));	
	transform = glm::rotate(transform, vRotate.y, glm::vec3(0.0f, 1.0f, 0.0f));	
	transform = glm::rotate(transform, vRotate.z, glm::vec3(0.0f, 0.0f, 1.0f));	
	
	transform = glm::translate(transform, vTranslate);	
	
	transform = glm::scale(transform, vScale);
		
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
