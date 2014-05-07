#ifndef CYLINDER_H
#define CYLINDER_H
#include "GeometricObject.h"
#include "BoundingBox.h"

class Cylinder:public GeometricObject
{
	BoundingBox bbox;
	BoundingBox createBoundingBox()const;
	float y0, y1, radius, inverseRadius;
public:
	Cylinder(void);
	Cylinder(float y0, float y1, float radius);
	virtual ~Cylinder(void);

	virtual BoundingBox getBoundingBox()const;
	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;

	void setY0(float value);
	void setY1(float value);
	void setRadius(float value);
};

#endif