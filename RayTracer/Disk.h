#ifndef DISK_H
#define DISK_H
#include "GeometricObject.h"

class Disk:public GeometricObject
{
	glm::vec3 center,normal;
	float rSquared, radius;

public:
	void computeUVW();

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual BoundingBox getBoundingBox()const;
	Disk(const glm::vec3& center, const glm::vec3& normal, float radius);

	virtual glm::vec3 sample();
	virtual glm::vec3 getNormal(const glm::vec3& point) const;

	virtual void setSampler(Sampler* sampler);

	inline void setRadius(float value) {rSquared = value * value; radius = value;}
	inline void setNormal(const glm::vec3& value) {normal = value;}
	inline void setCenter(const glm::vec3& value) {center = value;}
};

#endif