#include "Grid.h"
#include "TypeDefs.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Material.h"
#include "GeometricObject.h"
#include <iostream>
#include "ShapeData.h"
#include "FileLoader.h"
#include "Vertex.h"
#include "Mesh.h"
#include "FlatMeshTriangle.h"
#include "FlatUVMeshTriangle.h"
#include "SmoothMeshTriangle.h"
#include "SmoothUVMeshTriangle.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"



#include <typeinfo.h>
//about 8 times more cells than objects
#define CELL_MULTIPLIER 2.0 

Grid::Grid(void)
	:mesh(NULL),numberOfMeshes(0)
{
}


Grid::~Grid(void)
{
	if(mesh != NULL)
	{
		delete[] mesh;
		mesh = NULL;
	}

	uint size = cells.size();
	for(uint i=0;i<size;i++)
	{
		if(cells[i] != NULL)
			if(typeid(*cells[i]) == typeid(Compound))
			{
				((Compound*)cells[i])->clearObjects();
				delete cells[i];
			}
		cells[i] = NULL;
	}
	cells.clear();
}

BoundingBox Grid::getBoundingBox()
{
	return bbox;
}

void Grid::setupCells()
{
	glm::vec3 p0 = minCoordinate();
	glm::vec3 p1 = maxCoordinate();

	bbox.x0 = p0.x; bbox.y0 = p0.y; bbox.z0 = p0.z;
	bbox.x1 = p1.x; bbox.y1 = p1.y; bbox.z1 = p1.z;

	//compute number of cells
	uint numObjects = objects.size();
	float wx = p1.x - p0.x;
	float wy = p1.y - p0.y;
	float wz = p1.z - p0.z;
	float s = pow(wx * wy * wz / numObjects, 0.33333333333333f);
	nx = CELL_MULTIPLIER * wx / s + 1;
	ny = CELL_MULTIPLIER * wy / s + 1;
	nz = CELL_MULTIPLIER * wz / s + 1;

	//set up cell array
	uint numCells = nx * ny * nz;
	cells.reserve(numObjects);

	for(uint i=0;i<numCells;i++)
		cells.push_back(NULL);

	//set up temp array to hold cell counts
	std::vector<uint> counts;
	counts.reserve(numCells);

	for(int i=0;i<numCells;i++)
		counts.push_back(0);

	//place objects in cells
	BoundingBox objBox;
	uint index;

	for(uint i=0;i<numObjects;i++)
	{
		objBox = objects[i]->getBoundingBox();
		//catch verts at that are close to the edge of other boxes
		//float dx = (p1.x - p0.x) / (float)nx * 0.5f;
		//float dy = (p1.y - p0.y) / (float)ny * 0.5f;
		//float dz = (p1.z - p0.z) / (float)nz * 0.5f;
		float dx = 0.0f; float dy = 0.0f; float dz = 0.0f;

		//compute cell indicies
		int ixmin = clamp(((objBox.x0 - p0.x - dx) / (p1.x - p0.x)) * nx,0,nx - 1);
		int iymin = clamp(((objBox.y0 - p0.y - dy) / (p1.y - p0.y)) * ny,0,ny - 1);
		int izmin = clamp(((objBox.z0 - p0.z - dz) / (p1.z - p0.z)) * nz,0,nz - 1);
																
		int ixmax = clamp(((objBox.x1 - p0.x + dx) / (p1.x - p0.x)) * nx,0,nx - 1);
		int iymax = clamp(((objBox.y1 - p0.y + dy) / (p1.y - p0.y)) * ny,0,ny - 1);
		int izmax = clamp(((objBox.z1 - p0.z + dz) / (p1.z - p0.z)) * nz,0,nz - 1);

		//add objects to cells
		for(int iz=izmin;iz<=izmax;iz++)
			for(int iy=iymin;iy<=iymax;iy++)
				for(int ix=ixmin;ix<=ixmax;ix++)
				{
					index = ix + nx * iy + nx * ny * iz;

					//if there isnt an object yet add it
					if(counts[index] == 0)
					{
						cells[index] =  objects[i];
						counts[index] += 1;
					}
					else
					{
						//if this is the second object create a compound
						if(counts[index] == 1)
						{
							Compound* compound = new Compound;
							compound->addObject(cells[index]);
							compound->addObject(objects[i]);
							cells[index] = compound;
							counts[index] += 1;
						}
						else
						{
							((Compound*)cells[index])->addObject(objects[i]);
							//for testing purposes only
							counts[index] += 1;
						}
					}
				}
	}

	// display some statistics on counts
	// this is useful for finding out how many cells have no objects, one object, etc
	// comment this out if you don't want to use it

	int num_zeroes 	= 0;
	int num_ones 	= 0;
	int num_twos 	= 0;
	int num_threes 	= 0;
	int num_greater = 0;

	for (int j = 0; j < numCells; j++) {
		if (counts[j] == 0)
			num_zeroes += 1;
		if (counts[j] == 1)
			num_ones += 1;
		if (counts[j] == 2)
			num_twos += 1;
		if (counts[j] == 3)
			num_threes += 1;
		if (counts[j] > 3)
			num_greater += 1;
	}

	std::cout << "num_cells =" << numCells << std::endl;
	std::cout << "numZeroes = " << num_zeroes << "  numOnes = " << num_ones << "  numTwos = " << num_twos << std::endl;  
	std::cout << "numThrees = " << num_threes << "  numGreater = " << num_greater << std::endl;	

	counts.clear();

}

