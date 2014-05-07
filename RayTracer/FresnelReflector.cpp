#include "FresnelReflector.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "DebugMemory.h"

FresnelReflector::FresnelReflector(void)
	:BRDF()
{
}

float FresnelReflector::fresnelKr(const ShadeRec& sr) const
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

	return kr;
}

glm::vec3 FresnelReflector::sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected)const
{
	float nDotR = glm::dot(sr.normal,incoming);
	reflected = -incoming + 2.0f * sr.normal * nDotR;
	return fresnelKr(sr) * glm::vec3(1.0f) / fabs(glm::dot(sr.normal, reflected));
}
