#include "SVLambertian.h"
#include "Texture.h"
#include "TypeDefs.h"
#include "Sampler.h"
#include "DebugMemory.h"

SVLambertian::SVLambertian(void)
	:BRDF(),texture(NULL)
{
}

SVLambertian::~SVLambertian(void)
{
}

glm::vec3 SVLambertian::f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& reflected)const
{
	return kd * texture->getColor(sr) * INV_PI;
}

glm::vec3 SVLambertian::rho(const ShadeRec& sr, const glm::vec3& incoming)const
{
	return kd * texture->getColor(sr);
}

glm::vec3 SVLambertian::sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected, float& pdf)const
{
	glm::vec3 w = sr.normal;
	glm::vec3 v = glm::cross(glm::vec3(0.0034f,1.0f,0.0071f),w);
	v = glm::normalize(v);
	glm::vec3 u = glm::cross(v,w);

	glm::vec3 samplePoint = sampler->sampleHemisphere();
	reflected = samplePoint.x * u + samplePoint.y * v + samplePoint.z * w;
	reflected = glm::normalize(reflected);

	pdf = glm::dot(sr.normal,reflected) * INV_PI;

	return kd * texture->getColor(sr) * INV_PI;
}

void SVLambertian::setTexture(Texture* value)
{
	if(texture != NULL)
	{
		delete texture;
		texture = NULL;
	}

	texture=value;
}