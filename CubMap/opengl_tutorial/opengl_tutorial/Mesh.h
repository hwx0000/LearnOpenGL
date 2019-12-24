#pragma once
#include<glm/glm.hpp>
#include<iostream>
#include<vector>
#include "Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using std::string;
using std::vector;
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};


struct Texture
{
	unsigned int ID;
	aiString path;
	string type;
};


class Mesh
{
public:
	vector<Vertex>vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader *shader);
	~Mesh();
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();

};

