#include "GlossyReflector.h"
#include "GlossySpecular.h"
#include "ShadeRec.h"
#include "World.h"
#include "Tracer.h"
#include "DebugMemory.h"

GlossyReflector::GlossyReflector(void)
{
}

void GlossyReflector::setSamples(const int numSamples, float exp)
{
	glossySpecularBrdf->setSamples(numSamples,exp);
}

void GlossyReflector::setSetKReflective(float value)
{
	glossySpecularBrdf->setReflectionCoefficient(value);
}

void GlossyReflector::setExponentReflective(float exp)
{
	glossySpecularBrdf->setExponent(exp);
}

void GlossyReflector::setColorReflective(const glm::vec3& value)
{
	glossySpecularBrdf->setColor(value);
}

glm::vec3 GlossyReflector::areaLightShade(const ShadeRec& sr)const
{
	glm::vec3 L(Phong::areaLightShade(sr)); //direct Illumination
	glm::vec3 incoming(-sr.ray.getDirection());
	glm::vec3 reflected;
	float pdf;

	glm::vec3 fr(glossySpecularBrdf->sampleF(sr,incoming,reflected,pdf));
	Ray reflectedRay(sr.hitPoint,reflected);

	L += fr * sr.world.getTracer()->traceRay(reflectedRay,sr.depth + 1) * glm::dot(sr.normal,reflected) / pdf;
	return L;
}