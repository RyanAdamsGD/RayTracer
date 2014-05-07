#ifndef CONSTANTCOLOR_H
#define CONSTANTCOLOR_H
#include "Texture.h"

class ConstantColor:public Texture
{
	glm::vec3 color;
public:
	ConstantColor(void);

	virtual glm::vec3 getColor(const ShadeRec& sr)const;

	inline void setColor(const glm::vec3& value) {color=value;}
};

#endif