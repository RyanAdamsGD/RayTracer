#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H
#include "Light.h"


class AmbientLight:public Light
{
public:
	AmbientLight(bool useShadows, float intensity = 1.0f, const glm::vec3& color = glm::vec3(1.0f));
	virtual glm::vec3 getDirection(const ShadeRec& sr);
	virtual glm::vec3 L(const ShadeRec& sr);
	virtual bool inShadow(const Ray& ray,const ShadeRec& sr)const;
};

#endif