#ifndef COMPOUND_H
#define COMPOUND_H
#include "GeometricObject.h"
#include <vector>
#include "BoundingBox.h"

class Compound:public GeometricObject
{
	BoundingBox createBoundingBox()const;
protected:
	BoundingBox bbox;
	std::vector<GeometricObject*> objects;
public:
	Compound(void);
	virtual ~Compound(void);

	virtual void addObject(GeometricObject* object);
	virtual void setMaterial(Material* value);
	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr)const;
	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual BoundingBox getBoundingBox()const;

	virtual void setCastShadows(bool value);
	void clearObjects();
};

#endif