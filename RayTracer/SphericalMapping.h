#ifndef SPHERICALMAPPING_H
#define SPHERICALMAPPING_H
#include "Mapping.h"

class SphericalMapping:public Mapping
{
public:
	SphericalMapping(void);

	virtual void getPixelCoordinates(const glm::vec3 localHitPoint, const int hres, const int vres,
		int& row, int& column)const;
};

#endif