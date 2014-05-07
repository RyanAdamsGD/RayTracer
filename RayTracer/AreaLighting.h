#ifndef AREALIGHTING_H
#define AREALIGHTING_H
#include "Tracer.h"

class AreaLighting:public Tracer
{
public:
	AreaLighting(World* world);
	virtual glm::vec3 traceRay(const Ray& ray, const int depth) const;
};

#endif