bool Grid::hit(const Ray& ray,float& tmin, ShadeRec& sr)const
{
	float t0,txMax,txMin,tyMax,tyMin,tzMax,tzMin;
	if(!bbox.hit(ray,t0,txMax,txMin,tyMax,tyMin,tzMax,tzMin))
		return false;

	int ix,iy,iz;
	glm::vec3 origin = ray.getOrigin();
	glm::vec3 direction = ray.getDirection();

	//see where the ray is in relation to the grid

	if(bbox.contains(origin))
	{
		ix = clamp((origin.x - bbox.x0) * nx / (bbox.x1 - bbox.x0),0,nx-1);
		iy = clamp((origin.y - bbox.y0) * ny / (bbox.y1 - bbox.y0),0,ny-1);
		iz = clamp((origin.z - bbox.z0) * nz / (bbox.z1 - bbox.z0),0,nz-1);
	}
	else
	{
		glm::vec3 p = origin + t0 * ray.getDirection();
		ix = clamp((p.x - bbox.x0) * nx / (bbox.x1 - bbox.x0),0,nx-1);
		iy = clamp((p.y - bbox.y0) * ny / (bbox.y1 - bbox.y0),0,ny-1);
		iz = clamp((p.z - bbox.z0) * nz / (bbox.z1 - bbox.z0),0,nz-1);
	}

	//figure out order to traverse grid in

	float dtx = (txMax - txMin) / nx;
	float dty = (tyMax - tyMin) / ny;
	float dtz = (tzMax - tzMin) / nz;

	float txNext,tyNext,tzNext;
	int ixStep,iyStep,izStep;
	int ixStop,iyStop,izStop;

	if(direction.x > 0.0f)
	{
		txNext = txMin + (ix + 1) * dtx;
		ixStep = 1;
		ixStop = nx;
	}
	else
	{
		txNext = txMin + (nx - ix) * dtx;
		ixStep = -1;
		ixStop = -1;
	}

	if(direction.x == 0.0f)
	{
		txNext = kHugeValue;
		ixStep = -1;
		ixStop = -1;
	}

	if(direction.y > 0.0f)
	{
		tyNext = tyMin + (iy + 1) * dty;
		iyStep = 1;
		iyStop = ny;
	}
	else
	{
		tyNext = tyMin + (ny - iy) * dty;
		iyStep = -1;
		iyStop = -1;
	}

	if(direction.y == 0.0f)
	{
		tyNext = kHugeValue;
		iyStep = -1;
		iyStop = -1;
	}

	if(direction.z > 0.0f)
	{
		tzNext = tzMin + (iz + 1) * dtz;
		izStep = 1;
		izStop = nz;
	}
	else
	{
		tzNext = tzMin + (nz - iz) * dtz;
		izStep = -1;
		izStop = -1;
	}

	if(direction.z == 0.0f)
	{
		tzNext = kHugeValue;
		izStep = -1;
		izStop = -1;
	}

	//traverse grid

	float t;

	while(true)
	{
		GeometricObject* object = cells[ix + nx * iy + nx * ny * iz];

		if(txNext < tyNext && txNext < tzNext)
		{
			if(object != NULL && object->hit(ray,t,sr) && t < txNext)
			{
				if(sr.material == NULL)
					sr.material = object->getMaterial();

				tmin = t;
				return true;
			}

			txNext += dtx;
			ix += ixStep;

			if(ix == ixStop)
				return false;
		}
		else if(tyNext < tzNext)
		{
			if(object != NULL && object->hit(ray,t,sr) && t < tyNext)
			{
				if(sr.material == NULL)
					sr.material = object->getMaterial();

				tmin = t;
				return true;
			}

			tyNext += dty;
			iy += iyStep;

			if(iy == iyStop)
				return false;
		}
		else
		{
			if(object != NULL && object->hit(ray,t,sr) && t < tzNext)
			{
				if(sr.material == NULL)
					sr.material = object->getMaterial();

				tmin = t;
				return true;
			}

			tzNext += dtz;
			iz += izStep;

			if(iz == izStop)
				return false;
		}
	}

	return false;
}

