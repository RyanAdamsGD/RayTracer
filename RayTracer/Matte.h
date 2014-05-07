#ifndef MATTE_H
#define MATTE_H
#include "Material.h"
class Lambert;

class Matte:public Material
{
	Lambert* ambientBrdf;
	Lambert* diffuseBrdf;

public:
	Matte(void);
	virtual ~Matte(void);

	virtual glm::vec3 shade(const ShadeRec& sr)const;
	virtual glm::vec3 areaLightShade(const ShadeRec& sr)const;
	virtual glm::vec3 pathShade(const ShadeRec& sr)const;

	void setKAmbient(float k);
	void setKDiffuse(float k);
	void setColor(const glm::vec3& color);
};

#endif