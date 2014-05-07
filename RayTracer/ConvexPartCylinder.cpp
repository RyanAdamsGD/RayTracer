#include "ConvexPartCylinder.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "DebugMemory.h"
#include "HelperFunctions.h"

ConvexPartCylinder::ConvexPartCylinder(void)
{
	bbox = createBoundingBox();
}

ConvexPartCylinder::ConvexPartCylinder(float y0, float y1, float radius, float azimuthMax, float azimuthMin)
	:y0(y0),y1(y1),radius(fabs(radius)),inverseRadius(1.0f/radius),azimuthMax(azimuthMax),azimuthMin(azimuthMin)
{
	bbox = createBoundingBox();
}

BoundingBox ConvexPartCylinder::createBoundingBox()const
{
	glm::vec3 min(-radius,min(y0,y1),-radius);
	glm::vec3 max(radius,max(y0,y1),radius);
	return BoundingBox(max,min);
}

ConvexPartCylinder::~ConvexPartCylinder(void)
{
}

BoundingBox ConvexPartCylinder::getBoundingBox()const
{
	return bbox;
}

bool ConvexPartCylinder::shadowHit(const Ray& ray, float& tmin) const
{
	if(!castsShadows)
		return false;

	if(!bbox.hit(ray))
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
			glm::vec3 hitPoint = ray.getOrigin() + t * ray.getDirection();

			if(hitPoint.y > y0 && hitPoint.y < y1)
			{
				tmin = t;

				float phi = atan2(hitPoint.x, hitPoint.z);
				if(phi < 0.0f)
					phi += TWO_PI;


				if(phi < (azimuthMin * PI_OVER_180) || phi > (azimuthMax * PI_OVER_180))
					return false;

				return true;
			}
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) 
		{
			glm::vec3 hitPoint = ray.getOrigin() + t * ray.getDirection();

			if(hitPoint.y > y0 && hitPoint.y < y1)
			{
				tmin = t;
				float phi = atan2(hitPoint.x, hitPoint.z);
				if(phi < 0.0f)
					phi += TWO_PI;


				if(phi < (azimuthMin * PI_OVER_180) || phi > (azimuthMax * PI_OVER_180))
					return false;

				return (true);
			}
		}
	}

	return false;
}

bool ConvexPartCylinder::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	if(!bbox.hit(ray))
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
			glm::vec3 hitPoint = ray.getOrigin() + t * ray.getDirection();

			if(hitPoint.y > y0 && hitPoint.y < y1)
			{
				tmin = t;
				sr.normal = glm::vec3(hitPoint.x * inverseRadius, 0.0f, hitPoint.z * inverseRadius);
				
				float phi = atan2(hitPoint.x, hitPoint.z);
				if(phi < 0.0f)
					phi += TWO_PI;


				if(phi < (azimuthMin * PI_OVER_180) || phi > (azimuthMax * PI_OVER_180))
					return false;

				sr.localHitPoint = hitPoint;

				return true;
			}
		}

		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) 
		{
			glm::vec3 hitPoint = ray.getOrigin() + t * ray.getDirection();

			if(hitPoint.y > y0 && hitPoint.y < y1)
			{
				tmin = t;
				sr.normal = glm::vec3(hitPoint.x * inverseRadius, 0.0f, hitPoint.z * inverseRadius);
				
				float phi = atan2(hitPoint.x, hitPoint.z);
				if(phi < 0.0f)
					phi += TWO_PI;


				if(phi < (azimuthMin * PI_OVER_180) || phi > (azimuthMax * PI_OVER_180))
					return false;

				sr.localHitPoint = hitPoint;
	
				return (true);
			}
		}
	}

	return false;
}

void ConvexPartCylinder::setY0(float value) 
{
	y0=value;
	bbox = createBoundingBox();
}

void ConvexPartCylinder::setY1(float value) 
{
	y1=value;
	bbox = createBoundingBox();
}

void ConvexPartCylinder::setRadius(float value) 
{
	radius=fabs(value);
	inverseRadius = 1.0f / value;
	bbox = createBoundingBox();
}