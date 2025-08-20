#include "spotLight.h"

SpotLight::SpotLight(
	unsigned int idx,
	glm::vec3 ambient,
	glm::vec3 diffuse,
	glm::vec3 specular,
	glm::vec3 position,
	glm::vec3 direction,
	float constant,
	float linear,
	float quadratic,
	float cutOff,
	float outerCutOff
) : Light(idx, ambient, diffuse, specular), 
	position{position}, direction{direction},
	constant{constant}, linear{linear}, quadratic{quadratic},
	cutOff{cutOff}, outerCutOff{outerCutOff} {}

SpotLight::~SpotLight() {}

glm::vec3 SpotLight::getPosition() const {
	return position;
}

glm::vec3 SpotLight::getDirection() const {
	return direction;
}

float SpotLight::getConstant() const {
	return constant;
} 

float SpotLight::getLinear() const {
	return linear;
}

float SpotLight::getQuadratic() const {
	return quadratic;
}

void SpotLight::setPosition(glm::vec3 value) {
	position = value;
}

void SpotLight::setDirection(glm::vec3 value) {
	direction = value;
}

void SpotLight::setConstant(float value) {
	constant = value;
}

void SpotLight::setLinear(float value) {
	linear = value;
}

void SpotLight::setQuadratic(float value) {
	quadratic = value;
}

void SpotLight::update(Shader& shader) const {
	shader.setVec3("spotLights[" + std::to_string(idx) + "].position", position);
	shader.setVec3("spotLights[" + std::to_string(idx) + "].direction", direction);
	shader.setVec3("spotLights[" + std::to_string(idx) + "].ambient", ambient);
	shader.setVec3("spotLights[" + std::to_string(idx) + "].diffuse", diffuse);
	shader.setVec3("spotLights[" + std::to_string(idx) + "].specular", specular);
	shader.setFloat("spotLights[" + std::to_string(idx) + "].constant", constant);
	shader.setFloat("spotLights[" + std::to_string(idx) + "].linear", linear);
	shader.setFloat("spotLights[" + std::to_string(idx) + "].quadratic", quadratic);	
	shader.setFloat("spotLights[" + std::to_string(idx) + "].cutOff", cutOff);	
	shader.setFloat("spotLights[" + std::to_string(idx) + "].outerCutOff", outerCutOff);	
}
