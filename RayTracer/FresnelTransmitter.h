#ifndef FRESNELTRANSMITTER_H
#define FRESNELTRANSMITTER_H
#include "BTDF.h"

class FresnelTransmitter:public BTDF
{
	float etaIn, etaOut;
	float fresnelKt(const ShadeRec& sr) const;
public:
	FresnelTransmitter(void);

	virtual glm::vec3 sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& transmitted)const;
	virtual bool tir(const ShadeRec& sr)const;

	inline void setEtaIn(float value) {etaIn=value;}
	inline void setEtaOut(float value) {etaOut=value;}
};

#endif