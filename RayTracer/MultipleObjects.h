#ifndef MULTIPLEOBJECTS_H
#define MULTIPLEOBJECTS_H
#include "Tracer.h"

class MultipleObjects:public Tracer
{
public:
	virtual glm::vec3 traceRay(const Ray& ray) const;
	MultipleObjects(World* world);
};

#endif