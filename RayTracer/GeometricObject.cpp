#include "GeometricObject.h"
#include "Sampler.h"
#include "BoundingBox.h"

const float GeometricObject::KEpsilon = 0.0001f;

GeometricObject::GeometricObject()
	:material(NULL),castsShadows(true),sampler(NULL),invArea(0.0f)
{
}

void GeometricObject::setSampler(Sampler* sp)
{
	if(sampler != NULL)
	{
		delete sampler;
		sampler = NULL;
	}

	sampler = sp;
}

GeometricObject::~GeometricObject()
{
	sampler = NULL;
	material = NULL;
}

glm::vec3 GeometricObject::sample(void)
{
	return glm::vec3(0.0);
}

float GeometricObject::pdf(const ShadeRec& sr) const
{
	return invArea;
}

glm::vec3 GeometricObject::getNormal(const glm::vec3& point) const
{
	return glm::vec3(0.0f);
}

void GeometricObject::setMaterial(Material* value) 
{
	//add the check against value being NULL to properly delete materials
	//shared by multiple objects
	if(material != NULL && value != NULL)
	{
		delete material;
		material = NULL;
	}

	material = value;
}