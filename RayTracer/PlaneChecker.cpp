#include "PlaneChecker.h"
#include "ShadeRec.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

PlaneChecker::PlaneChecker(void)
{
}


PlaneChecker::~PlaneChecker(void)
{
}

glm::vec3 PlaneChecker::getColor(const ShadeRec& sr)const
{
	float x = sr.localHitPoint.x;
	float z = sr.localHitPoint.z;
	int ix = floor(x / size);
	int iz = floor(z / size);
	float fx = x / size - ix;
	float fz = z / size - iz;
	float width = 0.5f * outlineWidth / size;
	bool inOutline = (fx < width || fx > 1.0f - width) || (fz < width || fz > 1.0f - width);

	if(!inOutline)
	{
	if((ix + iz) % 2 == 0)
		return color1;
	else
		return color2;
	}
	return outLineColor;
}
