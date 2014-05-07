#include "Plane.h"
#include "Ray.h"
#include "ShadeRec.h"

Plane::Plane(const glm::vec3& point, const glm::vec3& normal)
	:point(point), normal(glm::normalize(normal))
{
}

Plane::Plane(void)
{
}

BoundingBox Plane::getBoundingBox()const
{
	return BoundingBox(glm::vec3(0),glm::vec3(0));
}

bool Plane::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	float t = glm::dot((point - ray.getOrigin()), normal) / glm::dot(ray.getDirection(), normal);
	if(t> KEpsilon)
	{
		tmin = t;
		sr.normal = normal;
		sr.localHitPoint = ray.getOrigin() + t * ray.getDirection();
		return true;
	}
	else	
		return false;
	
}

bool Plane::shadowHit(const Ray& ray, float& tmin) const
{
	if(!castsShadows)
		false;

	float t = glm::dot((point - ray.getOrigin()), normal) / glm::dot(ray.getDirection(), normal); 
	if(t > kEpsilon)
	{
		tmin = t;
		return true;
	}
	else
		return false;
}
