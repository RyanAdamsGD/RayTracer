#ifndef GLOSSYREFLECTOR_H
#define GLOSSYREFLECTOR_H
#include "Phong.h"

class GlossyReflector:public Phong
{
	GlossySpecular* glossySpecularBrdf;
public:
	GlossyReflector(void);

	void setSamples(const int numSamples, float exp);
	void setSetKReflective(float value);
	void setExponentReflective(float exp);
	void setColorReflective(const glm::vec3& value);

	virtual glm::vec3 areaLightShade(const ShadeRec& sr)const;
};

#endif