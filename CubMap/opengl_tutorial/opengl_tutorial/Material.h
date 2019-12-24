#pragma once
#include "Shader.h"
#include<glm/glm.hpp>

class Material
{
public:
	Material();
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shineness;
	~Material();
};

