#ifndef FLATMESHTRIANGLE_H
#define FLATMESHTRIANGLE_H
#include "MeshTriangle.h"

class FlatMeshTriangle:public MeshTriangle
{
public:
	FlatMeshTriangle(void);

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
};

#endif