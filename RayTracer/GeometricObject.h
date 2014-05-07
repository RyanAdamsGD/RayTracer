#ifndef GEOMETRICOBJECT_H
#define GEOMETRICOBJECT_H
#include "glm\gtx\transform.hpp"
#include "BoundingBox.h"
class Ray;
class ShadeRec;
class Material;
class Sampler;

class GeometricObject
{
protected:
	mutable Material* material;
	static const float KEpsilon;
	bool castsShadows;
	Sampler* sampler;
	float invArea;

public:
	GeometricObject();
	virtual ~GeometricObject();
	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const = 0;
	virtual bool shadowHit(const Ray& ray, float& tmin) const = 0;
	
	virtual glm::vec3 sample();
	virtual float pdf(const ShadeRec& sr)const;
	virtual glm::vec3 getNormal(const glm::vec3& point) const;

	virtual void setMaterial(Material* value);

	virtual BoundingBox getBoundingBox()const = 0;

	inline Material* getMaterial() {return material;}
	inline virtual void setCastShadows(bool value) {castsShadows = value;}
	virtual void setSampler(Sampler* sampler);
};

#endif