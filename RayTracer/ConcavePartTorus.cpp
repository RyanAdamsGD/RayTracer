#include "ConcavePartTorus.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "HelperFunctions.h"

ConcavePartTorus::ConcavePartTorus(void)
{
	createBoundingbox();
}

ConcavePartTorus::~ConcavePartTorus(void)
{
}

ConcavePartTorus::ConcavePartTorus(float tubeRadius, float sweptRadius, float azimuthMin,
	float azimuthMax, float polarStart,float polarEnd)
	:sweptRadius(sweptRadius),azimuthMin(azimuthMin),azimuthMax(azimuthMax),
	polarEnd(polarEnd),polarStart(polarStart)
{
	sweptRadiusSQ = sweptRadius * sweptRadius;
	tubeRadiusSQ = tubeRadius * tubeRadius;
	bbox = createBoundingbox();
}

BoundingBox ConcavePartTorus::createBoundingbox()const
{
	float tubeRadius = sqrt(tubeRadiusSQ);
	glm::vec3 min(-sweptRadius - tubeRadius,-tubeRadius,-sweptRadius - tubeRadius);
	glm::vec3 max(sweptRadius + tubeRadius,tubeRadius,sweptRadius + tubeRadius);
	return BoundingBox(max,min);
}

BoundingBox ConcavePartTorus::getBoundingBox()const
{
	return bbox;
}

bool ConcavePartTorus::shadowHit(const Ray& ray, float& tmin) const
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

	glm::vec3 hitPoint = ray.getOrigin() + ray.getDirection() * t;
	float phi = atan2(hitPoint.y, hitPoint.z);
	if(phi < 0.0f)
		phi += TWO_PI;

	if(phi < (polarStart * PI_OVER_180) || phi > (polarEnd * PI_OVER_180))
		return false;
	
	float phi2 = atan2(hitPoint.x, hitPoint.z);
	if(phi2 < 0.0f)
		phi2 += TWO_PI; 

	if(phi < (azimuthMin * PI_OVER_180) || phi > (azimuthMax * PI_OVER_180))
		return false;

	tmin = t;

	return true;
}

bool ConcavePartTorus::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
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

	glm::vec3 hitPoint = ray.getOrigin() + ray.getDirection() * t;
	float phi = atan2(hitPoint.y, hitPoint.z);
	if(phi < 0.0f)
		phi += TWO_PI;

	if(phi < (polarStart * PI_OVER_180) || phi > (polarEnd * PI_OVER_180))
		return false;
	
	float phi2 = atan2(hitPoint.x, hitPoint.z);
	if(phi2 < 0.0f)
		phi2 += TWO_PI; 

	if(phi < (azimuthMin * PI_OVER_180) || phi > (azimuthMax * PI_OVER_180))
		return false;

	tmin = t;
	sr.localHitPoint = ray.getOrigin() + ray.getDirection() * t;
	sr.normal = computeNormals(sr.localHitPoint);

	return true;
}

glm::vec3 ConcavePartTorus::computeNormals(const glm::vec3& point)const
{
	float paramSquared = sweptRadiusSQ + tubeRadiusSQ;
	float sumSquared = glm::dot(point,point) - paramSquared;

	glm::vec3 normal(4.0f * point.x * sumSquared,
		4.0f * point.y * (sumSquared + 2.0f * sweptRadiusSQ), 4.0f * point.z * sumSquared);
	return -glm::normalize(normal);
}

void ConcavePartTorus::setTubeRadius(float value)
{
	tubeRadiusSQ = value * value;
	bbox = createBoundingbox();
}

void ConcavePartTorus::setSweptRadius(float value)
{
	sweptRadius = fabs(value);
	sweptRadiusSQ = value * value;
	bbox = createBoundingbox();
}