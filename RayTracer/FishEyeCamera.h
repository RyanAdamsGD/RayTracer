#ifndef FISHEYECAMERA_H
#define FISHEYECAMERA_H
#include "Camera.h"

class FishEyeCamera: public Camera
{
	float psiMax;
	glm::vec3 rayDirection(const glm::vec2& point, int hres, int vres, float pixelSize, float* radius) const;
public:
	FishEyeCamera(const glm::vec3& eye, const glm::vec3& lookat,float psiMax,
		const glm::vec3& up,float exposureTime=1.0);
	FishEyeCamera(const glm::vec3& eye, const glm::vec3& lookat,float psiMax
		,float exposureTime=1.0);
	virtual void renderScene(World* world);
};

#endif