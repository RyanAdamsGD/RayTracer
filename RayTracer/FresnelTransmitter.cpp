#include "FresnelTransmitter.h"
#include "ShadeRec.h"
#include "DebugMemory.h"

FresnelTransmitter::FresnelTransmitter(void)
	:BTDF()
{
}

bool FresnelTransmitter::tir(const ShadeRec& sr)const
{
	glm::vec3 normal(sr.normal);
	float nDotD = glm::dot(-normal,sr.ray.getDirection());
	float eta = etaIn / etaOut;

	if(nDotD < 0.0)
	{
		normal = -normal;
		eta = etaOut / etaIn;
	}

	float cosThetaI = glm::dot(-normal, sr.ray.getDirection());
	return (1.0f - (1.0f - cosThetaI * cosThetaI) / (eta * eta)) < 0.0f;
}

glm::vec3 FresnelTransmitter::sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& transmitted)const
{
	glm::vec3 normal = sr.normal;
	float cosThetaI = glm::dot(normal,incoming);
	float eta = etaIn / etaOut;

	if(cosThetaI < 0.0f)
	{
		cosThetaI = -cosThetaI;
		normal = -normal;
		eta = etaOut / etaIn;
	}

	float cosTheta2 = sqrt(1.0f - (1.0f - cosThetaI * cosThetaI) / (eta * eta));
	transmitted = -incoming / eta - (cosTheta2 - cosThetaI / eta) * normal;

	return fresnelKt(sr) / (eta * eta) * glm::vec3(1.0f) / fabs(glm::dot(sr.normal,transmitted));
}

float FresnelTransmitter::fresnelKt(const ShadeRec& sr) const
{
	glm::vec3 normal(sr.normal);
	float nDotD = glm::dot(-normal,sr.ray.getDirection());
	float eta = etaIn / etaOut;

	if(nDotD < 0.0)
	{
		normal = -normal;
		eta = etaOut / etaIn;
	}

	float cosThetaI = glm::dot(-normal, sr.ray.getDirection());
	float cosThetaT = sqrt(1.0f - (1.0f - cosThetaI * cosThetaI) / (eta * eta));

	float rParrallel = (eta * cosThetaI - cosThetaT) / ( eta * cosThetaI + cosThetaT);
	float rPerpendicular = (cosThetaI - eta * cosThetaT) / ( cosThetaI + eta * cosThetaT);
	float kr = 0.5f * ( rParrallel * rParrallel + rPerpendicular * rPerpendicular);

	return 1.0f - kr;
}