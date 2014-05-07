#ifndef BOX_H
#define BOX_H
#include "GeometricObject.h"

class Box:public GeometricObject
{
	float x0,x1,y0,y1,z0,z1;
public:
	Box(const glm::vec3& corner1,const glm::vec3& corner2);
	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual BoundingBox getBoundingBox()const;
	glm::vec3 getNormal(int faceHit) const;

	void setMin(const glm::vec3& value);
	void setMax(const glm::vec3& value);
};

#endif