#include "Dielectric.h"
#include "FresnelReflector.h"
#include "FresnelTransmitter.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "World.h"
#include "Tracer.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

#define kEpsilon 0.0000001f

Dielectric::Dielectric(void)
	:Phong(),fresnelBrdf(new FresnelReflector), fresnelBtdf(new FresnelTransmitter)
{
}


Dielectric::~Dielectric(void)
{
	if(fresnelBrdf != NULL)
	{
		delete fresnelBrdf;
		fresnelBrdf = NULL;
	}

	if(fresnelBtdf != NULL)
	{
		delete fresnelBtdf;
		fresnelBtdf = NULL;
	}
}

glm::vec3 Dielectric::shade(const ShadeRec& sr)const
{
	glm::vec3 L;
	//glm::vec3 L = Phong::shade(sr);
	glm::vec3 reflected;
	glm::vec3 incoming(-sr.ray.getDirection());
	glm::vec3 fr = fresnelBrdf->sampleF(sr,incoming,reflected);
	Ray reflectedRay(sr.hitPoint,reflected);
	float t = 0.0f;
	glm::vec3 Lr, Lt;
	float nDotR = glm::dot(sr.normal,reflected);

	if(fresnelBtdf->tir(sr))
	{
		if(nDotR < 0.0)
		{
			//reflected ray is inside
			Lr = sr.world.getTracer()->traceRay(reflectedRay,t,sr.depth + 1);
			glm::vec3 colorFilter = glm::pow(colorFilterIn,glm::vec3(t));
			L.x += colorFilter.x * Lr.x;
			L.y += colorFilter.y * Lr.y;
			L.z += colorFilter.z * Lr.z;
		}
		else
		{
			//reflected ray is outside
			Lr = sr.world.getTracer()->traceRay(reflectedRay,t,sr.depth + 1);
			glm::vec3 colorFilter = glm::pow(colorFilterOut,glm::vec3(t));			
			L.x += colorFilter.x * Lr.x;
			L.y += colorFilter.y * Lr.y;
			L.z += colorFilter.z * Lr.z;
		}
	}
	else
	{
		//no total internal reflection
		glm::vec3 transmitted;
		glm::vec3 ft = fresnelBtdf->sampleF(sr,incoming,transmitted);
		Ray transmittedRay(sr.hitPoint,transmitted);
		float nDotT = glm::dot(sr.normal,transmitted);

		if(nDotT > 0.0)
		{
			//reflected ray is inside
			Lr = sr.world.getTracer()->traceRay(reflectedRay,t,sr.depth +1) * fabs(nDotR);
			Lr.x *= fr.x;
			Lr.y *= fr.y;
			Lr.z *= fr.z;

			glm::vec3 colorFilterR = glm::pow(colorFilterIn,glm::vec3(t));
			L.x += colorFilterR.x * Lr.x;
			L.y += colorFilterR.y * Lr.y;
			L.z += colorFilterR.z * Lr.z;

			//transmitted ray is outside
			Lt = sr.world.getTracer()->traceRay(transmittedRay,t,sr.depth +1) * fabs(nDotT);
			Lt.x *= ft.x;
			Lt.y *= ft.y;
			Lt.z *= ft.z;

			glm::vec3 colorFilterT = glm::pow(colorFilterOut, glm::vec3(t));
			L.x += colorFilterT.x * Lt.x;
			L.y += colorFilterT.y * Lt.y;
			L.z += colorFilterT.z * Lt.z;
		}
		else
		{
			//reflected ray is outisde
			Lr = sr.world.getTracer()->traceRay(reflectedRay,t,sr.depth +1) * fabs(nDotR);
			Lr.x *= fr.x;
			Lr.y *= fr.y;
			Lr.z *= fr.z;

			glm::vec3 colorFilterR = glm::pow(colorFilterOut,glm::vec3(t));
			colorFilterR.x *= Lr.x;
			colorFilterR.y *= Lr.y;
			colorFilterR.z *= Lr.z;
			L += colorFilterR;

			//transmitted ray is inside
			Lt = sr.world.getTracer()->traceRay(transmittedRay,t,sr.depth +1) * fabs(nDotT);
			Lt.x *= ft.x;
			Lt.y *= ft.y;
			Lt.z *= ft.z;

			glm::vec3 colorFilterT = glm::pow(colorFilterIn,glm::vec3(t));
			colorFilterT.x *= Lt.x;
			colorFilterT.y *= Lt.y;
			colorFilterT.z *= Lt.z;
			L += colorFilterT;
		}
	}

	return L;
}


void Dielectric::setEtaIn(float value)
{
	fresnelBrdf->setEtaIn(value);
	fresnelBtdf->setEtaIn(value);
}

void Dielectric::setEtaOut(float value)
{
	fresnelBrdf->setEtaOut(value);
	fresnelBtdf->setEtaOut(value);
}

void Dielectric::setColorFilterIn(const glm::vec3& value) 
{
	colorFilterIn=value;
	colorFilterIn.x = clamp(colorFilterIn.x,kEpsilon,1.0f - kEpsilon);
	colorFilterIn.y = clamp(colorFilterIn.y,kEpsilon,1.0f - kEpsilon);
	colorFilterIn.z = clamp(colorFilterIn.z,kEpsilon,1.0f - kEpsilon);
}

void Dielectric::setColorFilterOut(const glm::vec3& value) 
{
	colorFilterOut=value;
	colorFilterOut.x = clamp(colorFilterOut.x,kEpsilon,1.0f - kEpsilon);
	colorFilterOut.y = clamp(colorFilterOut.y,kEpsilon,1.0f - kEpsilon);
	colorFilterOut.z = clamp(colorFilterOut.z,kEpsilon,1.0f - kEpsilon);
}