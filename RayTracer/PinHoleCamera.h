#ifndef PINHOLECAMERA_H
#define PINHOLECAMERA_H
#include "Camera.h"
#include <queue>
#include "boost\thread\mutex.hpp"

class PinHoleCamera:public Camera
{
	float viewPlaneDistance; //distance from viewplane
	float zoom; //zoom factor
	glm::vec3 rayDirection(const glm::vec2& point) const;
	std::queue<int*> pixels;
public:
	boost::try_mutex mtx;
	void displayPixel(World* world);
	PinHoleCamera();
	PinHoleCamera(const glm::vec3& eye, const glm::vec3& lookat,float viewPlaneDistance,
		const glm::vec3& up,float zoom = 1.0f,float exposureTime=1.0f);
	PinHoleCamera(const glm::vec3& eye, const glm::vec3& lookat,float viewPlaneDistance
		,float zoom = 1.0f,float exposureTime=1.0f);
	virtual void renderScene(World* world);

	inline void setViewPlaneDistance(float value) {viewPlaneDistance=value;}
	inline void setZoom(float value) {zoom=value;}
};

#endif