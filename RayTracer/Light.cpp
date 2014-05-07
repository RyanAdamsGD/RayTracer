#include "Light.h"
#include "DebugMemory.h"

Light::Light(bool useShadows,const glm::vec3& color, float intensity)
	:useShadows(useShadows),color(color),intensity(intensity)
{
}

float Light::G(const ShadeRec& sr)const
{
	return 1.0f;
}

float Light::pdf(const ShadeRec& sr)const
{
	return 1.0f;
}