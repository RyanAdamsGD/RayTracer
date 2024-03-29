#ifndef SHAPEDATA_H
#define SHAPEDATA_H
#include "TypeDefs.h"
#include "Vertex.h"

struct ShapeData
{
	Vertex* verts;
	uint numVerts;
	ushort* indices;
	uint numIndices;
	char* textureFileName;
	char* normalMapFileName;
	void* skeleton;
	uint numBones;
	void* animation;
	uint numAnimations;
	uint frameCount;
	ShapeData() : 
	verts(0), numVerts(0), indices(0), numIndices(0), 
		textureFileName(0), normalMapFileName(0),skeleton(0),animation(0) {}
	uint vertexBufferSize() const { return numVerts * sizeof(Vertex); }
	uint indexBufferSize() const { return numIndices * sizeof(ushort); }
	uint animationBufferSize() const {return numAnimations * (sizeof(uint) + (sizeof(float) * 17) * frameCount); }
	void cleanUp()
	{
		delete[] verts;
		verts = 0;
		delete[] indices;
		indices = 0;
		numVerts = numIndices = 0;
		if(textureFileName != NULL)
		{
			delete[] textureFileName;
			textureFileName = 0;
		}
		if(skeleton != NULL)
		{
			delete [] skeleton;
			skeleton =0;
		}
		if(animation != NULL)
		{
			delete [] animation;
			animation =0;
		}
	}
};

#endif