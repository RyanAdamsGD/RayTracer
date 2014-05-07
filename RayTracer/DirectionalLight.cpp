#include "DirectionalLight.h"
#include "ShadeRec.h"
#include "World.h"
#include "GeometricObject.h"
#include "DebugMemory.h"

DirectionalLight::DirectionalLight(bool useShadows, float intensity,const glm::vec3 color,const glm::vec3& direction)
	:Light(useShadows,color,intensity)
{
	this->direction = glm::normalize(direction);
}

DirectionalLight::DirectionalLight()
	:Light(true,glm::vec3(1.0f),1.0f)
{
}

glm::vec3 DirectionalLight::getDirection(const ShadeRec& sr)
{
	return direction;
}

glm::vec3 DirectionalLight::L(const ShadeRec& sr)
{
	return intensity * color;	
}

bool DirectionalLight::inShadow(const Ray& ray,const ShadeRec& sr)const
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