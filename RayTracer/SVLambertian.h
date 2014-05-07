#ifndef SVLAMBERTIAN_H
#define SVLAMBERTIAN_H
#include "BRDF.h"
class Texture;

class SVLambertian:public BRDF
{
	Texture* texture;
	float kd;
public:
	SVLambertian(void);
	virtual ~SVLambertian(void);

	virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& reflected)const;
	virtual glm::vec3 rho(const ShadeRec& sr, const glm::vec3& incoming)const;
	virtual glm::vec3 sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected, float& pdf)const;

	inline void setReflectionCoefficient(float value) {kd=value;}
	void setTexture(Texture* value);
	Texture* getTexture() {return texture;}
};

#endif