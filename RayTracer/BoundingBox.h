#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "glm\gtx\transform.hpp"
class Ray;

class BoundingBox
{
public:
	float x0,x1,y0,y1,z0,z1;
	BoundingBox();
	BoundingBox(const glm::vec3& Max,const glm::vec3& Min);

	bool hit(const Ray& ray) const;
	bool contains(const glm::vec3& point)const;
	bool hit(const Ray& ray, float& t0, float& txMax, float& txMin,
		float& tyMax, float& tyMin, float& tzMax, float& tzMin)const;
};

#endif