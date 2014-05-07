#ifndef TORUS_H
#define TORUS_H
#include "GeometricObject.h"
#include "BoundingBox.h"

class Torus: public GeometricObject
{
	BoundingBox createBoundingbox()const;
	BoundingBox bbox;

	float tubeRadiusSQ, sweptRadiusSQ, sweptRadius;
	glm::vec3 computeNormals(const glm::vec3& point)const;
public:
	Torus(void);
	Torus(float tubeRadius, float sweptRadius);
	virtual ~Torus(void);

	virtual BoundingBox getBoundingBox()const;
	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;

	void setTubeRadius(float value);
	void setSweptRadius(float value);
};

#endif