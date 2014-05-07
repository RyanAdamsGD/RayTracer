#include "Disk.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Sampler.h"
#include "glm\gtx\norm.hpp"

Disk::Disk(const glm::vec3& center, const glm::vec3& normal, float radius)
	:center(center),normal(normal),rSquared(radius*radius),radius(radius)
{
}

BoundingBox Disk::getBoundingBox()const
{
	glm::vec3 p0 = glm::vec3(-kEpsilon) + center - glm::vec3(sqrt(rSquared));
	glm::vec3 p1 = glm::vec3(kEpsilon) + center + glm::vec3(sqrt(rSquared));

	return BoundingBox(p1,p0);
}

bool Disk::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	float t = glm::dot((center - ray.getOrigin()),normal) / glm::dot(ray.getDirection(),normal);

	if (t <= KEpsilon)
		return false;

	glm::vec3 point = ray.getOrigin() + t * ray.getDirection();

	if(glm::length2(center - point) < rSquared)
	{
		tmin = t;
		sr.normal = normal;
		sr.localHitPoint = point;
		return true;
	}

	return false;
}

bool Disk::shadowHit(const Ray& ray, float& tmin) const
{
	float t = glm::dot((center - ray.getOrigin()),normal) / glm::dot(ray.getDirection(),normal);

	if (t <= KEpsilon)
		return false;

	glm::vec3 point = ray.getOrigin() + t * ray.getDirection();

	if(glm::length2(center - point) < rSquared)
	{
		tmin = t;
		return true;
	}

	return false;
}

glm::vec3 Disk::sample()
{
	glm::vec2 sample = sampler->sampleUnitDisk();
	return center + glm::vec3(sample.x,sample.y,0) * radius;
}

glm::vec3 Disk::getNormal(const glm::vec3& point) const
{
	return normal;
}

void Disk::setSampler(Sampler* value)
{
	if(sampler != NULL)
	{
		delete sampler;
		sampler = NULL;
	}

	sampler = value;
	sampler->mapSamplesToUnitDisk();
}

void Disk::computeUVW()
{

}