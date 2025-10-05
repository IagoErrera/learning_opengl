#include "texture2d.h"

Texture2D::Texture2D(
		const std::vector<std::string>& paths,
		const std::vector<std::string>& shaderTexNames,
		unsigned int n, 
		Shader shader
) : nTextures(n) {
	textures = new unsigned int[nTextures];

	shader.use();

	stbi_set_flip_vertically_on_load(true);
	
	for (unsigned int i = 0; i < nTextures; i++) {
		loadTexture(paths[i], shaderTexNames[i], i, textures[i], shader);
	}
}

Texture2D::Texture2D(
		const char* path,
		const char* shaderTexName,
		Shader shader
) : nTextures(1) {
	textures = new unsigned int[1];

	shader.use();

	stbi_set_flip_vertically_on_load(true);
	
	glGenTextures(1, &textures[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	loadTexture(path, shaderTexName, 0, textures[0], shader);
}

Texture2D::~Texture2D() {
	//glDeleteTextures(nTextures, textures);
	
	delete[] textures;
}

void Texture2D::loadTexture(
	const std::string& path,
	const std::string& name,
	unsigned int n,
	unsigned int& texture,
	Shader& shader
) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channels;
	unsigned char* data;
	
	data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (!data) {
		std::cout << "Fail on load texture" << std::endl;	
		stbi_image_free(data);
		throw std::runtime_error("Fail on load texture: " + path); 
	}
	
	GLenum format;
	if (channels == 1)
		format = GL_RED;
	else if (channels == 3)
		format = GL_RGB;
	else if (channels == 4)
		format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	shader.setInt(name, n);
}

void Texture2D::activate() {
	for (unsigned int i = 0; i < nTextures; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);	
	}
}

unsigned int* Texture2D::getTexturesID() { return textures; }
