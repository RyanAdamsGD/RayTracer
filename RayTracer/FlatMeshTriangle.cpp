#include "FlatMeshTriangle.h"
#include "Mesh.h"
#include "Ray.h"
#include "ShadeRec.h"

FlatMeshTriangle::FlatMeshTriangle(void)
{
}


bool FlatMeshTriangle::hit(const Ray& ray, float& tmin, ShadeRec& sr)const
{
	glm::vec3 v0 = mesh->verts[index0], v1 = mesh->verts[index1], v2 = mesh->verts[index2];

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
	sr.localHitPoint = ray.getOrigin() + ray.getDirection() * t;

	return true;
}
