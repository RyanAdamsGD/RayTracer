#include "SphericalMapping.h"
#include "TypeDefs.h"
#include "DebugMemory.h"

SphericalMapping::SphericalMapping(void)
{
}


void SphericalMapping::getPixelCoordinates(const glm::vec3 localHitPoint, const int hres, const int vres,
		int& row, int& column)const
{
	//first compute theta and phi
	float theta = acos(localHitPoint.y);
	float phi = atan2(localHitPoint.x,localHitPoint.z);
	if(phi < 0.0)
		phi += TWO_PI;

	//next map theta and phi to (u,v) in [0,1] by [0,1]
	float u = phi * INV_TWO_PI;
	float v = 1 - theta * INV_PI;

	//finally map u and v to the texel coordinates
	column = int((hres-1) * u);
	row = int((vres -1) * v);
}
