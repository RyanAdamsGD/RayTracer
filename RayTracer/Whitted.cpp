#include "Whitted.h"
#include "World.h"
#include "Ray.h"
#include "Material.h"
#include "DebugMemory.h"

Whitted::Whitted(World* world)
	:Tracer(world)
{
}

glm::vec3 Whitted::traceRay(const Ray& ray, const int depth) const
{
	if(depth > world->getViewPlane().getMaxDepth())
		return glm::vec3(0.0);

	ShadeRec sr(world->hitObjects(ray));

	if(sr.hitObject)
	{
		sr.depth = depth;
		sr.ray = ray;

		return sr.material->shade(sr);
	}

	return world->getBackgroundColor();
}

glm::vec3 Whitted::traceRay(const Ray& ray, float& tmin, const int depth) const
{
	if(depth > world->getViewPlane().getMaxDepth())
	{
		return glm::vec3(0.0);
		tmin = kHugeValue;
	}
	
	ShadeRec sr(world->hitObjects(ray));

	if(sr.hitObject)
	{
		sr.depth = depth;
		sr.ray = ray;
		tmin = sr.t;

		return sr.material->shade(sr);
	}
	else
	{
		tmin = kHugeValue;
		return world->getBackgroundColor();
	}
}