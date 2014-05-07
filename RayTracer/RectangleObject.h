#ifndef RECTANGLEOBJET_H
#define RECTANGLEOBJET_H
#include "GeometricObject.h"

class RectangleObject:public GeometricObject
{
	glm::vec3 cornerPoint;
	glm::vec3 edgeA, edgeB;
	glm::vec3 normal;
	float edgeALenSq, edgeBLenSq;
	float invArea;

public:
	RectangleObject(const glm::vec3& cornerPoint,const glm::vec3& egdgeA,
		const glm::vec3& edgeB,const glm::vec3& normal);
	RectangleObject(const glm::vec3& cornerPoint,const glm::vec3& egdgeA,
		const glm::vec3& edgeB);

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, float& t) const;
	virtual glm::vec3 sample(void);
	virtual float pdf(ShadeRec& sr);
	virtual glm::vec3 getNormal(const glm::vec3& point) const;
	virtual BoundingBox getBoundingBox()const;
};

#endif