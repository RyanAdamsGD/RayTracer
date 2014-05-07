#ifndef MESHTRIANGLE_H
#define MESHTRIANGLE_H
#include "GeometricObject.h"
class Mesh;

class MeshTriangle:public GeometricObject
{
protected:
	Mesh* mesh;
	int index0,index1,index2;
	glm::vec3 normal;
	float area;

	float interpolateU(float beta, float gamma) const;
	float interpolateV(float beta, float gamma) const;
public:
	MeshTriangle(void);
	MeshTriangle(Mesh* mesh, const int index0, const int index1, const int index2);
	virtual ~MeshTriangle(void);

	void computeNormal(const bool reverseNormal);

	virtual bool shadowHit(const Ray& ray, float& tmin) const;
	virtual BoundingBox getBoundingBox()const;
	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const = 0;

	inline void setMesh(Mesh* value) {mesh=value;}
	virtual glm::vec3 getNormal()const {return normal;}
	inline void setIndicies(const int index0, const int index1, const int index2)
		{this->index0=index0;this->index1=index1;this->index2=index2;}
	inline void setNormal(const glm::vec3& value) {normal=value;}
};

#endif