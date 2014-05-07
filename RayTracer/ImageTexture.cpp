#include "ImageTexture.h"
#include "Mapping.h"
#include "ShadeRec.h"
#include "TexImage.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"
#include <iostream>

ImageTexture::ImageTexture(void)
	:mapping(NULL),image(NULL),hres(0),vres(0)
{
}


ImageTexture::~ImageTexture(void)
{
	if(image != NULL)
	{
		delete image;
		image = NULL;
	}

	if(mapping != NULL)
	{
		delete mapping;
		mapping = NULL;
	}
}

glm::vec3 ImageTexture::getColor(const ShadeRec& sr)const
{
	int row,column;

	if(mapping != NULL)
		mapping->getPixelCoordinates(sr.localHitPoint,hres,vres,row,column);
	else
	{
		//tileable
		/*float u = sr.u; float v = sr.v;
		while(u > 1.0f)
			u-=1;
		while(u < -1.0f)
			u+=1;
		while(v > 1.0f)
			v-=1;
		while(v < -1.0f)
			v-=1;*/
		//non tileable
		float u = clamp(sr.u,-1,1);
		float v = clamp(sr.v,-1,1);
		row = (int)fabs(u * (hres - 1));
		column = (int)fabs(v * (vres - 1));
	}

	return image->getColor(row,column);
}

void ImageTexture::setImage(TexImage* value) 
{
	image=value;
	hres = value->hres;
	vres = value->vres;
}

void ImageTexture::setMapping(Mapping* value)
{
	mapping = value;
}

void ImageTexture::cleanUp() 
{
	if(image != NULL)
	{
		delete image;
		image = NULL;
	}

	if(mapping != NULL)
	{
		delete mapping;
		mapping = NULL;
	}
}
