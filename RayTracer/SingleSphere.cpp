#include "SingleSphere.h"
#include "ShadeRec.h"
#include "World.h"

SingleSphere::SingleSphere(World* world)
	:Tracer(world)
{
}

glm::vec3 SingleSphere::traceRay(const Ray& ray) const
{
	ShadeRec sr(*world);
	float t=0;

	/*if(world->sphere.hit(ray,t,sr))
	{
		return glm::vec3(255.0,0.0,0.0);
	}*/
	return glm::vec3(0.0);
}