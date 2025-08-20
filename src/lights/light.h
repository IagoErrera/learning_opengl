#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"

class Light {
protected:
	unsigned int idx;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
public:
	Light(unsigned int idx, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	~Light();
	
	void setAmbient(glm::vec3 value);	
	void setDiffuse(glm::vec3 value);	
	void setSpecular(glm::vec3 value);	

	glm::vec3 getAmbient() const;
	glm::vec3 getDiffuse() const;
	glm::vec3 getSpecular() const;
	
	virtual void update(Shader& shader) const = 0;
};

#endif
