#ifndef REFLECTIVE_H
#define REFLECTIVE_H
#include "Phong.h"
class PerfectSpecular;

class Reflective:public Phong
{
	PerfectSpecular* reflectiveBrdf;
public:
	Reflective(void);
	virtual ~Reflective(void);

	virtual glm::vec3 shade(const ShadeRec& sr)const;
	virtual glm::vec3 pathShade(const ShadeRec& sr)const;

	inline void setReflectiveBrdf(PerfectSpecular* value) {reflectiveBrdf=value;}
	void setReflectiveColor(const glm::vec3& value);
	void setKReflective(float value);
};

#endif