bool Grid::shadowHit(const Ray& ray, float& tmin)const
{
	float t0,txMax,txMin,tyMax,tyMin,tzMax,tzMin;
	if(!bbox.hit(ray,t0,txMax,txMin,tyMax,tyMin,tzMax,tzMin))
		return false;

	int ix = 0,iy = 0,iz = 0;
	glm::vec3 origin = ray.getOrigin();
	glm::vec3 direction = ray.getDirection();

	//see where the ray is in relation to the grid

	if(bbox.contains(origin))
	{
		ix = clamp((origin.x - bbox.x0) * nx / (bbox.x1 - bbox.x0),0.0f,nx-1);
		iy = clamp((origin.y - bbox.y0) * ny / (bbox.y1 - bbox.y0),0.0f,ny-1);
		iz = clamp((origin.z - bbox.z0) * nz / (bbox.z1 - bbox.z0),0.0f,nz-1);
	}
	else
	{
		glm::vec3 p = origin + t0 * ray.getDirection();
		ix = clamp((p.x - bbox.x0) * nx / (bbox.x1 - bbox.x0),0.0f,nx-1);
		iy = clamp((p.y - bbox.y0) * ny / (bbox.y1 - bbox.y0),0.0f,ny-1);
		iz = clamp((p.z - bbox.z0) * nz / (bbox.z1 - bbox.z0),0.0f,nz-1);
	}

	if(iz < 0 || ix < 0 || iy < 0)
	{
		int x;
		x = 0;
	}
	//figure out order to traverse grid in

	float dtx = (txMax - txMin) / nx;
	float dty = (tyMax - tyMin) / ny;
	float dtz = (tzMax - tzMin) / nz;

	float txNext,tyNext,tzNext;
	int ixStep,iyStep,izStep;
	int ixStop,iyStop,izStop;

	if(direction.x > 0.0f)
	{
		txNext = txMin + (ix + 1) * dtx;
		ixStep = 1;
		ixStop = nx;
	}
	else
	{
		txNext = txMin + (nx - ix) * dtx;
		ixStep = -1;
		ixStop = -1;
	}

	if(direction.x == 0.0f)
	{
		txNext = kHugeValue;
		ixStep = -1;
		ixStop = -1;
	}

	if(direction.y > 0.0f)
	{
		tyNext = tyMin + (iy + 1) * dty;
		iyStep = 1;
		iyStop = ny;
	}
	else
	{
		tyNext = tyMin + (ny - iy) * dty;
		iyStep = -1;
		iyStop = -1;
	}

	if(direction.y == 0.0f)
	{
		tyNext = kHugeValue;
		iyStep = -1;
		iyStop = -1;
	}

	if(direction.z > 0.0f)
	{
		tzNext = tzMin + (iz + 1) * dtz;
		izStep = 1;
		izStop = nz;
	}
	else
	{
		tzNext = tzMin + (nz - iz) * dtz;
		izStep = -1;
		izStop = -1;
	}

	if(direction.z == 0.0f)
	{
		tzNext = kHugeValue;
		izStep = -1;
		izStop = -1;
	}

	//traverse grid

	float t;

	while(true)
	{
		GeometricObject* object = cells[ix + nx * iy + nx * ny * iz];

		if(txNext < tyNext && txNext < tzNext)
		{
			if(object != NULL && object->shadowHit(ray,t) && t < txNext)
			{
				tmin = t;
				return true;
			}

			txNext += dtx;
			ix += ixStep;

			if(ix == ixStop)
				return false;
		}
		else if(tyNext < tzNext)
		{
			if(object != NULL && object->shadowHit(ray,t) && t < tyNext)
			{
				tmin = t;
				return true;
			}

			tyNext += dty;
			iy += iyStep;

			if(iy == iyStop)
				return false;
		}
		else
		{
			if(object != NULL && object->shadowHit(ray,t) && t < tzNext)
			{
				tmin = t;
				return true;
			}

			tzNext += dtz;
			iz += izStep;

			if(iz == izStop)
				return false;
		}
	}

	return false;
}

