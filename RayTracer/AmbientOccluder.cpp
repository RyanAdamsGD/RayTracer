#include "AmbientOccluder.h"
#include "Sampler.h"
#include "ShadeRec.h"
#include "World.h"
#include "GeometricObject.h"
#include "DebugMemory.h"

AmbientOccluder::AmbientOccluder(bool useShadows,const glm::vec3& color, float intensity,
		Sampler* sampler,const glm::vec3& minAmount)
	:Light(useShadows,color,intensity),sampler(sampler),minAmount(minAmount)
{
	if(sampler != NULL)
		sampler->mapSamplesToHemisphere(1);
}


AmbientOccluder::~AmbientOccluder(void)
{
	if(sampler != NULL)
	{
		delete sampler;
		sampler = NULL;
	}
}

glm::vec3 AmbientOccluder::L(const ShadeRec& sr)
{
	w = sr.normal;
	//jitter up vector in case its vertical
	v = glm::cross(w,glm::vec3(0.0072f,1.0f,0.0034f));
	v = glm::normalize(v);
	u = glm::cross(v,w);

	Ray shadowRay(sr.hitPoint,getDirection(sr));
	if(useShadows && inShadow(shadowRay,sr))
		return minAmount * color * intensity;
	else
		return intensity * color;
}

bool AmbientOccluder::inShadow(const Ray& ray,const ShadeRec& sr)const
{
	float t;
	int numObjects = sr.world.objects.size();

	for(int i=0;i<numObjects;i++)
	{
		if(sr.world.objects[i]->shadowHit(ray,t))
			return true;
	}
	return false;
}

glm::vec3 AmbientOccluder::getDirection(const ShadeRec& sr)
{
	glm::vec3 point = sampler->sampleHemisphere();
	return point.x * u + point.y * v + point.z * w;
}

void AmbientOccluder::setSampler(Sampler* sampler)
{
	if(this->sampler != NULL)
	{
		delete this->sampler;
		this->sampler = NULL;
	}

	this->sampler = sampler;
	this->sampler->mapSamplesToHemisphere(1);
}