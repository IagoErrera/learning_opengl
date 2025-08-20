#include "directionalLight.h"

DirectionalLight::DirectionalLight(
	unsigned int idx,
	glm::vec3 ambient,
	glm::vec3 diffuse,
	glm::vec3 specular,
	glm::vec3 direction
) : Light(idx, ambient, diffuse, specular), direction{direction} {}

DirectionalLight::~DirectionalLight() {};

void DirectionalLight::update(Shader& shader) const {
	shader.setVec3("directionalLights[" + std::to_string(idx) + "].direction", direction);
	shader.setVec3("directionalLights[" + std::to_string(idx) + "].ambient", ambient);
	shader.setVec3("directionalLights[" + std::to_string(idx) + "].diffuse", diffuse);
	shader.setVec3("directionalLights[" + std::to_string(idx) + "].specular", specular);
}

glm::vec3 DirectionalLight::getDirection() const {
	return direction;
}

void DirectionalLight::setDirection(glm::vec3 value) {
	direction = value;
} 
