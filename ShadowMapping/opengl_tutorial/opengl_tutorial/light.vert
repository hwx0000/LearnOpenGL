#version 330 core
layout(location = 0)in vec3 aPos;
uniform mat3 model;
uniform mat3 lightView;
uniform mat3 lightProject;

void main()
{
	gl_Position = vec4(lightProject * lightView * model * aPos, 1.0f);
}