#include "light.h"

Light::Light(unsigned int idx, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
	idx{idx}, ambient{ambient}, diffuse{diffuse}, specular{specular} {}

Light::~Light() {}

void Light::setAmbient(glm::vec3 value) {
	ambient = value;
}

void Light::setDiffuse(glm::vec3 value) {
	diffuse = value;
}

void Light::setSpecular(glm::vec3 value) {
	diffuse = value;
}

glm::vec3 Light::getAmbient() const {
	return ambient;
}

glm::vec3 Light::getDiffuse() const {
	return diffuse;
}

glm::vec3 Light::getSpecular() const {
	return specular;
}
