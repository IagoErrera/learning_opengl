#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include "stb_image.h"

#include <iostream>
#include <string>
#include <exception>
#include <vector>

#include "shader.h"

class Texture2D {
private:
	unsigned int nTextures;
	unsigned int* textures;

	void loadTexture(const std::string& path, const std::string& name, unsigned int n, unsigned int& texture, Shader& shader);
public:
	Texture2D(const std::vector<std::string>& paths, const std::vector<std::string>& shaderTexNames, unsigned int nTextures, Shader shader);
	Texture2D(const char* paths, const char* shaderTexName, Shader shader);
	~Texture2D();
	
	void activate();
	unsigned int* getTexturesID();
};

#endif
