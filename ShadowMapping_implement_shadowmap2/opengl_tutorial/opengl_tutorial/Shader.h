#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>

using std::cout;
using std::endl;
using std::string;

class Shader
{
public:
	Shader(const char* vertexFilePath,const char* fragmentFilePath);
	void SetVertexShader(const char *);
	void SetFragmentShader(const char *);
	void Use();
	unsigned int GetID();
	void SetFloat(const char* name,float v);
	void SetVec3f(const char* name, float x, float y, float z);
	~Shader();
private:
	const char * _vertexShader;
	const char * _fragmentShader;
	unsigned int programID;
};
