#ifndef RECT_H
#define RECT_H
#include "GeometricObject.h"

class Rect:public GeometricObject
{
	glm::vec3 corner,v0,v1,normal;
	float aLenSquared,bLenSquared;
public:
	Rect(const glm::vec3& corner, const glm::vec3& edge1, const glm::vec3& edge2);
	Rect(const glm::vec3& corner, const glm::vec3& edge1, const glm::vec3& edge2,const glm::vec3& normal);
	Rect();

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual BoundingBox getBoundingBox()const;
};

#endif