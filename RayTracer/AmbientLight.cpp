#include "AmbientLight.h"
#include "DebugMemory.h"

AmbientLight::AmbientLight(bool useShadows, float intensity, const glm::vec3& color)
	:Light(useShadows,color,intensity)
{
}

glm::vec3 AmbientLight::getDirection(const ShadeRec& sr)
{
	return glm::vec3(0);
}

glm::vec3 AmbientLight::L(const ShadeRec& sr)
{
	return intensity * color;
}

bool AmbientLight::inShadow(const Ray& ray,const ShadeRec& sr) const
{
	return false;
}