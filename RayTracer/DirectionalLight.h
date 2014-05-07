#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "Light.h"


class DirectionalLight:public Light
{
	glm::vec3 direction;
public:
	DirectionalLight();
	DirectionalLight(bool useShadows, float intensity,const glm::vec3 color,const glm::vec3& direction);
	virtual glm::vec3 getDirection(const ShadeRec& sr);
	virtual glm::vec3 L(const ShadeRec& sr);
	virtual bool inShadow(const Ray& ray,const ShadeRec& sr)const;

	inline void setDirection(const glm::vec3 value) {direction=value;}
};

#endif