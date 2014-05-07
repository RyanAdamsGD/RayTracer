#ifndef WHITTED_H
#define WHITTED_H
#include "Tracer.h"

class Whitted:public Tracer
{
public:
	Whitted(World* world);
	virtual glm::vec3 traceRay(const Ray& ray, const int depth) const;
	virtual glm::vec3 traceRay(const Ray& ray, float& tmin, const int depth) const;
};

#endif