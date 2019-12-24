#version 330 core
in vec3 Normal;
in vec3 Pos;
uniform samplerCube skybox;
uniform vec3 cameraPos;
out vec4 fragColor;

void main()
{
	vec3 dir =  normalize(Pos - cameraPos);
	vec3 target = reflect(dir,normalize(Normal));
	//fragColor = texture(skybox,target);
	fragColor = vec4(texture(skybox,target).rgb,1.0);
}