#version 330 core
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec3 aNormal;
layout(location = 2)in vec2 aTexCoords;

out vec2 TexCoords; 
out vec3 Normal;
out vec4 PosInLightCoords;
out vec3 FragPos;

uniform mat4 lightModel;
uniform mat4 lightView;
uniform mat4 lightProjection;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = transpose(inverse(mat3(model))) * aNormal;
    TexCoords = aTexCoords;
    PosInLightCoords = lightProjection * lightView * vec4(FragPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}