#include "mesh.h"

Mesh::Mesh(
		std::vector<Vertex> vertices,
		std::vector<unsigned int> indices,
		std::vector<Texture> textures
) : vertices{vertices}, indices{indices}, textures{textures} {
	setupMesh();
}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vertex),
		&vertices[0],
		GL_STATIC_DRAW
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(unsigned int),
		&indices[0],
		GL_STATIC_DRAW
	);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, biTangent));
	
	glBindVertexArray(0);
}

void Mesh::draw(Shader& shader) {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = textures[i].type;
		
		if (name == "texture_diffuse") {
			name = "material.diffuse[" + std::to_string(diffuseNr) + "]";
			shader.setInt("material.n_diffuse", diffuseNr);
			number = std::to_string(diffuseNr++);
		} else if (name == "texture_specular") { 
			name = "material.specular[" + std::to_string(specularNr) + "]";
			shader.setInt("material.n_specular", diffuseNr);
			number = std::to_string(specularNr++);
		} else if (name == "texture_normal") {
			name = "material.normal[" + std::to_string(normalNr) + "]";
			//shader.setInt("material.n_diffuse", diffuseNr);
			number = std::to_string(normalNr++);
			continue;
		} else if (name == "texture_height") {
			name = "material.height[" + std::to_string(heightNr) + "]";
			//shader.setInt("material.n_diffuse", diffuseNr);
			number = std::to_string(heightNr++);
			continue;
		}
		
		shader.setInt((name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); 	
	glBindVertexArray(0);	
}
