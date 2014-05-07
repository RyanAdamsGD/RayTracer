#include "Box.h"
#include "Ray.h"
#include "HelperFunctions.h"
#include "ShadeRec.h"

Box::Box(const glm::vec3& corner1,const glm::vec3& corner2)
{
	x0 = min(corner1.x,corner2.x);
	y0 = min(corner1.y,corner2.y);
	z0 = min(corner1.z,corner2.z);

	x1 = max(corner1.x,corner2.x);
	y1 = max(corner1.y,corner2.y);
	z1 = max(corner1.z,corner2.z);
}

bool Box::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	glm::vec3 origin,direction;
	origin = ray.getOrigin();
	direction = glm::normalize(ray.getDirection());

	float ox = origin.x;
	float oy = origin.y;
	float oz = origin.z;
	float dx = direction.x;
	float dy = direction.y;
	float dz = direction.z;

	float txMin,tyMin,tzMin;
	float txMax,tyMax,tzMax;

	float a = 1.0f/dx;
	if(a >= 0.0f)
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
	if(b >= 0.0f)
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
	if(c >= 0.0f)
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
	int faceIn, faceOut;
	//find the largest entering face
	if(txMin > tyMin)
	{
		t0 = txMin;
		faceIn = a>=0.0f ? 0:3;
	}
	else
	{
		t0 = tyMin;
		faceIn = b>=0.0f ? 1:4;
	}
	if(tzMin > t0)
	{
		t0 = tzMin;
		faceIn = c>=0.0f ? 2:5;
	}

	//find the smallest exiting face
	if(txMax < tyMax)
	{
		t1 = txMax;
		faceOut = a>=0.0f ? 3:0;
	}
	else
	{
		t1 = tyMax;
		faceOut = b>=0.0f ? 4:1;
	}
	if(tzMax < t1)
	{
		t1 = tzMax;
		faceOut = c>=0.0f ? 5:2;
	}

	if(t0 < t1 && t1 > KEpsilon) //hit
	{
		if(t0 > KEpsilon) //ray hits outside surface
		{
			tmin = t0;
			sr.normal = getNormal(faceIn);
		}
		else //ray hits inside surface
		{
			tmin = t1;
			sr.normal = getNormal(faceOut);
		}
		sr.localHitPoint = ray.getOrigin() + tmin * ray.getDirection();
		return true;
	}
	return false;
}



bool Box::shadowHit(const Ray& ray, float& tmin) const
{
	if(!castsShadows)
		return false;

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
	if(a >= 0.0f)
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
	if(b >= 0.0f)
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
	if(c >= 0.0f)
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
	int faceIn, faceOut;
	//find the largest entering face
	if(txMin > tyMin)
	{
		t0 = txMin;
		faceIn = a>=0.0f ? 0:3;
	}
	else
	{
		t0 = tyMin;
		faceIn = b>=0.0f ? 1:4;
	}
	if(tzMin > t0)
	{
		t0 = tzMin;
		faceIn = c>=0.0f ? 2:5;
	}

	//find the smallest exiting face
	if(txMax < tyMax)
	{
		t1 = txMax;
		faceOut = a>=0.0f ? 3:0;
	}
	else
	{
		t1 = tyMax;
		faceOut = b>=0.0f ? 4:1;
	}
	if(tzMax < t1)
	{
		t1 = tzMax;
		faceOut = c>=0.0f ? 5:2;
	}

	if(t0 < t1 && t1 > KEpsilon) //hit
	{
		if(t0 > KEpsilon) //ray hits outside surface
		{
			tmin = t0;
		}
		else //ray hits inside surface
		{
			tmin = t1;
		}

		return true;
	}
	return false;
}

glm::vec3 Box::getNormal(int faceHit) const
{
	switch(faceHit)
	{
	case 0:
		return glm::vec3(-1,0,0);
	case 1:
		return glm::vec3(0,-1,0);
	case 2:
		return glm::vec3(0,0,-1);
	case 3:
		return glm::vec3(1,0,0);
	case 4:
		return glm::vec3(0,1,0);
	case 5:
		return glm::vec3(0,0,1);
	}
}

void Box::setMin(const glm::vec3& value)
{
	x0 = value.x;
	y0 = value.y;
	z0 = value.z;
}

void Box::setMax(const glm::vec3& value)
{
	x1 = value.x;
	y1 = value.y;
	z1 = value.z;
}

BoundingBox Box::getBoundingBox()const
{
	return BoundingBox(glm::vec3(x1,y1,z1),glm::vec3(x0,y0,z0));
}
