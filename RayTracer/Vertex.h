#ifndef NEUMONT_VERTEX_H
#define NEUMONT_VERTEX_H
#include "TypeDefs.h"
#include "glm\glm.hpp"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
	uint boneID;
	glm::vec3 weights;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	static uint POSITION_OFFSET;
	static uint COLOR_OFFSET;
	static uint NORMAL_OFFSET;
	static uint UV_OFFSET;
	static uint SKELETONID_OFFSET;
	static uint WEIGHT_OFFSET;
	static uint TANGENT_OFFSET;
	static uint BITANGENT_OFFSET;
	static uint STRIDE;
};


#endif