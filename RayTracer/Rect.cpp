#include "Rect.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "glm\gtx\norm.hpp"

Rect::Rect()
	:corner(-1,0,-1),v0(0,0,2),v1(2,0,0),aLenSquared(4.0f),bLenSquared(4.0f)
{
}

Rect::Rect(const glm::vec3& corner, const glm::vec3& edge1, const glm::vec3& edge2)
	:corner(corner),v0(edge1),v1(edge2)
{
	normal = glm::cross(edge1,edge2);
	normal = glm::normalize(normal);
	aLenSquared = glm::length2(edge1);
	bLenSquared = glm::length2(edge2);
}

Rect::Rect(const glm::vec3& corner, const glm::vec3& edge1, const glm::vec3& edge2,const glm::vec3& normal)
	:corner(corner),v0(edge1),v1(edge2),normal(glm::normalize(normal))
{
	aLenSquared = glm::length2(edge1);
	bLenSquared = glm::length2(edge2);
}

BoundingBox Rect::getBoundingBox()const
{
	glm::vec3 p0(kHugeValue),p1(-kHugeValue);

	p0.x = corner.x + v0.x + v1.x;
	p0.y = corner.y + v0.y + v1.y;
	p0.z = corner.z + v0.z + v1.z;
	p1.x = corner.x + v0.x + v1.x;
	p1.y = corner.y + v0.y + v1.y;
	p1.z = corner.z + v0.z + v1.z;

	p0.x = p0.x<corner.x? p0.x : corner.x;
	p0.y = p0.y<corner.y? p0.y : corner.y;
	p0.z = p0.z<corner.z? p0.z : corner.z;

	p1.x = p1.x>corner.x? p1.x : corner.x;
	p1.y = p1.y>corner.y? p1.y : corner.y;
	p1.z = p1.z>corner.z? p1.z : corner.z;

	p0 -= glm::vec3(KEpsilon);
	p1 += glm::vec3(KEpsilon);

	return BoundingBox(p1,p0);
}

bool Rect::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	float t = glm::dot((corner - ray.getOrigin()),normal) / glm::dot(ray.getDirection(),normal);

	if(t<=KEpsilon)
		return false;

	glm::vec3 point = ray.getOrigin() + t * ray.getDirection();
	glm::vec3 d = point - corner;

	float dDota = glm::dot(d, v0);
	if(dDota<0.0 || dDota > aLenSquared)
		return false;

	float dDotb = glm::dot(d, v1);
	if(dDotb<0.0 || dDotb > bLenSquared)
		return false;

	tmin = t;
	sr.normal = normal;
	sr.localHitPoint = point;

	return true;
}

bool Rect::shadowHit(const Ray& ray, float& tmin) const
{
	if(!castsShadows)
		return false;

	float t = glm::dot((corner - ray.getOrigin()),normal) / glm::dot(ray.getDirection(),normal);

	if(t<=KEpsilon)
		return false;

	glm::vec3 point = ray.getOrigin() + t * ray.getDirection();
	glm::vec3 d = point - v0;

	float dDota = glm::dot(d, v0);
	if(dDota<0.0 || dDota > aLenSquared)
		return false;

	float dDotb = glm::dot(d, v1);
	if(dDotb<0.0f || dDotb > bLenSquared)
		return false;

	tmin = t;

	return true;
}
