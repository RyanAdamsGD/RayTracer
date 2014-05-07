#ifndef SHADEREC_H
#define SHADEREC_H
#include "glm\gtx\transform.hpp"
#include "Ray.h"
class World;
class Material;

class ShadeRec
{
public:
	bool hitObject;
	Material* material;
	int depth;		//recursion depth
	float u;
	float v;
	float t;
	glm::vec3 localHitPoint;	//for attaching textures to objects
	glm::vec3 hitPoint;		//world coor of hit point
	glm::vec3 normal;
	glm::vec3 color;
	Ray ray;		//for specular lights
	glm::vec3 direction;	//for area lights
	World& world;


	ShadeRec(World& world);
	ShadeRec(const ShadeRec& shadeRec);
	~ShadeRec();

	ShadeRec& operator= (const ShadeRec& rhs);
};

#endif