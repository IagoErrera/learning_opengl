#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>
#include <exception>
#include <iostream>

#include "mesh.h"
#include "shader.h"
#include "utils.h"

// Remember to refactor -> Parent-Child Realtionship -> Decomposing in multiples/separate objects
// > Modify processModel method -> Set each child as a separete related model
// > Add a hierarchical system
// > Pay attention how to relate it with transform

class Model {
private:
	std::vector<Mesh> meshes;
	std::vector<Texture> textures_loaded;
	std::string directory;
	
	void loadModel(std::string path);
	void processModel(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
	Model(const char* path);
	~Model();

	void draw(Shader& shader);

};

#endif
