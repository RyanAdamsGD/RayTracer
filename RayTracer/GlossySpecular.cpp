#include "GlossySpecular.h"
#include "Sampler.h"
#include "DebugMemory.h"

GlossySpecular::GlossySpecular(Sampler* sampler, const glm::vec3& normal,const glm::vec3& color,float phongExponent, float coeffiecientOfSpecularReflection)
	:BRDF(sampler,normal),color(color),phongExponent(phongExponent),coeffiecientOfSpecularReflection(coeffiecientOfSpecularReflection)
{
}

GlossySpecular::GlossySpecular()
	:BRDF(),color(1.0f),phongExponent(10),coeffiecientOfSpecularReflection(1.0)
{
}

glm::vec3 GlossySpecular::f(const ShadeRec& sr, const glm::vec3& incoming, const glm::vec3& reflected)const
{
	glm::vec3 specularColor;
	float nDotI = glm::dot(sr.normal, reflected);
	glm::vec3 reflect(-reflected + 2.0f * sr.normal * nDotI);
	float rDotWo = glm::dot(reflect,incoming);

	if(rDotWo > 0.0f)
		specularColor = coeffiecientOfSpecularReflection * pow(rDotWo,phongExponent) * color;
	
	return specularColor;
}

glm::vec3 GlossySpecular::sampleF(const ShadeRec& sr,const glm::vec3& incoming,glm::vec3& reflected, float& pdf)const
{
	float nDotR = glm::dot(sr.normal,incoming);
	glm::vec3 r = -incoming + 2.0f * sr.normal * nDotR;

	glm::vec3 w = r;
	glm::vec3 u = glm::cross(glm::vec3(0.00434,1,0.00764),w);
	u = glm::normalize(u);
	glm::vec3 v = glm::cross(u,v);

	glm::vec3 samplePoint = sampler->sampleHemisphere();
	reflected = samplePoint.x * u + samplePoint.y * v + samplePoint.z * w;

	if(glm::dot(sr.normal,samplePoint) < 0.0f)
		reflected = -samplePoint.x * u - samplePoint.y * v - samplePoint.z * w;

	float phongLobe = pow(glm::dot(r, reflected),phongExponent);
	pdf = phongLobe * glm::dot(sr.normal,reflected);

	return coeffiecientOfSpecularReflection * color * phongLobe;
}

glm::vec3 GlossySpecular::rho(const ShadeRec& sr, const glm::vec3& incoming)const
{
	return glm::vec3(0.0f);
}