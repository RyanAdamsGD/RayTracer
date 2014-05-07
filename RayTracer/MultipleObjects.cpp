#include "MultipleObjects.h"
#include "ShadeRec.h"
#include "World.h"

MultipleObjects::MultipleObjects(World* world)
	:Tracer(world)
{
}

glm::vec3 MultipleObjects::traceRay(const Ray& ray) const
{
	ShadeRec sr(world->hitObjects(ray));

	if(sr.hitObject)
		return sr.color;
	else
		return world->getBackgroundColor();
}
