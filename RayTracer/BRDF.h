#ifndef DRBF_H
#define DRBF_H
#include "glm\gtx\transform.hpp"
#include "ShadeRec.h"
class Sampler;

class BRDF
{
protected:
	Sampler* sampler;
	glm::vec3 normal;
public:
	BRDF();
	virtual ~BRDF();
	BRDF(Sampler* sampler, const glm::vec3& normal);
	virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& reflected)const;
	virtual glm::vec3 sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected)const;
	virtual glm::vec3 sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected, float& pdf)const;
	virtual glm::vec3 rho(const ShadeRec& sr, const glm::vec3& incoming)const;

	virtual void setSamples(const int numSamples, float exp);
};

#endif