#include "TexImage.h"
#include <assert.h>
#include "DebugMemory.h"

TexImage::TexImage(void)
{
}

glm::vec3 TexImage::getColor(const uint row,const uint column)const
{
	assert(row < hres && column < vres);
	unsigned index = (column * hres + row) * 4;
	float b = image[index];
	float g = image[index+1];
	float r = image[index+2];
	return glm::vec3(r,g,b) / 255.0f;
}

TexImage::~TexImage(void)
{
	if(image != NULL)
	{
		delete [] image;
		image = NULL;
	}
}

void TexImage::setImage(unsigned char* value,int hieght, int width) 
{
	image=value;
	hres=width;
	vres=hieght;
}