#ifndef EMISSIVE_H
#define EMISSIVE_H
#include "Material.h"

class Emissive:public Material
{
	float radianceScale;
	glm::vec3 color;
public:
	Emissive(float radiance = 1.0, const glm::vec3& color = glm::vec3(1.0));
	virtual glm::vec3 shade(const ShadeRec& sr)const;
	virtual glm::vec3 areaLightShade(const ShadeRec& sr)const;
	virtual glm::vec3 getRadiance(const ShadeRec& sr)const;

	inline void setRadianceScale(float value) {radianceScale = value;}
	inline void setColor(const glm::vec3& value) {color = value;}
};

#endif