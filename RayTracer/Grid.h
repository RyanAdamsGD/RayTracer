#ifndef GRID_H
#define GRID_H
#include "Compound.h"
#include <vector>
#include "BoundingBox.h"
class Mesh;
class Vertex;

class Grid:public Compound
{
	std::vector<GeometricObject*> cells;
	BoundingBox bbox;
	int nx,ny,nz; //cell counts
	glm::vec3 minCoordinate();
	glm::vec3 maxCoordinate();
	Mesh* mesh; //holds triangle data

	void calculateNormal(std::vector<glm::vec3>& list,const int meshIndex);
	void readFile(const char* fileName, const int triangleType,const glm::mat4& transform);
public:
	unsigned int numberOfMeshes;
	Grid(void);
	~Grid(void);

	virtual BoundingBox getBoundingBox();
	void setupCells();
	virtual bool hit(const Ray&,float& tmin, ShadeRec& sr)const;
	virtual bool shadowHit(const Ray& ray, float& tmin)const;

	void readFlatTriangle(const char* fileName,const glm::mat4& transform = glm::mat4());
	void readSmoothTriangle(const char* fileName,const glm::mat4& transform = glm::mat4());
	void readFlatUVTriangle(const char* fileName,const glm::mat4& transform = glm::mat4());
	void readSmoothUVTriangle(const char* fileName,const glm::mat4& transform = glm::mat4());
	void setMaterial(Material* material,const unsigned int index);
};

#endif