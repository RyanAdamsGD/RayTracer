#ifndef CHECKER3D_H
#define CHECKER3D_H
#include "Texture.h"

class Checker3D:public Texture
{
	float size;
	glm::vec3 color1, color2;
public:
	Checker3D(void);
	virtual ~Checker3D(void);

	virtual glm::vec3 getColor(const ShadeRec& sr)const;

	void setSize(float value) {size=value;}
	void setColor1(const glm::vec3& value) {color1=value;}
	void setColor2(const glm::vec3& value) {color2=value;}
};

#endif