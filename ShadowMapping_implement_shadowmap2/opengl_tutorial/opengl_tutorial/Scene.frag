#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 posInLightCoords;

uniform sampler2D shadowMap;
uniform sampler2D texture1;

void main()
{
	if(posInLightCoords.z > texture(shadowMap, 
		vec2(posInLightCoords.x, posInLightCoords.y)).r)
		FragColor = vec4(0, 0, 0, 1) * texture(texture1, TexCoords);
	else
		FragColor = vec4(1,1,1,1)* texture(texture1, TexCoords);
}