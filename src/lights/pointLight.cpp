#include "pointLight.h"

PointLight::PointLight(
	unsigned int idx,
	glm::vec3 ambient,
	glm::vec3 diffuse,
	glm::vec3 specular,
	glm::vec3 position,
	float constant,
	float linear,
	float quadratic
) : Light(idx, ambient, diffuse, specular), 
	position{position}, constant{constant}, linear{linear}, quadratic{quadratic} {}

PointLight::~PointLight() {}

glm::vec3 PointLight::getPosition() const {
	return position;
}

float PointLight::getConstant() const {
	return constant;
} 

float PointLight::getLinear() const {
	return linear;
}

float PointLight::getQuadratic() const {
	return quadratic;
}

void PointLight::setPosition(glm::vec3 value) {
	position = value;
}

void PointLight::setConstant(float value) {
	constant = value;
}

void PointLight::setLinear(float value) {
	linear = value;
}

void PointLight::setQuadratic(float value) {
	quadratic = value;
}

void PointLight::update(Shader& shader) const {
	shader.setVec3("pointLights[" + std::to_string(idx) + "].position", position);
	shader.setVec3("pointLights[" + std::to_string(idx) + "].ambient", ambient);
	shader.setVec3("pointLights[" + std::to_string(idx) + "].diffuse", diffuse);
	shader.setVec3("pointLights[" + std::to_string(idx) + "].specular", specular);
	shader.setFloat("pointLights[" + std::to_string(idx) + "].constant", constant);
	shader.setFloat("pointLights[" + std::to_string(idx) + "].linear", linear);
	shader.setFloat("pointLights[" + std::to_string(idx) + "].quadratic", quadratic);	
}
