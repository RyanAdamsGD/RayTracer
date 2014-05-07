#include "Torus.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "HelperFunctions.h"

Torus::Torus(void)
{
	createBoundingbox();
}

Torus::~Torus(void)
{
}

Torus::Torus(float tubeRadius, float sweptRadius)
	:sweptRadius(sweptRadius)
{
	sweptRadiusSQ = sweptRadius * sweptRadius;
	tubeRadiusSQ = tubeRadius * tubeRadius;
	bbox = createBoundingbox();
}

BoundingBox Torus::createBoundingbox()const
{
	float tubeRadius = sqrt(tubeRadiusSQ);
	glm::vec3 min(-sweptRadius - tubeRadius,-tubeRadius,-sweptRadius - tubeRadius);
	glm::vec3 max(sweptRadius + tubeRadius,tubeRadius,sweptRadius + tubeRadius);
	return BoundingBox(max,min);
}

BoundingBox Torus::getBoundingBox()const
{
	return bbox;
}

bool Torus::shadowHit(const Ray& ray, float& tmin) const
{
	if(!castsShadows)
		return false;

	if(!bbox.hit(ray))
		return false;

	glm::vec3 origin = ray.getOrigin();
	glm::vec3 dir = ray.getDirection();

	float coefs[5];
	float roots[4];

	//define coefficients
	float sumDSquared = glm::dot(dir,dir);
	float e = glm::dot(origin,origin) - sweptRadiusSQ - tubeRadiusSQ;
	float f = glm::dot(origin,dir);
	float fourASquared = 4.0f * sweptRadiusSQ;

	coefs[0] = e * e - fourASquared * (tubeRadiusSQ - origin.y * origin.y);
	coefs[1] = 4.0f * f * e + 2.0f * fourASquared * origin.y * dir.y;
	coefs[2] = 2.0f * sumDSquared * e + 4.0f * f * f + fourASquared * dir.y * dir.y;
	coefs[3] = 4.0f * sumDSquared * f;
	coefs[4] = sumDSquared * sumDSquared;

	int numRealRoots = solveQuartic(coefs,roots);

	bool intersected = false;
	float t = kHugeValue;

	if(numRealRoots == 0)
		return false;

	for(int i=0;i<numRealRoots;i++)
		if(roots[i] > KEpsilon)
		{
			intersected = true;
			if(roots[i] < t)
				t = roots[i];
		}

	if(!intersected)
		return false;

	tmin = t;

	return true;
}

bool Torus::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	if(!bbox.hit(ray))
		return false;

	glm::vec3 origin = ray.getOrigin();
	glm::vec3 dir = ray.getDirection();

	float coefs[5];
	float roots[4];

	//define coefficients
	float sumDSquared = glm::dot(dir,dir);
	float e = glm::dot(origin,origin) - sweptRadiusSQ - tubeRadiusSQ;
	float f = glm::dot(origin,dir);
	float fourASquared = 4.0f * sweptRadiusSQ;

	coefs[0] = e * e - fourASquared * (tubeRadiusSQ - origin.y * origin.y);
	coefs[1] = 4.0f * f * e + 2.0f * fourASquared * origin.y * dir.y;
	coefs[2] = 2.0f * sumDSquared * e + 4.0f * f * f + fourASquared * dir.y * dir.y;
	coefs[3] = 4.0f * sumDSquared * f;
	coefs[4] = sumDSquared * sumDSquared;

	int numRealRoots = solveQuartic(coefs,roots);

	bool intersected = false;
	float t = kHugeValue;

	if(numRealRoots == 0)
		return false;

	for(int i=0;i<numRealRoots;i++)
		if(roots[i] > KEpsilon)
		{
			intersected = true;
			if(roots[i] < t)
				t = roots[i];
		}

	if(!intersected)
		return false;

	tmin = t;
	sr.localHitPoint = ray.getOrigin() + ray.getDirection() * t;
	sr.normal = computeNormals(sr.localHitPoint);

	return true;
}

glm::vec3 Torus::computeNormals(const glm::vec3& point)const
{
	float paramSquared = sweptRadiusSQ + tubeRadiusSQ;
	float sumSquared = glm::dot(point,point) - paramSquared;

	glm::vec3 normal(4.0f * point.x * sumSquared,
		4.0f * point.y * (sumSquared + 2.0f * sweptRadiusSQ), 4.0f * point.z * sumSquared);
	return glm::normalize(normal);
}

void Torus::setTubeRadius(float value)
{
	tubeRadiusSQ = value * value;
	bbox = createBoundingbox();
}

void Torus::setSweptRadius(float value)
{
	sweptRadius = fabs(value);
	sweptRadiusSQ = value * value;
	bbox = createBoundingbox();
}