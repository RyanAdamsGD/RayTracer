#ifndef SPHERICALPANORAMICCAMERA_H
#define SPHERICALPANORAMICCAMERA_H
#include "Camera.h"

class SphereicalPanoramicCamera:public Camera
{
	float verticalMax;
	float horizontalMax;

	glm::vec3 rayDirection(const glm::vec2& point, int hres, int vres, float pixelSize) const;
public:
	///horizontalMax/verticalMax must match the aspect Ratio otherwise there will be distortion
	SphereicalPanoramicCamera(const glm::vec3& eye, const glm::vec3& lookat,float verticalMax,
		float horizontalMax,const glm::vec3& up,float exposureTime=1.0f);
	///horizontalMax/verticalMax must match the aspect Ratio otherwise there will be distortion
	SphereicalPanoramicCamera(const glm::vec3& eye, const glm::vec3& lookat,float verticalMax
		,float horizontalMax,float exposureTime=1.0f);
	virtual void renderScene(World* world);
};

#endif