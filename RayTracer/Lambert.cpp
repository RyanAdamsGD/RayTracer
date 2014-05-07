#include "Lambert.h"
#include "TypeDefs.h"
#include "Sampler.h"
#include "DebugMemory.h"

Lambert::Lambert(Sampler* sampler, const glm::vec3& normal, float reflectionCoefficient, const glm::vec3& color)
	:BRDF(sampler,normal),reflectionCoefficient(reflectionCoefficient),color(color)
{
}

Lambert::Lambert()
	:BRDF(),reflectionCoefficient(1.0f),color(0.0f)
{
}

glm::vec3 Lambert::f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& reflected)const
{
	return(reflectionCoefficient * color * INV_PI);
}

glm::vec3 Lambert::sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected, float& pdf)const
{
	glm::vec3 w = sr.normal;
	glm::vec3 v = glm::cross(glm::vec3(0.0034f,1.0f,0.0071f),w);
	v = glm::normalize(v);
	glm::vec3 u = glm::cross(v,w);

	glm::vec3 samplePoint = sampler->sampleHemisphere();
	reflected = samplePoint.x * u + samplePoint.y * v + samplePoint.z * w;
	reflected = glm::normalize(reflected);

	pdf = glm::dot(sr.normal,reflected) * INV_PI;

	return reflectionCoefficient * color * INV_PI;
}

glm::vec3 Lambert::rho(const ShadeRec& sr, const glm::vec3& incoming)const
{
	return (reflectionCoefficient * color);
}