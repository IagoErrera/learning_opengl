#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "light.h"
#include "shader.h"

class SpotLight : Light {
private:
	glm::vec3 position;
	glm::vec3 direction;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;
public:
	SpotLight(
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
	);
	~SpotLight();

	glm::vec3 getPosition() const;
	glm::vec3 getDirection() const;
	float getConstant() const;
	float getLinear() const;
	float getQuadratic() const;
	float getCutOff() const;
	float getOuterCutOff() const;

	void setPosition(glm::vec3 value);
	void setDirection(glm::vec3 value);
	void setConstant(float value);
	void setLinear(float value);
	void setQuadratic(float value);
	void setCutOff(float value);
	void setOuterCutOff(float value);

	virtual void update(Shader& shader) const;
};

#endif
