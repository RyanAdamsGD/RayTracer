#include "FileLoader.h"
#include "ShapeData.h"
#include "Vertex.h"
#include "TexImage.h"
#include <fstream>
#include <memory>
#include "Qt\qimage.h"
#include "Grid.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Instance.h"
#include "TypeDefs.h"
#include "boost\thread\thread.hpp"
#include "FastDelegate.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

FileLoader::FileLoader(void)
{
}

ShapeData* FileLoader::loadFile(const char* fileName, unsigned int& numberOfShapeData, char*& buffer)
{
	// File structure
	// size of model data
	// numShapeData (unsigned int)
	// shapeDatas
	// verts
	// indicies
	// texture file name
	// normal map name
	// skeleton
	// animation data

	//_A*_
	//num paths
	//PathTree
	//connections
	
	numberOfShapeData = 0;

	std::ifstream File(fileName, std::ios::in | std::ios::binary);
	if(File.is_open())
	{
		//read off the file size
		buffer = (char*) malloc(4);
		File.read (buffer, 4);

		uint size = *reinterpret_cast<uint*>(buffer);
		free(buffer);
		//read the rest of the model data
		buffer = new char[size];
		File.read(buffer,size - sizeof(uint));

		numberOfShapeData = reinterpret_cast<uint*>(buffer)[0];
		ShapeData* data;
		uint bufferHeaderOffset = sizeof(uint);
		data = reinterpret_cast<ShapeData*>(buffer + bufferHeaderOffset);
		//re align the pointers for the shapedata
		for(int i=0;i<numberOfShapeData;i++)
		{
			//read in the offsets for the pointers
			uint vertexOffset = *reinterpret_cast<uint*>(buffer + bufferHeaderOffset + (i * sizeof(ShapeData)));
			//skip 1 uint for the num verts
			uint indexOffset = *reinterpret_cast<uint*>(buffer + bufferHeaderOffset + (i * sizeof(ShapeData)) + sizeof(uint) * 2);
			//skip 1 uint for the num indicies
			uint textureOffset = *reinterpret_cast<uint*>(buffer + bufferHeaderOffset + (i * sizeof(ShapeData)) + sizeof(uint) * 4);
			uint normalMapOffset = *reinterpret_cast<uint*>(buffer + bufferHeaderOffset + (i * sizeof(ShapeData)) + sizeof(uint) * 5);
			uint skeletonOffset = *reinterpret_cast<uint*>(buffer + bufferHeaderOffset + (i * sizeof(ShapeData)) + sizeof(uint) * 6);
			//skip 1 uint for the num bones
			uint animationOffset = *reinterpret_cast<uint*>(buffer + bufferHeaderOffset + (i * sizeof(ShapeData)) + sizeof(uint) * 8);
			//set the pointers
			data[i].verts = reinterpret_cast<Vertex*>(buffer + vertexOffset-bufferHeaderOffset);
			data[i].indices = reinterpret_cast<ushort*>(buffer + indexOffset-bufferHeaderOffset);
			data[i].textureFileName = reinterpret_cast<char*>(buffer + textureOffset-bufferHeaderOffset);
			data[i].normalMapFileName = reinterpret_cast<char*>(buffer + normalMapOffset-bufferHeaderOffset);
			//check if there is any skeleton data
			if(skeletonOffset != animationOffset)
			{
				data[i].skeleton = reinterpret_cast<void*>(buffer + skeletonOffset-bufferHeaderOffset);
			}
			else
			{
				data[i].skeleton = NULL;
			}
			//check if there is any animation data
			if(animationOffset != *reinterpret_cast<uint*>(buffer + bufferHeaderOffset + ((i+1) * sizeof(ShapeData))))
			{
				data[i].animation = reinterpret_cast<void*>(buffer + animationOffset-bufferHeaderOffset);
			}
			else
			{
				data[i].animation = NULL;
			}
		}	
		File.close();
		return data;
	}
	return NULL;
}

TexImage* FileLoader::loadImage(const char* fileName)
{
	QImage image = QImage();
	image.load(fileName);
	if(!image.isNull())
	{
		if(image.format() != QImage::Format_RGB32)
			image.convertToFormat(QImage::Format_RGB32);

		TexImage* texture = new TexImage;
		uint size = image.byteCount();
		uchar* bits = new uchar[size];
		memcpy(bits,image.bits(),size);
		texture->setImage(bits,image.height(),image.width());
		return texture;
	}
	return NULL;
}

