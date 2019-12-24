#pragma once
#include<iostream>
#include<glm/glm.hpp>


class Light
{
public:
	Light(glm::vec3 _position, glm::vec3 _ambient,glm::vec3 _diffuse,glm::vec3 _specular);
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	const float constant = 1.0f;
	const float linear = 0.09f;
	const float quadratic = 0.032f;
	~Light();
};

