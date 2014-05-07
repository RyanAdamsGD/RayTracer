#ifndef ANNULUS_H
#define ANNULUS_H
#include "GeometricObject.h"

class Annulus:public GeometricObject
{
	glm::vec3 center, normal;
	float outerRadiusSQ, innerRadiusSQ;

public:
	Annulus(const glm::vec3& center, const glm::vec3& normal, float innerRadius, float outerRadius);
	virtual ~Annulus(void);

	virtual BoundingBox getBoundingBox()const;
	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;

	inline void setInnerRadius(float value) {innerRadiusSQ = value * value;}
	inline void setNormal(const glm::vec3& value) {normal = value;}
	inline void setCenter(const glm::vec3& value) {center = value;}
	inline void setOuterRadius(float value) {outerRadiusSQ = value * value;}
};

#endif