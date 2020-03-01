#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include"Camera.h"

using std::cout;
using std::endl;
using std::string;

class Shader
{
public:
	Shader(const char* vertexFilePath,const char* fragmentFilePath,
		const char* geometryFilePath);
	Shader(const char* vertexFilePath, const char* fragmentFilePath);
	void setVertexShader(const char *);
	void setFragmentShader(const char *);
	void use()const;
	unsigned int getID()const;
	void setFloat(const char* name,float v)const;
	void setVec3f(const char* name, float x, float y, float z)const;
	void setVec3f(const char* name, glm::vec3 )const;
	void setInt(const char*, int x)const;
	void setMatrix4fv(const char*, glm::mat4 mat)const;
	void setMat4(const char*, glm::mat4)const;
	~Shader();
private:
	const char * _vertexShader;
	const char * _fragmentShader;
	unsigned int programID;
};
