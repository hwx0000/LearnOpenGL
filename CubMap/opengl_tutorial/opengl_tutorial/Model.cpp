#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model::Model(string const& path)
{
	LoadModel(path);
}

Model::~Model()
{
}

void Model::LoadModel(string const& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene||scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)  
	{
		std::cout << "ASSIMP ERROR::" << importer.GetErrorString() << std::endl;
		return;
	}
	
	directory = path.substr(0, path.find_last_of('\\'));
	//std::cout << directory << std::endl;

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode * node,const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh,scene));
	}
	for (unsigned int  i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i],scene);
	}

}

//turn aiMesh to mesh
Mesh Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	//mesh由顶点、顶点索引 和贴图索引等因素组成
	//顶点由pos、normal和texCoord等组成
	vector<Vertex>vertices;
	vector<unsigned int>indices;
	vector<Texture>textures;

	//dig data for vertex
	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		//pos
		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;
		//normal
		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;
		//texCoord
		if (mesh->mTextureCoords[0])
		{
			vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.texCoord = glm::vec2(0.0f, 0.0f);
			cout << "Failed to load texCoord in ProcessMesh " << endl;
		}

		vertices.push_back(vertex);
	}

	//dig indices from each face
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
		{
			indices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}

	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. load diffuse maps ,named texture_diffuse
	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. load specular maps
	vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. load normal maps
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	

	Mesh result(vertices,indices,textures);
	return result;
}

void Model::Draw(Shader * shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{   // 如果纹理还没有被加载，则加载它
			Texture texture;
			texture.ID = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture); // 添加到已加载的纹理中
		}
	}
	return textures;
}


unsigned int Model::TextureFromFile(const char *path, const string &directory)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

/*//只挖顶点坐标和索引值
vector<InputMesh> Model::GetInputMesh()
{
	vector<InputMesh> result;
	for (size_t i = 0; i < meshes.size(); i++)
	{
		InputMesh mesh;
		for (size_t j = 0; j < meshes[i].vertices.size(); j++)
		{
			mesh.vertices.push_back(meshes[i].vertices[j].position.x);
			mesh.vertices.push_back(meshes[i].vertices[j].position.y);
			mesh.vertices.push_back(meshes[i].vertices[j].position.z);
		}
		for (size_t j = 0; j < meshes[i].indices.size(); j++)
		{
			mesh.indices.push_back(meshes[i].indices[j]);
		}
		result.push_back(mesh);
	}

	return result;
}
*/