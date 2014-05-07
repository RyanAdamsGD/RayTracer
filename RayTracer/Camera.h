#ifndef CAMERA_H
#define CAMERA_H
#include "glm\gtx\transform.hpp"
class World;

class Camera
{
protected:
	glm::vec3 eye, lookat, up;
	glm::vec3 u,v,w;
	float exposureTime;
public:
	Camera();
	virtual ~Camera();
	Camera(glm::vec3 eye, glm::vec3 lookat, glm::vec3 up,float exposureTime=1.0);
	void computeUVW();
	virtual void renderScene(World* world)=0;

	inline void setEye(const glm::vec3& value) {eye=value;}
	inline void setLookAt(const glm::vec3& value) {lookat=value;}
	inline void setUp(const glm::vec3& value) {up=value;}
};

#endif