#ifndef DIELECTRIC_H
#define DIELECTRIC_H
#include "Phong.h"
class FresnelTransmitter;
class FresnelReflector;

class Dielectric:public Phong
{
	FresnelReflector* fresnelBrdf;
	FresnelTransmitter* fresnelBtdf;

	glm::vec3 colorFilterIn;
	glm::vec3 colorFilterOut;
public:
	Dielectric(void);
	virtual ~Dielectric(void);

	virtual glm::vec3 shade(const ShadeRec& sr)const;

	void setEtaIn(float value); 
	void setEtaOut(float value);
	void setColorFilterIn(const glm::vec3& value); 
	void setColorFilterOut(const glm::vec3& value);
};

#endif