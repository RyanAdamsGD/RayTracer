#include "Sphere.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "MultiJittered.h"

Sphere::Sphere(const glm::vec3& center, float radius)
	:center(center), radius(radius)
{
	invArea = (1.0/(PI * 4.0f * radius * radius));
}

Sphere::Sphere()
	:center(0.0f),radius(1.0f)
{
	invArea = (1.0/(PI * 4.0f * radius * radius));
}

BoundingBox Sphere::getBoundingBox()const
{
	glm::vec3 p0 = center + glm::vec3(-radius) - glm::vec3(KEpsilon);
	glm::vec3 p1 = center + glm::vec3(radius) + glm::vec3(KEpsilon);

	return BoundingBox(p1,p0);
}

bool Sphere::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	glm::vec3 rayToCenter = ray.getOrigin() - center;
	float a = glm::dot(ray.getDirection(),ray.getDirection());
	float b = 2.0f *glm::dot(rayToCenter,ray.getDirection());
	float c = glm::dot(rayToCenter,rayToCenter) - (radius * radius);
	float disc = b * b - 4.0f * a * c;

	if(disc < 0.0f)
		return false;
	else
	{
		float e = sqrt(disc);
		float denom = 2.0f * a;
		float t = (-b - e) / denom; // smaller root
		if(t > KEpsilon)
		{
			tmin = t;
			sr.normal = (rayToCenter + t * ray.getDirection()) / radius;
			sr.localHitPoint = ray.getOrigin() + t * ray.getDirection();
			return true;
		}

		t = (-b + e) / denom; //larger root
		if(t > KEpsilon)
		{
			tmin = t;
			sr.normal = (rayToCenter + t * ray.getDirection()) / radius;
			sr.localHitPoint = ray.getOrigin() + t * ray.getDirection();
			return true;
		}
	}
	return false;
}

bool Sphere::shadowHit(const Ray& ray, float& tmin) const
{
	if(!castsShadows)
		return false;

	glm::vec3 rayToCenter = ray.getOrigin() - center;
	float a = glm::dot(ray.getDirection(),ray.getDirection());
	float b = 2.0f *glm::dot(rayToCenter,ray.getDirection());
	float c = glm::dot(rayToCenter,rayToCenter) - (radius * radius);
	float disc = b * b - 4.0f * a * c;

	if(disc < 0.0)
		return false;
	else
	{
		float e = sqrt(disc);
		float denom = 2.0f * a;
		float t = (-b - e) / denom; // smaller root
		if(t > KEpsilon)
		{
			tmin = t;
			return true;
		}

		t = (-b + e) / denom; //larger root
		if(t > KEpsilon)
		{
			tmin = t;
			return true;
		}
	}
	return false;
}

float Sphere::pdf(const ShadeRec& sr)const
{
	return invArea * sampler->getNumSamples() * 2.0f;
}

glm::vec3 Sphere::sample()
{
	glm::vec3 sample = sampler->sampleHemisphere();
	return sample * radius + center;
}

glm::vec3 Sphere::getNormal(const glm::vec3& point) const
{
	return (point - center) / radius;
}

void Sphere::setSampler(Sampler* value)
{
	if(sampler != NULL)
	{
		delete sampler;
		sampler = NULL;
	}

	sampler = value;
	sampler->mapSamplesToHemisphere(1.0);
}