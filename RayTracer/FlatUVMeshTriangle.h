#ifndef FLATUVMESHTRIANGLE_H
#define FLATUVMESHTRIANGLE_H
#include "FlatMeshTriangle.h"

class FlatUVMeshTriangle:public FlatMeshTriangle
{
public:
	FlatUVMeshTriangle(void);
	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
};

#endif