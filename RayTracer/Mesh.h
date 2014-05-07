#ifndef MESH_H
#define MESH_H
#include <vector>
#include "glm\gtx\transform.hpp"
#include "TypeDefs.h"
class FlatUVMeshTriangle;
class SmoothUVMeshTriangle;

class Mesh
{
public:
	Mesh(void);

	std::vector<glm::vec3> verts;
	std::vector<uint> indicies;
	std::vector<glm::vec3> normals;		//averaged normals
	std::vector<std::vector<int>> vertexFaces;		//faces shared by each vert
	std::vector<float> u;
	std::vector<float> v;
	int numVerts;
	int numTris;
};

#endif