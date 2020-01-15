#include "Camera.h"



Camera::Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 _worldUp):
position(_position),
target(_target),
worldUp(glm::normalize(_worldUp))
{
	forward = glm::normalize(target - position);
	right = glm::cross(forward,worldUp);
	up = glm::cross(right, forward);
}

Camera::Camera(glm::vec3 _position, float _pitch, float _yaw, glm::vec3 _worldUp):
position(_position),
pitch(_pitch),
worldUp(glm::normalize(_worldUp)),
yaw(_yaw)
{
	forward.x = cos(glm::radians(pitch))*sin(glm::radians(yaw));
	forward.y = sin(glm::radians(pitch));
	forward.z = -cos(glm::radians(pitch))*cos(glm::radians(yaw));

	right = glm::cross(forward, glm::normalize(worldUp));
	up = glm::cross(right, forward);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + forward, worldUp);//第二个参数是方向，无所谓具体值
}

void Camera::UpdateCamera(float _pitchOffset, float _yawOffset)
{
	pitch += _pitchOffset;
	yaw += _yawOffset;
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	forward.x = cos(glm::radians(pitch))*sin(glm::radians(yaw));
	forward.y = sin(glm::radians(pitch));
	forward.z = -cos(glm::radians(pitch))*cos(glm::radians(yaw));

	right = glm::cross(forward, glm::normalize(worldUp));
	up = glm::cross(right, forward);

}



Camera::~Camera()
{
}
