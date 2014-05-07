#ifndef PERFECTTRANSMITTER_H
#define PERFECTTRANSMITTER_H
#include "BTDF.h"

class PerfectTransmitter
{
	float ior; //index of reflection
	float kt; //transmission coefficient
	float fresnel(const ShadeRec& sr) const;
public:
	PerfectTransmitter(void);

	virtual glm::vec3 sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& transmitted)const;
	virtual bool tir(const ShadeRec& sr)const;

	inline void setIor(float value) {ior=value;}
	inline void setKt(float value) {kt=value;}
};

#endif