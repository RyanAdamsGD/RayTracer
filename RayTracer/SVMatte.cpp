#include "SVMatte.h"
#include "SVLambertian.h"
#include "ShadeRec.h"
#include "World.h"
#include "Light.h"
#include "Tracer.h"
#include "DebugMemory.h"
#include "Texture.h"

SVMatte::SVMatte(void)
	:Material(),ambientBrdf(new SVLambertian),diffuseBrdf(new SVLambertian)
{
}

void SVMatte::setKAmbient(float k)
{
	ambientBrdf->setReflectionCoefficient(k);
}

void SVMatte::setKDiffuse(float k)
{
	diffuseBrdf->setReflectionCoefficient(k);
}

void SVMatte::setTexture(Texture* texture)
{
	diffuseBrdf->setTexture(texture);
	ambientBrdf->setTexture(texture);
}

glm::vec3 SVMatte::shade(const ShadeRec& sr)const
{
	glm::vec3 incoming = -sr.ray.getDirection();
	glm::vec3 ambientColor = ambientBrdf->rho(sr,incoming);
	glm::vec3 color = sr.world.getAmbient()->L(sr);
	color.x *= ambientColor.x;
	color.y *= ambientColor.y;
	color.z *= ambientColor.z;
	int numLights = sr.world.lights.size();

	for(int i=0;i<numLights;i++)
	{
		glm::vec3 reflected = sr.world.lights[i]->getDirection(sr);
		float normalDotReflected = glm::dot(sr.normal, reflected);

		if(normalDotReflected > 0.0)
		{
			bool inShadow = false;
			if(hasShadows && sr.world.lights[i]->castsShadows())
			{
				Ray shadowRay(sr.hitPoint,reflected);
				inShadow = sr.world.lights[i]->inShadow(shadowRay,sr);
			}

			if(!inShadow)
			{
				glm::vec3 diffuseColor = diffuseBrdf->f(sr,incoming,reflected);
				glm::vec3 lightColor = sr.world.lights[i]->L(sr) * normalDotReflected;
				lightColor.x *= diffuseColor.x;
				lightColor.y *= diffuseColor.y;
				lightColor.z *= diffuseColor.z;
				color += lightColor;
			}
		}
	}
	return color;
}

glm::vec3 SVMatte::areaLightShade(const ShadeRec& sr)const
{
	glm::vec3 incoming = -sr.ray.getDirection();
	glm::vec3 ambientColor = ambientBrdf->rho(sr,incoming);
	glm::vec3 color = sr.world.getAmbient()->L(sr);
	color.x *= ambientColor.x;
	color.y *= ambientColor.y;
	color.z *= ambientColor.z;
	int numLights = sr.world.lights.size();

	for(int i=0;i<numLights;i++)
	{
		glm::vec3 reflected = sr.world.lights[i]->getDirection(sr);
		float nDotI = glm::dot(sr.normal,reflected);

		if(nDotI > 0.0)
		{
			bool inShadow = false;

			if(hasShadows && sr.world.lights[i]->castsShadows())
			{
				Ray shadowRay(sr.hitPoint,reflected);
				inShadow = sr.world.lights[i]->inShadow(shadowRay,sr);
			}

			if(!inShadow)
			{
				glm::vec3 diffuseColor = diffuseBrdf->f(sr,incoming,reflected);
				glm::vec3 lightColor = sr.world.lights[i]->L(sr) * sr.world.lights[i]->G(sr) * nDotI / sr.world.lights[i]->pdf(sr);
				lightColor.x *= diffuseColor.x;
				lightColor.y *= diffuseColor.y;
				lightColor.z *= diffuseColor.z;
				color += lightColor;
			}
		}
	}
	return color;
}

glm::vec3 SVMatte::pathShade(const ShadeRec& sr)const
{
	glm::vec3 incoming = -sr.ray.getDirection();
	glm::vec3 reflected;
	float pdf;
	glm::vec3 fr = diffuseBrdf->sampleF(sr,incoming,reflected,pdf);
	Ray reflectedRay(sr.hitPoint,reflected);

	glm::vec3 reflectedColor = sr.world.getTracer()->traceRay(reflectedRay,sr.depth + 1);
	fr.x *= reflectedColor.x;
	fr.y *= reflectedColor.y;
	fr.z *= reflectedColor.z;
	return fr  * glm::dot(sr.normal,reflected) / pdf;
}

SVMatte::~SVMatte(void)
{
	delete ambientBrdf->getTexture();

	if(ambientBrdf != NULL)
	{
		delete ambientBrdf;
		ambientBrdf = NULL;
	}
	if(diffuseBrdf != NULL)
	{
		delete diffuseBrdf;
		diffuseBrdf = NULL;
	}
}