#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H
#include "Texture.h"
class Mapping;
class TexImage;

class ImageTexture:public Texture
{
	int hres, vres;
	TexImage* image;
	Mapping* mapping;
public:
	ImageTexture(void);
	virtual ~ImageTexture(void);
	virtual void cleanUp();

	virtual glm::vec3 getColor(const ShadeRec& sr)const;

	void setImage(TexImage* value);
	void setMapping(Mapping* value);
};

#endif