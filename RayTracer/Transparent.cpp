#include "Transparent.h"
#include "PerfectSpecular.h"
#include "PerfectTransmitter.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "World.h"
#include "Tracer.h"
#include "DebugMemory.h"

Transparent::Transparent(void)
	:Phong(),reflectiveBrdf(new PerfectSpecular),specularBtfd(new PerfectTransmitter)
{
}

Transparent::~Transparent(void)
{
	if(reflectiveBrdf != NULL)
	{
		delete reflectiveBrdf;
		reflectiveBrdf = NULL;
	}

	if(specularBtfd != NULL)
	{
		delete specularBtfd;
		specularBtfd = NULL;
	}
}

glm::vec3 Transparent::shade(const ShadeRec& sr)const
{
	glm::vec3 L(Phong::shade(sr));

	glm::vec3 incoming = -sr.ray.getDirection();
	glm::vec3 reflected;
	glm::vec3 fr = reflectiveBrdf->sampleF(sr,incoming,reflected);
	Ray reflectedRay(sr.hitPoint,reflected);

	if(specularBtfd->tir(sr))
	{
		//comment this out to remove the reflection and get cool effects
		L +=  sr.world.getTracer()->traceRay(reflectedRay,sr.depth + 1);
		//kr = 1.0
	}
	else
	{
		glm::vec3 transmitted;
		glm::vec3 ft = specularBtfd->sampleF(sr,incoming,transmitted);
		Ray transmittedRay(sr.hitPoint,transmitted);

		glm::vec3 reflectedColor = sr.world.getTracer()->traceRay(reflectedRay,sr.depth + 1) * fabs(glm::dot(sr.normal,reflected));
		fr.x *= reflectedColor.x;
		fr.y *= reflectedColor.y;
		fr.z *= reflectedColor.z;
		glm::vec3 transmittedColor = sr.world.getTracer()->traceRay(transmittedRay,sr.depth + 1) * fabs(glm::dot(sr.normal,transmitted));
		ft.x *= transmittedColor.x;
		ft.y *= transmittedColor.y;
		ft.z *= transmittedColor.z;
		L += fr + ft;
	}

	return L;
}

void Transparent::setIor(float value)
{
	specularBtfd->setIor(value);
}

void Transparent::setKReflective(float value)
{
	reflectiveBrdf->setCoefficientReflection(value);
}

void Transparent::setKTransparent(float value)
{
	specularBtfd->setKt(value);
}