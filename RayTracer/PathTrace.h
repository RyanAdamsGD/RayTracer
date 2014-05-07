#ifndef PATHTRACE_H
#define PATHTRACE_H
#include "Tracer.h"

class PathTrace:public Tracer
{
public:
	PathTrace(World* world);
	virtual glm::vec3 traceRay(const Ray& ray, const int depth) const;
};

#endif