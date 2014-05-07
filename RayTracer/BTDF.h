#ifndef BTDF_H
#define BTDF_H
#include "glm\gtx\transform.hpp"
class ShadeRec;

class BTDF
{
public:
	BTDF(void);

	virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& transmitted)const;
	virtual glm::vec3 sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& transmitted)const;
	virtual glm::vec3 rho(const ShadeRec& sr, const glm::vec3& incoming)const;
	virtual bool tir(const ShadeRec& sr)const = 0;
};

#endif