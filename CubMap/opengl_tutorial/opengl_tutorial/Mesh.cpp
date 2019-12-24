#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	setupMesh();
}

void Mesh::Draw(Shader *shader)
{
	unsigned int diffuseNum = 1;
	unsigned int specularNum = 1;
	string number;
	for (unsigned int i = 0;  i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D,textures[i].ID);
		if (textures[i].type=="texture_diffuse")
		{
			diffuseNum++;
			number = std::to_string(diffuseNum);
		}
		if (textures[i].type=="texture_specular")
		{
			specularNum++;
			number = std::to_string(specularNum);
		}
		//这里的fragmentShader允许同时传入多个同种贴图，所以在这里针对其个数加了个序号
		glUniform1i(glGetUniformLocation(shader->GetID(),(
			"material."+textures[i].type+number).c_str()),i);
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}

void Mesh::setupMesh() 
{
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//为啥用&vertices就不行呢
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texCoord)));

	glBindVertexArray(0);
}


Mesh::~Mesh()
{
}
