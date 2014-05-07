#include "Emissive.h"
#include "ShadeRec.h"
#include "DebugMemory.h"

Emissive::Emissive(float radianceScale, const glm::vec3& color)
	:radianceScale(radianceScale),color(color)
{
}

glm::vec3 Emissive::shade(const ShadeRec& sr)const
{
	if(glm::dot(-sr.normal, sr.ray.getDirection()) > 0.0)
		return color * radianceScale;
	else
		return glm::vec3(0.0);
}

glm::vec3 Emissive::areaLightShade(const ShadeRec& sr)const
{
	if(glm::dot(-sr.normal, sr.ray.getDirection()) > 0.0)
		return color * radianceScale;
	else
		return glm::vec3(0.0);
}

glm::vec3 Emissive::getRadiance(const ShadeRec& sr)const
{
		return color * radianceScale;
}