#ifndef SMOOTHUVMESHTRIANGLE_H
#define SMOOTHUVMESHTRIANGLE_H
#include "SmoothMeshTriangle.h"

class SmoothUVMeshTriangle:public SmoothMeshTriangle
{
public:
	SmoothUVMeshTriangle(void);

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
};

#endif