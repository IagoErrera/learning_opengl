#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "light.h"
#include "shader.h"

class PointLight : Light {
private:
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;
public:
	PointLight(
		unsigned int idx,
		glm::vec3 ambient,
		glm::vec3 diffuse,
		glm::vec3 specular,
		glm::vec3 position,
		float constant,
		float linear,
		float quadratic
	);
	~PointLight();

	glm::vec3 getPosition() const;
	float getConstant() const;
	float getLinear() const;
	float getQuadratic() const;

	void setPosition(glm::vec3 value);
	void setConstant(float value);
	void setLinear(float value);
	void setQuadratic(float value);

	virtual void update(Shader& shader) const;
};

#endif
