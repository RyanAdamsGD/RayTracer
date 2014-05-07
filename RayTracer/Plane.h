#ifndef PLANE_H
#define PLANE_H
#include "GeometricObject.h"
#include "glm\gtx\transform.hpp"


class Plane: public GeometricObject
{
	glm::vec3 point; //point through which the plane passes
	glm::vec3 normal;

public:
	Plane(void);
	Plane(const glm::vec3& point, const glm::vec3& normal);

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, float& t) const;
	virtual BoundingBox getBoundingBox()const;
};

#endif