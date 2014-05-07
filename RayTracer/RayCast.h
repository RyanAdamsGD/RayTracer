#ifndef RAYCAST_H
#define RAYCAST_H
#include "Tracer.h"

class RayCast:public Tracer
{
public:
	RayCast(World* world);
	virtual glm::vec3 traceRay(const Ray& ray,const int depth) const;
};

#endif