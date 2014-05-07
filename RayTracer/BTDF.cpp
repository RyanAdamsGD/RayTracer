#include "BTDF.h"
#include "DebugMemory.h"

BTDF::BTDF(void)
{
}

glm::vec3 BTDF::f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& transmitted)const
{
	return glm::vec3(0.0f);
}

glm::vec3 BTDF::sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& transmitted)const
{
	return glm::vec3(0.0f);
}

glm::vec3 BTDF::rho(const ShadeRec& sr, const glm::vec3& incoming)const
{
	return glm::vec3(0.0f);
}
