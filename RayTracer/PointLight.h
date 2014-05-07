#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light.h"

class PointLight:public Light
{
	glm::vec3 position;
public:
	PointLight(void);
	PointLight(bool useShadows, float intensity,const glm::vec3& color, const glm::vec3& position);
	virtual glm::vec3 getDirection(const ShadeRec& sr);
	virtual glm::vec3 L(const ShadeRec& sr);
	virtual bool inShadow(const Ray& ray,const ShadeRec& sr)const;

	inline void setPosition(const glm::vec3& value) {position=value;}
};

#endif