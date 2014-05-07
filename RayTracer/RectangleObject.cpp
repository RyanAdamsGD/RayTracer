#include "RectangleObject.h"
#include "Sampler.h"
#include "Ray.h"
#include "ShadeRec.h"

RectangleObject::RectangleObject(const glm::vec3& cornerPoint,const glm::vec3& egdgeA,
		const glm::vec3& edgeB,const glm::vec3& normal)
		:cornerPoint(cornerPoint),edgeB(edgeB), edgeA(edgeA),normal(normal)
{
	float length = edgeA.length();
	edgeALenSq = length * length;
	length = edgeB.length();
	edgeBLenSq = length * length;

	invArea = 1.0f / (edgeA.length() * edgeB.length());

}

RectangleObject::RectangleObject(const glm::vec3& cornerPoint,const glm::vec3& egdgeA,
		const glm::vec3& edgeB)
		:cornerPoint(cornerPoint),edgeB(edgeB), edgeA(edgeA)
{
	float length = edgeA.length();
	edgeALenSq = length * length;
	length = edgeB.length();
	edgeBLenSq = length * length;

	normal = glm::cross(edgeA, edgeB);
	normal = glm::normalize(normal);
	invArea = 1.0f / (edgeA.length() * edgeB.length());

}

BoundingBox RectangleObject::getBoundingBox()const
{
	glm::vec3 p0(kHugeValue),p1(-kHugeValue);
	glm::vec3 v0 = cornerPoint + edgeA;
	glm::vec3 v1 = cornerPoint + edgeB;

	v0.x<v1.x? p0.x = v0.x , p1.x = v1.x : p0.x = v1.x , p1.x = v1.x;
	v0.y<v1.y? p0.y = v0.y , p1.y = v1.y : p0.y = v1.y , p1.y = v1.y;
	v0.z<v1.z? p0.z = v0.z , p1.z = v1.z : p0.z = v1.z , p1.z = v1.z;
	p0.x = p0.x<cornerPoint.x? p0.x : cornerPoint.x;
	p0.y = p0.y<cornerPoint.y? p0.y : cornerPoint.y;
	p0.z = p0.z<cornerPoint.z? p0.z : cornerPoint.z;

	p1.x = p1.x>cornerPoint.x? p1.x : cornerPoint.x;
	p1.y = p1.y>cornerPoint.y? p1.y : cornerPoint.y;
	p1.z = p1.z>cornerPoint.z? p1.z : cornerPoint.z;

	p0 -= glm::vec3(KEpsilon);
	p1 += glm::vec3(KEpsilon);

	return BoundingBox(p1,p0);
}

bool RectangleObject::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	float t = glm::dot(cornerPoint - ray.getOrigin(), normal) / glm::dot(ray.getDirection(), normal); 
	
	if (t <= kEpsilon)
		return false;
			
	glm::vec3 point = ray.getOrigin() + t * ray.getDirection();
	glm::vec3 direction = point - cornerPoint;
	
	float ddota = glm::dot(direction, edgeA);
	
	if (ddota < 0.0f || ddota > edgeALenSq)
		return false;
		
	float ddotb = glm::dot(direction, edgeB);
	
	if (ddotb < 0.0f || ddotb > edgeBLenSq)
		return false;
		
	tmin = t;
	sr.normal = normal;
	sr.localHitPoint = point;
	
	return true;
}

bool RectangleObject::shadowHit(const Ray& ray, float& tmin) const
{
	float t = glm::dot(cornerPoint - ray.getOrigin(), normal) / glm::dot(ray.getDirection(), normal); 
	
	if (t <= kEpsilon)
		return false;
			
	glm::vec3 point = ray.getOrigin() + t * ray.getDirection();
	glm::vec3 direction = point - cornerPoint;
	
	float ddota = glm::dot(direction, edgeA);
	
	if (ddota < 0.0f || ddota > edgeALenSq)
		return false;
		
	float ddotb = glm::dot(direction, edgeB);
	
	if (ddotb < 0.0f || ddotb > edgeBLenSq)
		return false;
		
	tmin = t;
	
	return true;
}

glm::vec3 RectangleObject::sample(void)
{
	glm::vec2 samplePoint = sampler->sampleUnitSquare();
	return cornerPoint + samplePoint.x * edgeA + samplePoint.y * edgeB;
}

float RectangleObject::pdf(ShadeRec& sr)
{
	return invArea;
}

glm::vec3 RectangleObject::getNormal(const glm::vec3& point) const
{
	return normal;
}