#ifndef FRESNELREFLECTOR_H
#define FRESNELREFLECTOR_H
#include "BRDF.h"

class FresnelReflector:public BRDF
{
	float etaIn, etaOut;
	float fresnelKr(const ShadeRec& sr) const;
public:
	FresnelReflector(void);

	virtual glm::vec3 sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected)const;

	inline void setEtaIn(float value) {etaIn=value;}
	inline void setEtaOut(float value) {etaOut=value;}
};

#endif