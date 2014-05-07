#ifndef SINGLESPHERE_H
#define SINGLESPHERE_H
#include "Tracer.h"

class SingleSphere:public Tracer
{
public:
	SingleSphere(World* world);
	virtual glm::vec3 traceRay(const Ray& ray) const;
};

#endif