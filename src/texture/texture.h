#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include "stb_image.h"

#include <iostream>
#include <string>
#include <exception>
#include <vector>

#include "shader.h"

class Texture {
private:
	unsigned int nTextures;
	unsigned int* textures;
public:

	Texture(const std::vector<std::string>& paths, const std::vector<std::string>& shaderTexNames, unsigned int nTextures, Shader shader);
	~Texture();
	
	void activate();
};

#endif
