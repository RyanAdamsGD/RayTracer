#ifndef SPHERE_H
#define SPHERE_H
#include "GeometricObject.h"
#include "glm\gtx\transform.hpp"


class Sphere:public GeometricObject
{
	glm::vec3 center;
	float radius;
	
public:
	Sphere(const glm::vec3& center, float radius);
	Sphere();

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, float& t) const;
	virtual BoundingBox getBoundingBox()const;

	virtual float pdf(const ShadeRec& sr)const;
	virtual glm::vec3 sample();
	virtual glm::vec3 getNormal(const glm::vec3& point) const;
	virtual void setSampler(Sampler* value);

	inline void setRadius(const float& value) {radius=value;}
	inline void setCenter(const glm::vec3& value) {center=value;}
};

#endif