glm::vec3 Grid::maxCoordinate()
{
	BoundingBox bBox;
	glm::vec3 p1(-kHugeValue);

	int numObjects = objects.size();
	for(int i=0;i<numObjects;i++)
	{
		bBox = objects[i]->getBoundingBox();

		if(bBox.x1 > p1.x)
			p1.x = bBox.x1;
		if(bBox.y1 > p1.y)
			p1.y = bBox.y1;
		if(bBox.z1 > p1.z)
			p1.z = bBox.z1;
	}

	p1 += glm::vec3(KEpsilon);

	return p1;
}

glm::vec3 Grid::minCoordinate()
{
	BoundingBox bBox;
	glm::vec3 p0(kHugeValue);

	int numObjects = objects.size();
	for(int i=0;i<numObjects;i++)
	{
		bBox = objects[i]->getBoundingBox();

		if(bBox.x0 < p0.x)
			p0.x = bBox.x0;
		if(bBox.y0 < p0.y)
			p0.y = bBox.y0;
		if(bBox.z0 < p0.z)
			p0.z = bBox.z0;
	}

	p0 -= glm::vec3(KEpsilon);

	return p0;
}

void Grid::readFlatTriangle(const char* fileName,const glm::mat4& transform)
{
	readFile(fileName,0,transform);
}

void Grid::readSmoothTriangle(const char* fileName,const glm::mat4& transform)
{
	readFile(fileName,1,transform);
}

void Grid::readFlatUVTriangle(const char* fileName,const glm::mat4& transform)
{
	readFile(fileName,2,transform);
}

void Grid::readSmoothUVTriangle(const char* fileName,const glm::mat4& transform)
{
	readFile(fileName,3,transform);
}

