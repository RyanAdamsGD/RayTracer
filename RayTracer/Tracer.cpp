#include "Tracer.h"
#include "DebugMemory.h"

Tracer::Tracer(World* world)
	:world(world)
{
}

glm::vec3 Tracer::traceRay(const Ray& ray) const
{
	return glm::vec3(0.0);
}

glm::vec3 Tracer::traceRay(const Ray& ray, const int depth) const {
	return glm::vec3(0.0);
}

glm::vec3 Tracer::traceRay(const Ray& ray,float& tmin, const int depth) const {
	return glm::vec3(0.0);
}