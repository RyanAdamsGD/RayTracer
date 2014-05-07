#include "RayCast.h"
#include "ShadeRec.h"
#include "World.h"
#include "Material.h"
#include "DebugMemory.h"

RayCast::RayCast(World* world)
	:Tracer(world)
{
}

glm::vec3 RayCast::traceRay(const Ray& ray,const int depth) const
{
	ShadeRec sr(world->hitObjects(ray));

	if(sr.hitObject)
	{
		sr.ray = ray;
		return sr.material->shade(sr);
	}
	else
		return world->getBackgroundColor();

}