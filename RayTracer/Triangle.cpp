#include "Triangle.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "HelperFunctions.h"

Triangle::Triangle(const glm::vec3& v0,const glm::vec3& v1,const glm::vec3& v2)
	:v0(v0),v1(v1),v2(v2)
{
	normal = glm::cross(v1-v0,v2-v0);
	normal = glm::normalize(normal);
}

Triangle::Triangle(const glm::vec3& v0,const glm::vec3& v1,const glm::vec3& v2,const glm::vec3& normal)
	:v0(v0),v1(v1),v2(v2),normal(normal)
{
}

bool Triangle::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	glm::vec3 origin = ray.getOrigin(), direction = ray.getDirection();
	float a = v0.x - v1.x, b = v0.x - v2.x, c = direction.x, d = v0.x - origin.x;
	float e = v0.y - v1.y, f = v0.y - v2.y, g = direction.y, h = v0.y - origin.y;
	float i = v0.z - v1.z, j = v0.z - v2.z, k = direction.z, l = v0.z - origin.z;

	float m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	float q = g * i - e * k, s = e * j - f * i;

	float invDenom = 1.0f / (a * m + b * q + c * s);

	float e1 = d * m - b * n - c * p;
	float beta = e1 * invDenom;

	if(beta < 0.0f)
		return false;

	float r = e * l - h * i;
	float e2 = a * n + d * q + c * r;
	float gamma = e2 * invDenom;

	if(gamma < 0.0f)
		return false;

	if(beta + gamma > 1.0f)
		return false;

	float e3 = a * p - b * r + d * s;
	float t = e3 * invDenom;

	if(t < KEpsilon)
		return false;

	tmin = t;
	sr.normal = normal;
	sr.localHitPoint = origin + t * direction;

	return true;
}

bool Triangle::shadowHit(const Ray& ray, float& tmin) const
{
	if(!castsShadows)
		return false;

	glm::vec3 origin = ray.getOrigin(), direction = ray.getDirection();
	float a = v0.x - v1.x, b = v0.x - v2.x, c = direction.x, d = v0.x - origin.x;
	float e = v0.y - v1.y, f = v0.y - v2.y, g = direction.y, h = v0.y - origin.y;
	float i = v0.z - v1.z, j = v0.z - v2.z, k = direction.z, l = v0.z - origin.z;

	float m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	float q = g * i - e * k, s = e * j - f * i;

	float invDenom = 1.0f / (a * m + b * q + c * s);

	float e1 = d * m - b * n - c * p;
	float beta = e1 * invDenom;

	if(beta < 0.0f)
		return false;

	float r = e * l - h * i;
	float e2 = a * n + d * q + c * r;
	float gamma = e2 * invDenom;

	if(gamma < 0.0f)
		return false;

	if(beta + gamma > 1.0f)
		return false;

	float e3 = a * p - b * r + d * s;
	float t = e3 * invDenom;

	if(t < KEpsilon)
		return false;

	tmin = t;
	return true;
}

BoundingBox Triangle::getBoundingBox()const
{
	float delta = 0.000001f; 

	glm::vec3 minimum(min(min(v0.x, v1.x), v2.x) - delta, min(min(v0.y, v1.y), v2.y) - delta, 
		min(min(v0.z, v1.z), v2.z) - delta);
	glm::vec3 maximum(max(max(v0.x, v1.x), v2.x) + delta, max(max(v0.y, v1.y), v2.y) + delta, max(max(v0.z, v1.z), v2.z) + delta);

	return BoundingBox(maximum,minimum);
}