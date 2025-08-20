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

	void loadTexture(const std::string& path, const std::string& name, unsigned int n, unsigned int& texture, Shader& shader);
public:
	Texture(const std::vector<std::string>& paths, const std::vector<std::string>& shaderTexNames, unsigned int nTextures, Shader shader);
	Texture(const char* paths, const char* shaderTexName, Shader shader);
	~Texture();
	
	void activate();
	unsigned int* getTexturesID();
};

#endif
