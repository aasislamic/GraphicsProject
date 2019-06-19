#pragma once 

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {

private:
	std::string directory;
	std::vector<Mesh> meshes;
	void ProcessNode(aiNode * node, const aiScene * scene);
	Mesh ProcessMesh(aiMesh * mesh, const aiScene * scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName);

public:
	Model(const char*);
	void LoadModel(const char* path);
	Model();
	~Model();
	void Draw(Shader& shader);
};
