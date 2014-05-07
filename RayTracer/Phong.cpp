#include "Phong.h"
#include "ShadeRec.h"
#include "Lambert.h"
#include "GlossySpecular.h"
#include "World.h"
#include "Light.h"
#include "DebugMemory.h"

Phong::Phong()
	:Material(),ambientBrdf(new Lambert),diffuseBrdf(new Lambert),specularBrdf(new GlossySpecular)
{
}

Phong::~Phong()
{
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

	if(specularBrdf != NULL)
	{
		delete specularBrdf;
		specularBrdf = NULL;
	}
}

void Phong::setKAmbient(float k)
{
	ambientBrdf->setReflectionCoefficient(k);
}

void Phong::setKDiffuse(float k)
{
	diffuseBrdf->setReflectionCoefficient(k);
}

void Phong::setKSpecular(float k)
{
	specularBrdf->setReflectionCoefficient(k);
}

void Phong::setExponent(float exp)
{
	specularBrdf->setExponent(exp);
}

void Phong::setColor(const glm::vec3& color)
{
	diffuseBrdf->setColor(color);
	ambientBrdf->setColor(color);
}

glm::vec3 Phong::shade(const ShadeRec& sr)const
{
	glm::vec3 incoming(-sr.ray.getDirection());
	glm::vec3 ambient = sr.world.getAmbient()->L(sr);
	glm::vec3 color = ambientBrdf->rho(sr,incoming);
	color.x *= ambient.x;
	color.y *= ambient.y;
	color.z *= ambient.z;

	int numLights = sr.world.lights.size();

	for(int i=0;i<numLights;i++)
	{
		glm::vec3 reflected(sr.world.lights[i]->getDirection(sr));
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
				glm::vec3 gainedColor(diffuseBrdf->f(sr,incoming,reflected) + specularBrdf->f(sr,incoming,reflected));
				glm::vec3 lightColor = sr.world.lights[i]->L(sr) * nDotI;
				lightColor.x *= gainedColor.x;
				lightColor.y *= gainedColor.y;
				lightColor.z *= gainedColor.z;
				color += lightColor;
			}
		}
	}
	return color;
}

glm::vec3 Phong::areaLightShade(const ShadeRec& sr)const
{
	glm::vec3 incoming(-sr.ray.getDirection());
	glm::vec3 ambient = sr.world.getAmbient()->L(sr);
	glm::vec3 color = ambientBrdf->rho(sr,incoming);
	color.x *= ambient.x;
	color.y *= ambient.y;
	color.z *= ambient.z;

	int numLights = sr.world.lights.size();

	for(int i=0;i<numLights;i++)
	{
		glm::vec3 reflected(sr.world.lights[i]->getDirection(sr));
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
				glm::vec3 gainedColor(diffuseBrdf->f(sr,incoming,reflected) + specularBrdf->f(sr,incoming,reflected));
				glm::vec3 lightColor = sr.world.lights[i]->L(sr) * nDotI;
				lightColor.x *= gainedColor.x;
				lightColor.y *= gainedColor.y;
				lightColor.z *= gainedColor.z;
				color += lightColor;
			}
		}
	}
	return color;
}