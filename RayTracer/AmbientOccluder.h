#ifndef AMBIENTOCCLUDER_H
#define AMBIENTOCCLUDER_H
#include "Light.h"
class Sampler;

class AmbientOccluder:public Light
{
	Sampler* sampler;
	glm::vec3 minAmount;
	glm::vec3 u,v,w;
public:
	AmbientOccluder(bool useShadows,const glm::vec3& color, float intensity,
		Sampler* sampler = NULL,const glm::vec3& minAmount = glm::vec3(0.25f));
	~AmbientOccluder(void);

	virtual glm::vec3 L(const ShadeRec& sr);
	virtual bool inShadow(const Ray& ray,const ShadeRec& sr)const;
	virtual glm::vec3 getDirection(const ShadeRec& sr);
	void setSampler(Sampler* sampler);
};

#endif