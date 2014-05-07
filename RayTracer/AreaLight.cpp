#include "AreaLight.h"
#include "GeometricObject.h"
#include "ShadeRec.h"
#include "World.h"
#include "Material.h"
#include "DebugMemory.h"

AreaLight::AreaLight(bool useShadows,const glm::vec3& color, float intensity)
	:Light(useShadows,color,intensity),object(NULL), material(NULL)
{
}


AreaLight::~AreaLight(void)
{
	if(object != NULL)
	{
		delete object;
		object = NULL;
	}

	if(material != NULL)
	{
		delete material;
		material = NULL;
	}
}

glm::vec3 AreaLight::getDirection(const ShadeRec& sr)
{
	samplePoint = object->sample();
	lightNormal = object->getNormal(samplePoint);
	reflected = glm::normalize(samplePoint - sr.hitPoint);
	return reflected;
}

glm::vec3 AreaLight::L(const ShadeRec& sr)
{
	float nDotD = glm::dot(-lightNormal,reflected);

	if(nDotD > 0.0f)
		return material->areaLightShade(sr);
	else
		return glm::vec3(0.0f);
}

float AreaLight::G(const ShadeRec& sr)const
{
	float nDotD = glm::dot(-lightNormal,reflected);
	float length = (samplePoint - sr.hitPoint).length();

	return nDotD / (length * length);
}

float AreaLight::pdf(const ShadeRec& sr)const
{
	return object->pdf(sr);
}

bool AreaLight::inShadow(const Ray& ray,const ShadeRec& sr)const
{
	if(!useShadows)
		return false;

	float t;
	int numObjects = sr.world.objects.size();
	float ts = glm::dot((samplePoint - ray.getOrigin()),ray.getOrigin());

	for(int i=0;i<numObjects;i++)
	{
		if(sr.world.objects[i]->shadowHit(ray,t) && t < ts)
			return true;
	}

	return false;
}

void AreaLight::setObject(GeometricObject* value)
{
	if(object != NULL)
	{
		delete object;
		object = NULL;
	}

	object = value;
	setMaterial(value->getMaterial());
}

void AreaLight::setMaterial(Material* value) 
{
	if(material != NULL)
	{
		delete material;
		material = NULL;
	}

	material = value;
}