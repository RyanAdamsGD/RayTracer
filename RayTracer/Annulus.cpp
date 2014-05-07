#include "Annulus.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "glm\gtx\norm.hpp"

Annulus::Annulus(const glm::vec3& center, const glm::vec3& normal, float innerRadius, float outerRadius)
	:center(center), normal(normal), innerRadiusSQ(innerRadius*innerRadius), outerRadiusSQ(outerRadius*outerRadius)
{
}


Annulus::~Annulus(void)
{
}

BoundingBox Annulus::getBoundingBox()const
{
	return BoundingBox(glm::vec3(sqrt(outerRadiusSQ)),glm::vec3(-sqrt(outerRadiusSQ)));
}

bool Annulus::shadowHit(const Ray& ray, float& tmin) const
{
	if(!castsShadows)
		return false;

	float t = glm::dot((center - ray.getOrigin()),normal) / glm::dot(ray.getDirection(),normal);

	if (t <= KEpsilon)
		return false;

	glm::vec3 point = ray.getOrigin() + t * ray.getDirection();
	//inner circle
	if(glm::length2(center - point) < innerRadiusSQ)
	{
		return false;
	}
	//outer circle
	if(glm::length2(center - point) < outerRadiusSQ)
	{
		tmin = t;
		return true;
	}

	return false;
}

bool Annulus::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	float t = glm::dot((center - ray.getOrigin()),normal) / glm::dot(ray.getDirection(),normal);

	if (t <= KEpsilon)
		return false;

	glm::vec3 point = ray.getOrigin() + t * ray.getDirection();
	//inner circle
	if(glm::length2(center - point) < innerRadiusSQ)
	{
		return false;
	}
	//outer circle
	if(glm::length2(center - point) < outerRadiusSQ)
	{
		tmin = t;
		sr.normal = normal;
		sr.localHitPoint = point;
		return true;
	}

	return false;
}