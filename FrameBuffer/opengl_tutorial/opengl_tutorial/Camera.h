#pragma once
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using std::cout;
using std::endl;



class Camera
{
public:
	Camera(glm::vec3 _position,glm::vec3 _target,glm::vec3 _worldUp);
	Camera(glm::vec3 _position, float _pitch, float _yaw, glm::vec3 _worldUp);
	void UpdateCamera(float _pitchOffset, float _yawOffset);
	glm::mat4 GetViewMatrix();
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up; 
	~Camera();
private:
	glm::vec3 target;
	glm::vec3 worldUp;
	glm::vec3 right;
	float pitch;
	float yaw;
};

