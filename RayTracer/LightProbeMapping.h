#ifndef LIGHTPROBEMAPPING_H
#define LIGHTPROBEMAPPING_H
#include "Mapping.h"

class LightProbeMapping:public Mapping
{
public:
	LightProbeMapping(void);
	virtual void getPixelCoordinates(const glm::vec3 localHitPoint, const int hres, const int vres,
		int& row, int& column)const;
};

#endif