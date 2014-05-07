#include "PointLight.h"
#include "ShadeRec.h"
#include "World.h"
#include "GeometricObject.h"
#include "DebugMemory.h"

PointLight::PointLight(bool useShadows, float intensity,const glm::vec3& color, const glm::vec3& position)
	:Light(useShadows,color,intensity),position(position)
{
}

PointLight::PointLight()
	:Light(true,glm::vec3(1.0f),1.0f),position()
{
}
glm::vec3 PointLight::getDirection(const ShadeRec& sr)
{
	glm::vec3 vec = position - sr.hitPoint;
	return glm::normalize(vec);
}

glm::vec3 PointLight::L(const ShadeRec& sr)
{
	return intensity * color;	
}

bool PointLight::inShadow(const Ray& ray,const ShadeRec& sr) const
{
	float t;
	int numObjects = sr.world.objects.size();
	float distance = glm::length(position - ray.getOrigin());

	for(int i=0;i<numObjects;i++)
	{
		if(sr.world.objects[i]->shadowHit(ray,t) && t < distance)
			return true;
	}
	return false;
}
