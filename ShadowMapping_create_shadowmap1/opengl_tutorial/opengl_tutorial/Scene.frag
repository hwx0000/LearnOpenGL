#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
	float a = texture(texture1, TexCoords).r;
	FragColor = vec4(a,a,a,1);
}