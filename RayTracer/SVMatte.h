#ifndef SVMATTE_H
#define SVMATTE_H
#include "Material.h"
class Texture;
class SVLambertian;

class SVMatte:public Material
{
	SVLambertian* ambientBrdf;
	SVLambertian* diffuseBrdf;
public:
	SVMatte(void);
	virtual ~SVMatte(void);

	virtual glm::vec3 shade(const ShadeRec& sr)const;
	virtual glm::vec3 areaLightShade(const ShadeRec& sr)const;
	virtual glm::vec3 pathShade(const ShadeRec& sr)const;

	void setKAmbient(float k);
	void setKDiffuse(float k);
	void setTexture(Texture* texture);
};

#endif