#include "texture.h"

Texture::Texture(
		const std::vector<std::string>& paths,
		const std::vector<std::string>& shaderTexNames,
		unsigned int n, 
		Shader shader
) : nTextures(n) {
	textures = new unsigned int[nTextures];

	shader.use();

	stbi_set_flip_vertically_on_load(true);
	
	int width, height, channels;
	unsigned char* data;
	for (unsigned int i = 0; i < nTextures; i++) {
		glGenTextures(1, &textures[i]);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		data = stbi_load(paths[i].c_str(), &width, &height, &channels, 0);

		if (!data) {
			std::cout << "Fail on load texture" << std::endl;	
			throw std::runtime_error("Fail on load texture: " + paths[i]); 
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		shader.setInt(shaderTexNames[i], i);
	}
}

Texture::~Texture() {
	//glDeleteTextures(nTextures, textures);
	
	delete[] textures;
}

void Texture::activate() {
	for (unsigned int i = 0; i < nTextures; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);	
	}
}
