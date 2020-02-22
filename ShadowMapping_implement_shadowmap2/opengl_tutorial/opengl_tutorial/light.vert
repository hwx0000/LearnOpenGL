#version 330 core
layout(location = 0)in vec3 aPos;
uniform mat4 lightModel;
uniform mat4 lightView;
uniform mat4 lightProject;

void main()
{
	gl_Position = lightProject * lightView * lightModel * vec4(aPos,1.0f);
}