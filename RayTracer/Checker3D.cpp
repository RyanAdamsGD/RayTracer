#include "Checker3D.h"
#include "ShadeRec.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

Checker3D::Checker3D(void)
{
}


Checker3D::~Checker3D(void)
{
}

glm::vec3 Checker3D::getColor(const ShadeRec& sr)const
{
	float eps = -0.00018379326f; //small random number
	float x = sr.localHitPoint.x;
	float y = sr.localHitPoint.y;
	float z = sr.localHitPoint.z;

	if(((int)floor(x/size) + (int)floor(y/size) + (int)floor(z / size)) % 2 == 0 )
		return color1;
	else
		return color2;
}