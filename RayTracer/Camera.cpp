#include "Camera.h"
#include "DebugMemory.h"

Camera::Camera()
	:exposureTime(1.0f),up(glm::vec3(0,1,0))
{
}

Camera::~Camera()
{
}

Camera::Camera(glm::vec3 eye, glm::vec3 lookat, glm::vec3 up,float exposureTime)
	:eye(eye),lookat(lookat),up(up),exposureTime(exposureTime)
{
	computeUVW();
}

void Camera::computeUVW()
{
	w = eye - lookat;
	w = glm::normalize(w);
	u = glm::cross(up,w);
	u = glm::normalize(u);
	v = glm::cross(u,w);

	//handle looking straight up or down
	if(eye.x == lookat.x && eye.z == lookat.z && lookat.y > eye.y)
	{
		u = glm::vec3(0,0,1);
		v = glm::vec3(1,0,0);
		w = glm::vec3(0,1,0);
	}

	if(eye.x == lookat.x && eye.z == lookat.z && eye.y < lookat.y) 
	{ 
		u = glm::vec3(1, 0, 0);
		v = glm::vec3(0, 0, 1);
		w = glm::vec3(0, -1, 0);
	}
}