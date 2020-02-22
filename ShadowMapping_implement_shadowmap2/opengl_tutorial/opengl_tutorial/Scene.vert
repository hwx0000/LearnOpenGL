#version 330 core
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec2 aTexCoords;

out vec2 TexCoords; 
out vec4 posInLightCoords;
uniform mat4 lightModel;
uniform mat4 lightView;
uniform mat4 lightProject;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	TexCoords = aTexCoords;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	posInLightCoords = lightProject * lightView * lightModel * vec4(aPos, 1.0f);
}