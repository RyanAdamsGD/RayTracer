#include "PerfectTransmitter.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "DebugMemory.h"

PerfectTransmitter::PerfectTransmitter(void)
	:ior(1.0),kt(0.0)
{
}

bool PerfectTransmitter::tir(const ShadeRec& sr)const
{
	glm::vec3 incoming(-sr.ray.getDirection());
	float cosThetaI = glm::dot(sr.normal, incoming);
	float eta = ior;

	if(cosThetaI < 0.0f)
		eta = 1.0f / eta;

	return (1.0f - (1.0f - cosThetaI * cosThetaI) / (eta * eta)) < 0.0f;
}

glm::vec3 PerfectTransmitter::sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& transmitted)const
{
	glm::vec3 norm(sr.normal);
	float cosThetaI = glm::dot(norm,incoming);
	float eta = ior;

	if(cosThetaI < 0.0f)
	{
		cosThetaI = -cosThetaI;
		norm = -norm;
		eta = 1.0f / eta;
	}

	float cosTheta2 = sqrt(1.0f - (1.0f - cosThetaI * cosThetaI) / (eta * eta));
	transmitted = -incoming / eta - (cosTheta2 - cosThetaI / eta) * norm;

	return (kt / (eta * eta) * glm::vec3(1.0f) / fabs(glm::dot(sr.normal,transmitted)));
}
