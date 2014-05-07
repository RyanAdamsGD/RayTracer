#ifndef AREALIGHT_H
#define AREALIGHT_H
#include "Light.h"
class GeometricObject;
class Material;

class AreaLight:public Light
{
	GeometricObject* object;
	Material* material;
	glm::vec3 samplePoint;
	glm::vec3 lightNormal;
	glm::vec3 reflected;	//unit vector from hit point to sample point
public:
	AreaLight(bool useShadows,const glm::vec3& color, float intensity);
	~AreaLight(void);

	virtual glm::vec3 getDirection(const ShadeRec& sr);
	virtual glm::vec3 L(const ShadeRec& sr);
	virtual float G(const ShadeRec& sr)const;
	virtual float pdf(const ShadeRec& sr)const;
	virtual bool inShadow(const Ray& ray,const ShadeRec& sr)const;

	void setObject(GeometricObject* value);
	void setMaterial(Material* value);
};

#endif