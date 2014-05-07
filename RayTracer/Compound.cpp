#include "Compound.h"
#include "TypeDefs.h"
#include "Material.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "DebugMemory.h"

Compound::Compound(void)
{
	bbox = createBoundingBox();
}

BoundingBox Compound::createBoundingBox()const
{
	uint size = objects.size();
	BoundingBox boundingBox(glm::vec3(-kHugeValue),glm::vec3(kHugeValue));
	BoundingBox bBox;

	for(uint i=0;i<size;i++)
	{
		bBox = objects[i]->getBoundingBox();

		if(bBox.x0 < boundingBox.x0)
			boundingBox.x0 = bBox.x0;
		if(bBox.y0 < boundingBox.y0)
			boundingBox.y0 = bBox.y0;
		if(bBox.z0 < boundingBox.z0)
			boundingBox.z0 = bBox.z0;

		if(bBox.x1 > boundingBox.x1)
			boundingBox.x1 = bBox.x1;
		if(bBox.y1 > boundingBox.y1)
			boundingBox.y1 = bBox.y1;
		if(bBox.z1 > boundingBox.z1)
			boundingBox.z1 = bBox.z1;
	}

	return boundingBox;
}

Compound::~Compound(void)
{
	for(uint i=0;i<objects.size();i++)
	{
		if(objects[i] != NULL)
		{
			delete objects[i];
			objects[i] = NULL;
		}
	}

	objects.clear();
}

void Compound::setMaterial(Material* value)
{
	uint size = objects.size();
	for(uint i=0;i<size;i++)
		objects[i]->setMaterial(value);
}

void Compound::addObject( GeometricObject* object)
{
	objects.push_back(object);
	bbox = createBoundingBox();
}

bool Compound::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	if(!bbox.hit(ray))
		return false;

	float t;
	glm::vec3 normal;
	glm::vec3 localHitPoint;
	glm::vec2 uv;
	bool hit = false;
	tmin = kHugeValue;
	uint numObjects = objects.size();
	BoundingBox* boundingBox;

	for(uint i=0;i<numObjects;i++)
	{
		if(objects[i]->hit(ray,t,sr))
			if(t<tmin)
			{
				hit = true;
				tmin = t;
				normal = sr.normal;
				localHitPoint = sr.localHitPoint;
				uv.x = sr.u;
				uv.y = sr.v;
				sr.material = objects[i]->getMaterial();
			}
	}

	if(hit)
	{
		sr.t = tmin;
		sr.normal = normal;
		sr.localHitPoint = localHitPoint;
		sr.u = uv.x;
		sr.v = uv.y;
	}

	return hit;
}

bool Compound::shadowHit(const Ray& ray, float& tmin) const
{
	if(!bbox.hit(ray))
		return false;

	bool hit = false;
	uint numObjects = objects.size();

	for(uint i=0;i<numObjects;i++)
	{
		if(objects[i]->shadowHit(ray,tmin))
		{
			hit = true;
		}
	}

	return hit;
}

BoundingBox Compound::getBoundingBox()const
{
	return bbox;
}

void Compound::setCastShadows(bool value)
{
	for(uint i=0;i<objects.size();i++)
	{
		if(objects[i] != NULL)
		{
			objects[i]->setCastShadows(value);
		}
	}
}

void Compound::clearObjects()
{
	uint size = objects.size();
	for(uint i=0;i<size;i++)
	{
		objects[i] = NULL;
	}

	objects.clear();
}
