#ifndef RECTANGULARMAPPING_H
#define RECTANGULARMAPPING_H
#include "Mapping.h"

class RectangularMapping:public Mapping
{
public:
	RectangularMapping(void);

	virtual void getPixelCoordinates(const glm::vec3 localHitPoint, const int hres, const int vres,
		int& row, int& column)const;
};

#endif