#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Pos;

uniform sampler2D texture_diffuse1;
uniform samplerCube cube_texture;
uniform vec3 cameraPos;

void main()
{    
	float ratio = 1/1.52;
	vec3 dir = normalize( Pos - cameraPos);
	vec3 target = refract(dir, normalize(Normal),ratio);

    //FragColor = texture(texture_diffuse1, TexCoords);
    FragColor = texture(cube_texture, target);
}