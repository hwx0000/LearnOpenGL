#pragma once
#include "Shader.h"

using std::ifstream;
using std::exception;
using std::stringstream;

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
{
	ifstream vertexFile;
	ifstream fragmentFile;
	const char* vertexShaderSource;
	const char* fragmentShaderSource;
	string vertexString;
	string fragmentString;

	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
	try
	{
		vertexFile.open(vertexFilePath);
		fragmentFile.open(fragmentFilePath);
		
		stringstream vertexStringStream;
		stringstream fragmentStringStream;
		vertexStringStream << vertexFile.rdbuf();
		fragmentStringStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexString = vertexStringStream.str();
		fragmentString = fragmentStringStream.str();

		vertexShaderSource = vertexString.c_str();
		fragmentShaderSource = fragmentString.c_str();
	}
	catch (ifstream::failure f)
	{
		std::cout << "Failed to open shader file!!" << std::endl;
	}


	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success1 = 0;
	char infoLog1[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success1);
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog1);
	if (!success1)
	{
		cout << "Failed to compile vertexShader!!" << endl;
		cout << infoLog1 << endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	int success2 = 0;
	char infoLog2[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);
	if (!success2)
	{
		cout << infoLog2<< endl;
		cout << "Failed to compile fragmentShader!!" << endl;
	}
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	int success3 = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &success3);
	if (!success3)
	{
		cout << "Failed to link shader program!!" << endl;
	}

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	
	//glUseProgram(GetID());

}

void Shader::SetVertexShader(const char * vertexInput)
{
	_vertexShader = vertexInput;
}


void Shader::Use() 
{
	glUseProgram(programID);

}

void Shader::SetFragmentShader(const char * fragmentInput)
{
	_fragmentShader = fragmentInput;
}

unsigned int Shader::GetID() 
{
	return this->programID;
}

void Shader::SetFloat(const char* name, float v)
{
	glUniform1f(glGetUniformLocation(programID, name), v);
}

void Shader::SetVec3f(const char* name,float x,float y,float z)
{
	glUniform3f(glGetUniformLocation(programID, name), x, y, z);
}


Shader::~Shader()
{
}
