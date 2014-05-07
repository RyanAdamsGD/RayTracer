#include "Reflective.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "World.h"
#include "Tracer.h"
#include "PerfectSpecular.h"
#include "DebugMemory.h"

Reflective::Reflective(void)
	:Phong(),reflectiveBrdf(new PerfectSpecular)
{
}


Reflective::~Reflective(void)
{
	if(reflectiveBrdf != NULL)
	{
		delete reflectiveBrdf;
		reflectiveBrdf = NULL;
	}
}

glm::vec3 Reflective::shade(const ShadeRec& sr)const
{
	glm::vec3 L(Phong::shade(sr)); //direct illumination

	glm::vec3 incoming = -sr.ray.getDirection();
	glm::vec3 reflected;
	glm::vec3 fr = reflectiveBrdf->sampleF(sr,incoming,reflected);
	Ray reflectedRay(sr.hitPoint,reflected);

	//trace the incoming ray
	L += fr * sr.world.getTracer()->traceRay(reflectedRay,sr.depth + 1) * glm::dot(sr.normal,reflected);
	
	return L;
}

glm::vec3 Reflective::pathShade(const ShadeRec& sr)const
{
	glm::vec3 incoming = -sr.ray.getDirection();
	glm::vec3 reflected;
	float pdf;
	glm::vec3 fr = reflectiveBrdf->sampleF(sr,incoming,reflected,pdf);
	Ray reflectedRay(sr.hitPoint,reflected);

	glm::vec3 reflectedColor = sr.world.getTracer()->traceRay(reflectedRay,sr.depth + 1);
	fr.x *= reflectedColor.x;
	fr.y *= reflectedColor.y;
	fr.z *= reflectedColor.z;
	return fr  * glm::dot(sr.normal,reflected) / pdf;
}

void Reflective::setReflectiveColor(const glm::vec3& value)
{
	reflectiveBrdf->setReflectiveColor(value);
}

void Reflective::setKReflective(float value)
{
	reflectiveBrdf->setCoefficientReflection(value);
}