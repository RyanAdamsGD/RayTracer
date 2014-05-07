#include "AreaLighting.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"
#include "DebugMemory.h"

AreaLighting::AreaLighting(World* world)
	:Tracer(world)
{
}

glm::vec3 AreaLighting::traceRay(const Ray& ray, const int depth) const
{
	ShadeRec sr(world->hitObjects(ray));

	if(sr.hitObject)
	{
		sr.ray = ray;
		return sr.material->areaLightShade(sr);
	}
	else
		return world->getBackgroundColor();
}
