#ifndef ENVIRONMENTLIGHT_H
#define ENVIRONMENTLIGHT_H
#include "Light.h"
class Sampler;
class Material;

class EnvironmentLight:public Light
{
	Sampler* sampler;
	Material* material;
	glm::vec3 u,v,w;
	glm::vec3 incoming;
public:
	void setSampler(Sampler* sampler);
	virtual glm::vec3 getDirection(ShadeRec& sr);
	virtual glm::vec3 L(ShadeRec& sr);
	virtual bool inShadow(const Ray& ray, const ShadeRec& sr) const;
	virtual double pdf(const ShadeRec& sr) const;

	EnvironmentLight(bool useShadows,const glm::vec3& color = glm::vec3(1.0),const double& intensity = 1.0);
	~EnvironmentLight(void);
};

#endif