#include "MeshTriangle.h"
#include "BoundingBox.h"
#include "TypeDefs.h"
#include "Mesh.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "HelperFunctions.h"

MeshTriangle::MeshTriangle(void)
{
}


MeshTriangle::~MeshTriangle(void)
{
}

bool MeshTriangle::shadowHit(const Ray& ray, float& tmin) const
{
	if(!castsShadows)
		return false;

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
	return true;
}

void MeshTriangle::computeNormal(const bool reverseNormal)
{
	normal = glm::cross(mesh->verts[index1] - mesh->verts[index0],
			 mesh->verts[index2] - mesh->verts[index0]);
	normal = glm::normalize(normal);
	
	if (reverseNormal)
		normal = -normal;
}

BoundingBox MeshTriangle::getBoundingBox()const
{
	float delta = 0.001f; 
	glm::vec3 v0 = mesh->verts[index0], v1 = mesh->verts[index1], v2 = mesh->verts[index2];
	
	glm::vec3 minimum(min(min(v0.x, v1.x), v2.x) - delta, min(min(v0.y, v1.y), v2.y) - delta, 
				 min(min(v0.z, v1.z), v2.z) - delta);
	glm::vec3 maximum(max(max(v0.x, v1.x), v2.x) + delta, max(max(v0.y, v1.y), v2.y) + delta, max(max(v0.z, v1.z), v2.z) + delta);

	return BoundingBox(maximum,minimum);
}

float MeshTriangle::interpolateU(float beta, float gamma) const
{
	return ( (1 - beta - gamma) * mesh->u[index0] 
				+ beta * mesh->u[index1] 
					+ gamma * mesh->u[index2] );
}

float MeshTriangle::interpolateV(float beta, float gamma) const
{
	return 1 - ( (1 - beta - gamma) * mesh->v[index0] 
				+ beta * mesh->v[index1] 
					+ gamma * mesh->v[index2] );
}