void Grid::readFile(const char* fileName, const int triangleType,const glm::mat4& transform)
{
	//load in our shape data
	char* buffer;
	ShapeData* shapeData = FileLoader::loadFile(fileName,numberOfMeshes,buffer);
	assert(shapeData != NULL);
	//create the appropriate number of meshes
	mesh = new Mesh[numberOfMeshes];

	for(uint i=0;i<numberOfMeshes;i++)
	{
		Mesh& currentMesh = mesh[i];
		ShapeData& currentShapeData = shapeData[i];

		currentMesh.numVerts = currentShapeData.numVerts;
		currentMesh.numTris = currentShapeData.numIndices/3;

		for(uint j=0;j<currentShapeData.numIndices;j++)
		{
			currentMesh.indicies.push_back(currentShapeData.indices[j]);
		}

		for(uint j=0;j<currentShapeData.numVerts;j++)
		{
			Vertex& vert = currentShapeData.verts[j];
			glm::vec3 position = glm::vec3(glm::vec4(vert.position.x,vert.position.y,vert.position.z,1.0) * glm::transpose(transform));
			currentMesh.verts.push_back(position);
			currentMesh.u.push_back(vert.uv.x);
			currentMesh.v.push_back(vert.uv.y);
			currentMesh.normals.push_back(glm::normalize(glm::vec3(glm::vec4(vert.normal.x,vert.normal.y,vert.normal.z,0.0f) * glm::transpose(transform))));
		}

		//get the triangle normals for the current mesh
		std::vector<glm::vec3> normals;
		calculateNormal(normals,i);

		for(uint j=0;j<currentMesh.numTris;j++)
		{
			//create the proper type of triangle
			MeshTriangle* triangle;
			switch(triangleType)
			{
			case 0:
				triangle = new FlatMeshTriangle();
				triangle->setMesh(&currentMesh);
				triangle->setIndicies(currentMesh.indicies[j*3],currentMesh.indicies[j*3+1],currentMesh.indicies[j*3+2]);
				triangle->setNormal(normals[j]);
				objects.push_back(triangle);
				break;
			case 1:
				triangle = new SmoothMeshTriangle();
				triangle->setMesh(&currentMesh);
				triangle->setIndicies(currentMesh.indicies[j*3],currentMesh.indicies[j*3+1],currentMesh.indicies[j*3+2]);
				triangle->setNormal(normals[j]);
				objects.push_back(triangle);
				break;
			case 2:
				triangle = new FlatUVMeshTriangle();
				triangle->setMesh(&currentMesh);
				triangle->setIndicies(currentMesh.indicies[j*3],currentMesh.indicies[j*3+1],currentMesh.indicies[j*3+2]);
				triangle->setNormal(normals[j]);
				objects.push_back(triangle);
				break;
			case 3:
				triangle = new SmoothUVMeshTriangle();
				triangle->setMesh(&currentMesh);
				triangle->setIndicies(currentMesh.indicies[j*3],currentMesh.indicies[j*3+1],currentMesh.indicies[j*3+2]);
				triangle->setNormal(normals[j]);
				objects.push_back(triangle);
				break;
			}
		}

		normals.clear();
	}
	shapeData = NULL;
	delete [] buffer;
	buffer = NULL;
}

void Grid::calculateNormal(std::vector<glm::vec3>& list,const int meshIndex)
{
	Mesh& currentMesh = mesh[meshIndex];
	for(uint i=0;i<currentMesh.numTris;i++)
	{
		uint index0 = currentMesh.indicies[i*3], index1 = currentMesh.indicies[i*3+1], index2 = currentMesh.indicies[i*3+2]; 
		glm::vec3 normal = glm::cross(currentMesh.verts[index0] - currentMesh.verts[index2],currentMesh.verts[index1] - currentMesh.verts[index2]);
		int flip = 0;
		normal = glm::normalize(normal);		
		list.push_back(normal);
	}

}

void Grid::setMaterial(Material* material,const unsigned int index)
{
	if(mesh != NULL)
	{
		uint startIndex = 0;
		for(uint i=0;i<index;i++)
			startIndex += mesh[i].numTris;

		uint size = mesh[index].numTris;
		for(uint i=0;i<size;i++)
			objects[startIndex + i]->setMaterial(material);
	}
	else
	{
		uint size = objects.size();
		for(uint i=0;i<size;i++)
			objects[i]->setMaterial(material);
	}
}