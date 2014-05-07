#include "EnvironmentLight.h"
#include "Sampler.h"
#include "ShadeRec.h"
#include "Material.h"
#include "World.h"
#include "GeometricObject.h"

EnvironmentLight::EnvironmentLight(bool useShadows,const glm::vec3& color,const double& intensity)
	:Light(useShadows,color,intensity)
{
}


EnvironmentLight::~EnvironmentLight(void)
{
	if(sampler != NULL)
	{
		delete sampler;
		sampler = NULL;
	}

	if(material != NULL)
	{
		delete material;
		material = NULL;
	}
}


void EnvironmentLight::setSampler(Sampler* sampler)
{
	if(this->sampler != NULL)
	{
		delete this->sampler;
		this->sampler = NULL;
	}

	this->sampler = sampler;
	this->sampler->mapSamplesToHemisphere(1);
}

glm::vec3 EnvironmentLight::getDirection(ShadeRec& sr)
{
	w = sr.normal;
	v = glm::cross(glm::vec3(0.0034,1,0.0071),w);
	v = glm::normalize(v);
	u = glm::cross(v,w);
	glm::vec3 samplePoint = sampler->sampleHemisphere();
	incoming = samplePoint.x * u + samplePoint.y * v + samplePoint.z * w;

	return incoming;
}

glm::vec3 EnvironmentLight::L(ShadeRec& sr)
{
	return material->getRadiance(sr);
}

bool EnvironmentLight::inShadow(const Ray& ray, const ShadeRec& sr) const
{
	double t;
	int numObjects = sr.world.objects.size();

	for(int i=0;i<numObjects;i++)
	{
		if(sr.world.objects[i]->shadowHit(ray,t))
			return true;
	}
	return false;
}

double EnvironmentLight::pdf(const ShadeRec& sr) const
{
	return glm::dot(sr.normal,incoming) * INV_PI;
}