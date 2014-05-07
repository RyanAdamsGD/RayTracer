#include "PerfectSpecular.h"
#include "DebugMemory.h"

PerfectSpecular::PerfectSpecular(Sampler* sampler, const glm::vec3& normal)
	:BRDF(sampler,normal),reflectiveColor(0.0f),kr(0.0f)
{
}

PerfectSpecular::PerfectSpecular()
	:BRDF(),reflectiveColor(1.0f),kr(0.0f)
{
}

glm::vec3 PerfectSpecular::f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& reflected)const
{
	return glm::vec3(0.0f);
}

glm::vec3 PerfectSpecular::sampleF(const ShadeRec& sr,const glm::vec3& incoming, glm::vec3& reflected)const
{
	float nDotR = glm::dot(sr.normal,incoming);
	reflected = -incoming + 2.0f * sr.normal * nDotR;
	return kr * reflectiveColor / fabs(glm::dot(sr.normal, reflected));
}

glm::vec3 PerfectSpecular::sampleF(const ShadeRec& sr,const glm::vec3& incoming, glm::vec3& reflected, float& pdf)const
{
	float nDotR = glm::dot(sr.normal,incoming);
	reflected = -incoming + 2.0f * sr.normal * nDotR;
	pdf = fabs(glm::dot(sr.normal, reflected));
	return kr * reflectiveColor;
}

glm::vec3 PerfectSpecular::rho(const ShadeRec& sr, const glm::vec3& incoming)const
{
	return glm::vec3(0.0f);
}