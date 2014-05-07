#include "PathTrace.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"
#include "Ray.h"
#include "ViewPlane.h"
#include "DebugMemory.h"

PathTrace::PathTrace(World* world)
	:Tracer(world)
{
}

glm::vec3 PathTrace::traceRay(const Ray& ray, const int depth) const
{
	if(depth > world->getViewPlane().getMaxDepth())
		return glm::vec3(0.0);

	ShadeRec sr(world->hitObjects(ray));

	if(sr.hitObject)
	{
		sr.depth = depth;
		sr.ray = ray;

		return sr.material->pathShade(sr);
	}
	else
		return world->getBackgroundColor();

}