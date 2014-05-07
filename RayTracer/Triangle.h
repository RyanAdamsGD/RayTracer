#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "GeometricObject.h"

class Triangle:public GeometricObject
{
	glm::vec3 v0,v1,v2;
	glm::vec3 normal;
public:
	Triangle(const glm::vec3& v0,const glm::vec3& v1,const glm::vec3& v2);
	Triangle(const glm::vec3& v0,const glm::vec3& v1,const glm::vec3& v2,const glm::vec3& normal);

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual BoundingBox getBoundingBox()const;

	inline void setNormal(const glm::vec3& value) {normal=value;}
	inline void setV0(const glm::vec3& value) {v0=value;}
	inline void setV1(const glm::vec3& value) {v1=value;}
	inline void setV2(const glm::vec3& value) {v2=value;}
};

#endif