#ifndef LAMBERT_H
#define LAMBERT_H
#include "BRDF.h"

class Lambert: public BRDF
{
	float reflectionCoefficient;
	glm::vec3 color;
public:
	Lambert();
	Lambert(Sampler* sampler, const glm::vec3& normal, float reflectionCoefficient, const glm::vec3& color);
	virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& reflected)const;
	virtual glm::vec3 sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected, float& pdf)const;
	virtual glm::vec3 rho(const ShadeRec& sr, const glm::vec3& incoming)const;

	float getReflectionCoefficient() { return reflectionCoefficient; }
	const glm::vec3& getColor() { return color; }
	void setReflectionCoefficient(float value) {reflectionCoefficient = value;}
	void setColor(const glm::vec3& value) {color = value;}
};

#endif