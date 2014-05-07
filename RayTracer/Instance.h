#ifndef INSTANCE_H
#define INSTANCE_H
#include "GeometricObject.h"
#include "BoundingBox.h"

class Instance:public GeometricObject
{
	glm::mat4 transform;
	glm::mat4 invTransform;
	GeometricObject* object;
	bool transformTexture;
	BoundingBox bbox;
	
public:
	Instance();
	Instance(GeometricObject* object);
	Instance(GeometricObject* object,const glm::mat4& transform);
	~Instance();
	void computeBoundingBox();

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual BoundingBox getBoundingBox()const;

	void setTransform(const glm::mat4& value);
	inline void setTransformTexture(bool value) {transformTexture = value;}
	void setObject(GeometricObject* value);
};

#endif