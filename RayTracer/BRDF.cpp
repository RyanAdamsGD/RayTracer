#include "BRDF.h"
#include "MultiJittered.h"
#include "DebugMemory.h"

BRDF::BRDF(Sampler* sampler, const glm::vec3& normal)
	:sampler(sampler),normal(normal)
{

}
BRDF::BRDF()
	:sampler(NULL),normal(0.0)
{

}

BRDF::~BRDF()
{
	if(sampler != NULL)
	{
		delete sampler;
		sampler = NULL;
	}
}

void BRDF::setSamples(const int numSamples, float exp)
{
	if(sampler != NULL)
	{
		delete sampler;
		sampler = NULL;
	}

	sampler = new MultiJittered(numSamples);
	sampler->mapSamplesToHemisphere(exp);
}

glm::vec3 BRDF::f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& reflected)const
{
	return glm::vec3(0.0f);
}

glm::vec3 BRDF::sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected)const
{
	return glm::vec3(0.0f);
}

glm::vec3 BRDF::sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected, float& pdf)const
{
	return glm::vec3(0.0f);
}

glm::vec3 BRDF::rho(const ShadeRec& sr, const glm::vec3& incoming)const
{
	return glm::vec3(0.0f);
}