Grid* FileLoader::loadSphereFile(const char* fileName,const glm::mat4& transform)
{
	Grid *sphereGrid = new Grid;

	std::ifstream File(fileName, std::ios::in | std::ios::binary);
	if(File.is_open())
	{
		//read off the file size
		char* buffer = new char[4];
		File.read (buffer, 4);

		uint size = *reinterpret_cast<uint*>(buffer);
		delete [] buffer;

		buffer = new char[size - sizeof(uint)];
		File.read(buffer,size - sizeof(uint));
		size = *reinterpret_cast<uint*>(buffer);
		uint particleSize = sizeof(float) + sizeof(glm::vec3);
		float radius;
		glm::vec3 position;
		for(uint i=0;i<size;i++)
		{
			radius = *reinterpret_cast<float*>(buffer+ (sizeof(uint) + i * particleSize));
			position = *reinterpret_cast<glm::vec3*>(buffer + (sizeof(uint) + i * particleSize + sizeof(float)));
			position = glm::vec3(glm::vec4(position,1) * transform);
			sphereGrid->addObject(new Sphere(position,radius));
		}
		delete [] buffer;
	}

	return sphereGrid;
}

void FileLoader::createCylinderGrid(Grid* cylinderGrid, char* buffer, uint size,const glm::mat4& transform)
{
	uint strandSize = sizeof(glm::vec3)*2;
	glm::vec3 position1, position2;
	float radius = 0.005f;
	float rotationX, rotationZ;
	float length, invLength;
	float convertedRotationAngle, rotationAngle;
	glm::mat4 currentTransform;
	glm::vec3 cross, rot;
	uint count=0;

	for(uint i=0;i<size;i++)
	{
		position1 = *reinterpret_cast<glm::vec3*>(buffer + i * strandSize);
		position2 = *reinterpret_cast<glm::vec3*>(buffer + i * strandSize + sizeof(glm::vec3));

		rot = position2 - position1;
		length = glm::length(rot);

		if(length == 0)
			continue;
		//check for infinity
		else if(length * 0.0f != 0.0f)
			continue;
		else
			invLength = 1.0f/length;

		//create cylinder
		Cylinder* cylinder = new Cylinder(-length,length,radius);

		rotationAngle= acosf(glm::dot(glm::vec3(0.0f,1.0f,0.0f),rot * invLength));
		//convert to radians
		convertedRotationAngle = rotationAngle * _180_PI;
		//get rotation vector
		cross = glm::cross(glm::vec3(0.0f,1.0f,0.0f),rot);
		if(cross.x == 0.0f && cross.y == 0.0f && cross.z == 0.0f || (rot.x == 0.0f && rot.y == 1.0f && rot.z == 0.0f))
		{
			cross.y = 1.0f;
			convertedRotationAngle = 0;
		}

		assert(convertedRotationAngle * 0.0f == 0.0f);
		//create transform matrix
		currentTransform = glm::translate(position1) * glm::rotate(convertedRotationAngle,cross);
		
		cylinderGrid->addObject(new Instance(cylinder,currentTransform));
	}
	std::cout<<count<<std::endl;
}

Grid** FileLoader::loadCylinderFile(const char* fileName, uint& count, const glm::mat4& transform)
{
	std::ifstream File(fileName, std::ios::in | std::ios::binary);
	if(File.is_open())
	{
		//read off the file size
		char* buffer = new char[4];
		File.read (buffer, 4);

		uint size = *reinterpret_cast<uint*>(buffer);
		delete [] buffer;

		buffer = new char[size - sizeof(uint)];
		File.read(buffer,size - sizeof(uint));
		size = *reinterpret_cast<uint*>(buffer);
		uint strandSize = sizeof(glm::vec3)*2;

		count = size / MAX_NUMBER_OF_OBJECTS_IN_GRID + 1;
		Grid **cylinderGrid = new Grid*[count];
		for(uint i=0;i<count;i++)
		{
			cylinderGrid[i] = new Grid;
		}
		
		for(uint i=0;i<count;i++)
		{
			if(i != count-1)
				createCylinderGrid(cylinderGrid[i],&buffer[(strandSize * MAX_NUMBER_OF_OBJECTS_IN_GRID * i) + sizeof(uint)], MAX_NUMBER_OF_OBJECTS_IN_GRID, transform);
			else
				createCylinderGrid(cylinderGrid[i],&buffer[(strandSize * MAX_NUMBER_OF_OBJECTS_IN_GRID * i) + sizeof(uint)], size - (MAX_NUMBER_OF_OBJECTS_IN_GRID * i), transform);
		}

		delete [] buffer;
		return cylinderGrid;
	}
	else
	{
		count = 0;
		return NULL;
	}
		
}
