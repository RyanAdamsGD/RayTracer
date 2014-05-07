#ifndef TRANSPARENT_H
#define TRANSPARENT_H
#include "Phong.h"
class PerfectSpecular;
class PerfectTransmitter;

class Transparent:public Phong
{
	PerfectSpecular* reflectiveBrdf;
	PerfectTransmitter* specularBtfd;
public:
	Transparent(void);
	virtual ~Transparent(void);

	virtual glm::vec3 shade(const ShadeRec& sr)const;

	void setIor(float value);
	void setKReflective(float value);
	void setKTransparent(float value);
};

#endif