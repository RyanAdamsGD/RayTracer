#ifndef PHONG_H
#define PHONG_H
#include "Material.h"
class Lambert;
class GlossySpecular;

class Phong:public Material
{
protected:
	Lambert* ambientBrdf;
	Lambert* diffuseBrdf;
	GlossySpecular* specularBrdf;

public:
	Phong();
	virtual ~Phong();
	virtual glm::vec3 shade(const ShadeRec& sr)const;
	virtual glm::vec3 areaLightShade(const ShadeRec& sr)const;

	void setKAmbient(float k);
	void setKDiffuse(float k);
	void setKSpecular(float k);
	void setColor(const glm::vec3& color);
	void setExponent(float exp);
};

#endif