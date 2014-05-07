#ifndef THINLENSCAMERA_H
#define THINLENSCAMERA_H
#include "Camera.h"

class ThinLensCamera:public Camera
{
	float lensRadius;
	float viewPlaneDistance;
	float focalPlaneDistance;
	float zoom;
public:
	ThinLensCamera(const glm::vec3& eye, const glm::vec3& lookat,float viewPlaneDistance,
		const glm::vec3& up,float focalDistance, float lensRadius,float zoom = 1.0,float exposureTime=1.0);
	ThinLensCamera(const glm::vec3& eye, const glm::vec3& lookat,float viewPlaneDistance
		,float focalDistance, float lensRadius,float zoom = 1.0,float exposureTime=1.0);

	virtual void renderScene(World* world);
	glm::vec3 rayDirection(const glm::vec2 pixelPoint, const glm::vec2 lensPoint) const;
};

#endif