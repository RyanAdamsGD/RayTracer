#ifndef GLOSSYSPECULAR_H
#define GLOSSYSPECULAR_H
#include "BRDF.h"

class GlossySpecular:public BRDF
{
	float coeffiecientOfSpecularReflection;
	float phongExponent;	//exponent for how far the reflected light spreads
	glm::vec3 color;

public:
	GlossySpecular();
	GlossySpecular(Sampler* sampler, const glm::vec3& normal,const glm::vec3& color,float phongExponent, float coeffiecientOfSpecularReflection);
	virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& reflected)const;
	virtual glm::vec3 sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected, float& pdf)const;
	virtual glm::vec3 rho(const ShadeRec& sr, const glm::vec3& incoming)const;

	inline void setReflectionCoefficient(float value) {coeffiecientOfSpecularReflection=value;}
	inline void setExponent(float value) {phongExponent=value;}
	inline void setColor(const glm::vec3& value) {color=value;}
};

#endif