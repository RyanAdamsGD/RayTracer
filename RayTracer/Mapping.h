#ifndef MAPPING_H
#define MAPPING_H
#include "glm\gtx\transform.hpp"

class Mapping
{
public:
	Mapping(void);

	virtual void getPixelCoordinates(const glm::vec3 localHitPoint, const int hres, const int vres,
		int& row, int& column)const = 0;
};

#endif