#ifndef PLANECHECKER_H
#define PLANECHECKER_H
#include "Texture.h"

class PlaneChecker:public Texture
{
	float size, outlineWidth;
	glm::vec3 color1, color2, outLineColor;
public:
	PlaneChecker(void);
	virtual ~PlaneChecker(void);

	virtual glm::vec3 getColor(const ShadeRec& sr)const;

	void setSize(float value) {size=value;}
	void setoutLineWidth(float value) {outlineWidth=value;}
	void setColor1(const glm::vec3& value) {color1=value;}
	void setColor2(const glm::vec3& value) {color2=value;}
	void setOutLineColor(const glm::vec3& value) {outLineColor=value;}
};

#endif