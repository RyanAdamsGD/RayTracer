#ifndef TRACER_H
#define TRACER_H
#include "glm\gtx\transform.hpp"
#include "Ray.h"
class World;

class Tracer
{
protected:
	World* world;
public:
	Tracer(World* world);
	virtual glm::vec3 traceRay(const Ray& ray) const;
	virtual glm::vec3 traceRay(const Ray& ray, const int depth) const;
	virtual glm::vec3 traceRay(const Ray& ray,float& tmin, const int depth) const;
};

#endif