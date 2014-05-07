#ifndef CONCAVEPARTCYLINDER_H
#define CONCAVEPARTCYLINDER_H
#include "GeometricObject.h"

class ConcavePartCylinder:public GeometricObject
{
	BoundingBox bbox;
	BoundingBox createBoundingBox()const;
	float y0, y1, radius, inverseRadius, azimuthMin, azimuthMax;

public:
	ConcavePartCylinder(void);
	ConcavePartCylinder(float y0, float y1, float radius, float azimuthMax = 360, float azimuthMin = 0.0f);
	virtual ~ConcavePartCylinder(void);

	virtual BoundingBox getBoundingBox()const;
	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;

	void setY0(float value);
	void setY1(float value);
	void setRadius(float value);
	inline void setAzimuthMin(float value) {azimuthMin=value;}
	inline void setAzimuthMax(float value) {azimuthMax=value;}
};

#endif