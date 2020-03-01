#version 330 core

in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main()
{
	float dist = length(FragPos.xyz - lightPos);
	dist = dist/far_plane;
	gl_FragDepth = dist;
}