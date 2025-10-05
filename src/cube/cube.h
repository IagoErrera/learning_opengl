#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>

#include "shader.h"
#include "utils.h"
#include "texture2d.h"
#include "transform.h"

class Cube {
private:
	static unsigned int VAO, VBO;
	static bool initialized;
	bool outline;
	float outline_scale;
	Shader* shader;
	Shader* outline_shader;
	Texture2D* texture;

	static void initDrawer();
public:
	Cube(Shader* shader, Texture2D* texture);
	void enableOutline(Shader* outline_shader, float outline_scale = 1.1f);
	void drawOutline(Shader* shader, float scale);
	void draw() const;
	void draw(Shader* s) const;
	
	Transform transform;
	Transform* outline_transform;
};

#endif
