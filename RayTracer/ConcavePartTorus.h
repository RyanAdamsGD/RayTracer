#ifndef CONCAVEPARTTORUS_H
#define CONCAVEPARTTORUS_H
#include "GeometricObject.h"

class ConcavePartTorus:public GeometricObject
{
	BoundingBox createBoundingbox()const;
	BoundingBox bbox;

	float tubeRadiusSQ, sweptRadiusSQ, sweptRadius, azimuthMin, azimuthMax, polarStart, polarEnd;
	glm::vec3 computeNormals(const glm::vec3& point)const;
public:
	ConcavePartTorus(void);
	virtual ~ConcavePartTorus(void);
	ConcavePartTorus(float tubeRadius, float sweptRadius, float azimuthMin = 0.0f, float azimuthMax = 360,
		float polarStart = 0,float polarEnd = 360);

	virtual BoundingBox getBoundingBox()const;
	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;

	void setTubeRadius(float value);
	void setSweptRadius(float value);
	void setAzimuthMin(float value) {azimuthMin=value;}
	void setAzimuthMax(float value) {azimuthMax=value;}
	void setPolarStart(float value) {polarStart=value;}
	void setPolarEnd(float value) {polarEnd=value;}
};

#endif