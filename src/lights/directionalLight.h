#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "light.h"
#include "shader.h"

class DirectionalLight : Light {
private:
	glm::vec3 direction;
public:
	DirectionalLight(
		unsigned int idx,
		glm::vec3 ambient,
		glm::vec3 diffuse,
		glm::vec3 specular,
		glm::vec3 direction
	);
	~DirectionalLight();
	
	glm::vec3 getDirection() const;
	void setDirection(glm::vec3 value);

	virtual void update(Shader& shader) const;

};

#endif
