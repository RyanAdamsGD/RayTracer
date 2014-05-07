#include "LightProbeMapping.h"
#include "TypeDefs.h"
#include "DebugMemory.h"

LightProbeMapping::LightProbeMapping(void)
{
}


void LightProbeMapping::getPixelCoordinates(const glm::vec3 localHitPoint, const int hres, const int vres,
		int& row, int& column)const
{
	float x = localHitPoint.x, y = localHitPoint.y, z = localHitPoint.z;
	float d = sqrt(x*x + y*y);
	float sinBeta = y/d;
	float cosBeta = x/d;
	float alpha;

	//if(mapType == lightProbe) //the default
		alpha = acos(z);
	/*if(mapType == panoramic)
		alpha = acos(-z);*/

	float r = alpha * INV_PI;
	float u = (1.0 + r * cosBeta) * 0.5;
	float v = (1.0 + r * sinBeta) * 0.5;

	column = int((hres - 1) * u);
	row = int((vres - 1) * v);
}
