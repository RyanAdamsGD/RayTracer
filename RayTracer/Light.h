#ifndef LIGHT_H
#define LIGHT_H
#include "glm\gtx\transform.hpp"
class ShadeRec;
class Ray;

class Light
{
protected:
	bool useShadows;
	glm::vec3 color;
	float intensity;
public:
	Light(bool useShadows,const glm::vec3& color, float intensity);
	virtual glm::vec3 getDirection(const ShadeRec& sr) = 0;
	virtual glm::vec3 L(const ShadeRec& sr) = 0;
	virtual float G(const ShadeRec& sr)const;
	virtual float pdf(const ShadeRec& sr)const;
	virtual bool inShadow(const Ray& ray,const ShadeRec& sr)const = 0;

	inline void setUseShadows(bool value) {useShadows = value;}
	inline void setColor(const glm::vec3& value) {color = value;}
	inline void setIntensity(float value) {intensity = value;}
	bool castsShadows() {return useShadows;}
};

#endif