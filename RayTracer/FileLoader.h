#ifndef FILELOADER_H
#define FILELOADER_H
class ShapeData;
class TexImage;
class Grid;
#include "glm\gtx\transform.hpp"

class FileLoader
{
	static void createCylinderGrid(Grid* cylinderGrid, char* buffer, unsigned int size,const glm::mat4& transform);
public:
	FileLoader(void);
	static Grid* loadSphereFile(const char* fileName, const glm::mat4& transform = glm::mat4());
	static ShapeData* loadFile(const char* fileName, unsigned int& numberOfShapeData, char*& buffer);
	static TexImage* loadImage(const char* fileName);
	static Grid** loadCylinderFile(const char* fileName, unsigned int& count, const glm::mat4& transform = glm::mat4());
};

#endif