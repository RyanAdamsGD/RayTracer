#ifndef PERFECTSPECULAR_H
#define PERFECTSPECULAR_H
#include "BRDF.h"

class PerfectSpecular:public BRDF
{
	float kr; //coefficient of reflection
	glm::vec3 reflectiveColor;
public:
	PerfectSpecular();
	PerfectSpecular(Sampler* sampler, const glm::vec3& normal);
	virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& reflected)const;
	virtual glm::vec3 sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected)const;
	virtual glm::vec3 sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected,float& pdf)const;
	virtual glm::vec3 rho(const ShadeRec& sr, const glm::vec3& incoming)const;

	inline void setCoefficientReflection(float value) {kr=value;}
	inline void setReflectiveColor(const glm::vec3& value) {reflectiveColor=value;}
};

#endif