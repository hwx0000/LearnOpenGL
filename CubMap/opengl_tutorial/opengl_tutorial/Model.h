#pragma once
#include<string>
#include<vector>
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<iostream>
#include<string>


using std::cout;
using std::string;
using std::vector;

class Model
{
public:
	Model(const string& path);
	void LoadModel(const string& path);
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	void Draw(Shader *shader);
	unsigned int TextureFromFile(const char *path, const string &directory);

	vector<Mesh>meshes;
	string directory;
	vector<Texture>textures_loaded;

	~Model();
};

