#include "Cylinder.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "DebugMemory.h"
#include "HelperFunctions.h"

Cylinder::Cylinder(void)
{
	bbox = createBoundingBox();
}

Cylinder::Cylinder(float y0, float y1, float radius)
:y0(y0),y1(y1),radius(fabs(radius)),inverseRadius(1.0f/radius)
{
	bbox = createBoundingBox();
}

BoundingBox Cylinder::createBoundingBox()const
{
	glm::vec3 min(-radius,min(y0,y1),-radius);
	glm::vec3 max(radius,max(y0,y1),radius);
	return BoundingBox(max,min);
}

Cylinder::~Cylinder(void)
{
}

BoundingBox Cylinder::getBoundingBox()const
{
	return bbox;
}

bool Cylinder::shadowHit(const Ray& ray, float& tmin) const
{
	if(!castsShadows)
		return false;

	float dx = ray.getDirection().x; float dz = ray.getDirection().z;
	float ox = ray.getOrigin().x; float oz = ray.getOrigin().z;

	float a = dx * dx + dz * dz;
	float b = 2.0f * (ox * dx + oz * dz);
	float c = ox * ox + oz * oz - radius * radius;
	float disc = b * b - 4.0 * a * c;
	float t;

	if(disc < 0.0)
		return false;
	else
	{
		float e = sqrt(disc);
		float denom = 2.0 * a;
		t = (-b - e) / denom;

		if(t > KEpsilon)
		{
			float yHit = ray.getOrigin().y + t * ray.getDirection().y;

			if(yHit > y0 && yHit < y1)
			{
				tmin = t;
				return true;
			}
		}

		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) 
		{
			float yHit = ray.getOrigin().y + t * ray.getDirection().y;
			
			if (yHit > y0 && yHit < y1) 
			{
				tmin = t;
				return (true);
			}
		}
	}

	return false;
}

bool Cylinder::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	float dx = ray.getDirection().x; float dz = ray.getDirection().z;
	float ox = ray.getOrigin().x; float oz = ray.getOrigin().z;

	float a = dx * dx + dz * dz;
	float b = 2.0f * (ox * dx + oz * dz);
	float c = ox * ox + oz * oz - radius * radius;
	float disc = b * b - 4.0 * a * c;
	float t;

	if(disc < 0.0)
		return false;
	else
	{
		float e = sqrt(disc);
		float denom = 2.0f * a;
		t = (-b - e) / denom;

		if(t > KEpsilon)
		{
			glm::vec3 hitPoint = ray.getOrigin() + t * ray.getDirection();

			if(hitPoint.y > y0 && hitPoint.y < y1)
			{
				tmin = t;
				sr.normal = glm::vec3(hitPoint.x * inverseRadius, 0.0f, hitPoint.z * inverseRadius);

				//test for hitting form inside

				if(glm::dot(-ray.getDirection(),sr.normal) < 0.0)
					sr.normal = -sr.normal;

				sr.localHitPoint = hitPoint;

				return true;
			}
		}

		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) 
		{
			glm::vec3 hitPoint = ray.getOrigin() + t * ray.getDirection();
			
			if (hitPoint.y > y0 && hitPoint.y < y1) 
			{
				tmin = t;
				sr.normal = glm::vec3(hitPoint.z * inverseRadius, 0.0f, hitPoint.x * inverseRadius);
				
				// test for hitting inside surface
			
				if (glm::dot(-ray.getDirection(), sr.normal) < 0.0)
					sr.normal = -sr.normal;
					
				sr.localHitPoint = hitPoint;
	
				return (true);
			}
		}
	}

	return false;
}

void Cylinder::setY0(float value) 
{
	y0=value;
	bbox = createBoundingBox();
}

void Cylinder::setY1(float value) 
{
	y1=value;
	bbox = createBoundingBox();
}

void Cylinder::setRadius(float value) 
{
	radius=fabs(value);
	inverseRadius = 1.0f / value;
	bbox = createBoundingBox();
}