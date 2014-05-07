#ifndef CYLINDRICALMAPPING_H
#define CYLINDRICALMAPPING_H
#include "Mapping.h"

class CylindricalMapping:public Mapping
{
public:
	CylindricalMapping(void);

	virtual void getPixelCoordinates(const glm::vec3 localHitPoint, const int hres, const int vres,
		int& row, int& column)const;
};

#endif