#ifndef TEXIMAGE_H
#define TEXIMAGE_H
#include "glm\gtx\transform.hpp"
#include "TypeDefs.h"

class TexImage
{
	unsigned char* image;
public:
	int hres,vres;
	TexImage(void);
	~TexImage(void);

	void setImage(unsigned char* value,int hieght, int width);
	glm::vec3 getColor(const uint row,const uint column)const;
};

#endif