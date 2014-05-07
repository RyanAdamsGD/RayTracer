#ifndef SMOOTHMESHTRIANLGE_H
#define SMOOTHMESHTRIANLGE_H
#include "MeshTriangle.h"

class SmoothMeshTriangle:public MeshTriangle
{
public:
	SmoothMeshTriangle(void);
	glm::vec3 interpolateNormals(float beta, float gamma)const;

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;
};

#endif