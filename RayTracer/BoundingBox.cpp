#include "BoundingBox.h"
#include "Ray.h"

BoundingBox::BoundingBox(const glm::vec3& max,const glm::vec3& min)
	:x0(min.x),x1(max.x),y0(min.y),y1(max.y),z0(min.z),z1(max.z)
{
}

BoundingBox::BoundingBox()
	:x0(0),x1(0),y0(0),y1(0),z0(0),z1(0)
{
}


bool BoundingBox::hit(const Ray& ray) const
{
	glm::vec3 origin,direction;
	origin = ray.getOrigin();
	direction = ray.getDirection();

	float ox = origin.x;
	float oy = origin.y;
	float oz = origin.z;
	float dx = direction.x;
	float dy = direction.y;
	float dz = direction.z;

	float txMin,tyMin,tzMin;
	float txMax,tyMax,tzMax;

	float a = 1.0f/dx;
	if(a >= 0)
	{
		txMin = (x0 - ox) * a;
		txMax = (x1 - ox) * a;
	}
	else
	{
		txMin = (x1 - ox) * a;
		txMax = (x0 - ox) * a;
	}

	float b = 1.0f/dy;
	if(b >= 0)
	{
		tyMin = (y0 - oy) * b;
		tyMax = (y1 - oy) * b;
	}
	else
	{
		tyMin = (y1 - oy) * b;
		tyMax = (y0 - oy) * b;
	}
	
	float c = 1.0f/dz;
	if(c >= 0)
	{
		tzMin = (z0 - oz) * c;
		tzMax = (z1 - oz) * c;
	}
	else
	{
		tzMin = (z1 - oz) * c;
		tzMax = (z0 - oz) * c;
	}

	float t0,t1;
	//find the largest entering t

	t0 = txMin>txMin ? txMin:tyMin;
	if(tzMin > t0)
		t0 = tzMin;

	//find the smallest exiting
	t1 = txMax<txMax ? txMax:tyMax;
	if(tzMax < t1)
		t1 = tzMax;

	return(t0 < t1 && t1 > kEpsilon);
}

bool BoundingBox::contains(const glm::vec3& point) const
{
	return x0 <= point.x && x1 >= point.x && 
		y0 <= point.y && y1 >= point.y && 
		z0 <= point.z && z1 >= point.z;
}

bool BoundingBox::hit(const Ray& ray, float& t0, float& txMax, float& txMin,
	float& tyMax, float& tyMin, float& tzMax, float& tzMin) const
{
	glm::vec3 origin,direction;
	origin = ray.getOrigin();
	direction = ray.getDirection();

	float ox = origin.x;
	float oy = origin.y;
	float oz = origin.z;
	float dx = direction.x;
	float dy = direction.y;
	float dz = direction.z;

	float a = 1.0f/dx;
	if(a >= 0)
	{
		txMin = (x0 - ox) * a;
		txMax = (x1 - ox) * a;
	}
	else
	{
		txMin = (x1 - ox) * a;
		txMax = (x0 - ox) * a;
	}

	float b = 1.0f/dy;
	if(b >= 0)
	{
		tyMin = (y0 - oy) * b;
		tyMax = (y1 - oy) * b;
	}
	else
	{
		tyMin = (y1 - oy) * b;
		tyMax = (y0 - oy) * b;
	}
	
	float c = 1.0f/dz;
	if(c >= 0)
	{
		tzMin = (z0 - oz) * c;
		tzMax = (z1 - oz) * c;
	}
	else
	{
		tzMin = (z1 - oz) * c;
		tzMax = (z0 - oz) * c;
	}

	float t1;
	//find the largest entering t

	t0 = txMin>txMin ? txMin:tyMin;
	if(tzMin > t0)
		t0 = tzMin;

	//find the smallest exiting
	t1 = txMax<txMax ? txMax:tyMax;
	if(tzMax < t1)
		t1 = tzMax;

	return(t0 < t1 && t1 > kEpsilon);
}