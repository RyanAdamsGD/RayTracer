#include "Material.h"
#include "ShadeRec.h"
#include "DebugMemory.h"

Material::~Material()
{
}

glm::vec3 Material::shade(const ShadeRec& sr)const
{
	return glm::vec3(0.0);
}

glm::vec3 Material::areaLightShade(const ShadeRec& sr)const
{
	return glm::vec3(0.0);
}

glm::vec3 Material::pathShade(const ShadeRec& sr)const
{
	return glm::vec3(0.0);
}

glm::vec3 Material::getRadiance(const ShadeRec& sr)const
{
	return glm::vec3(0.0);
}