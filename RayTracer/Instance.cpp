#include "Instance.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "BoundingBox.h"

Instance::Instance(GeometricObject* object)
	:transformTexture(true),object(object),transform(),invTransform()
{
	computeBoundingBox();
}

Instance::Instance()
	:object(NULL),transformTexture(true),transform(),invTransform()
{
}

Instance::Instance(GeometricObject* object,const glm::mat4& transform)
	:transformTexture(true),object(object)
{
	invTransform = glm::inverse(glm::transpose(transform));
	this->transform = glm::transpose(transform);
	computeBoundingBox();
}

BoundingBox Instance::getBoundingBox()const
{
	return bbox;
}

void Instance::computeBoundingBox()
{
	if(object == NULL)
		return;

	BoundingBox objBox= object->getBoundingBox();
	glm::vec4 min(objBox.x0,objBox.y0,objBox.z0,1);
	glm::vec4 max(objBox.x1,objBox.y1,objBox.z1,1);

	min = min * transform;
	max = max * transform;
	glm::vec3 p0,p1;

	min.x > max.x ? p1.x = min.x, p0.x = max.x : p0.x = min.x, p1.x = max.x;
	min.y > max.y ? p1.y = min.y, p0.y = max.y : p0.y = min.y, p1.y = max.y;
	min.z > max.z ? p1.z = min.z, p0.z = max.z : p0.z = min.z, p1.z = max.z;

	min = glm::vec4(objBox.x1,objBox.y0,objBox.z0,1);
	max = glm::vec4(objBox.x0,objBox.y1,objBox.z1,1);

	min = min * transform;
	max = max * transform;

	glm::vec3 v0,v1;

	min.x > max.x ? v1.x = min.x, v0.x = max.x : v0.x = min.x, v1.x = max.x;
	min.y > max.y ? v1.y = min.y, v0.y = max.y : v0.y = min.y, v1.y = max.y;
	min.z > max.z ? v1.z = min.z, v0.z = max.z : v0.z = min.z, v1.z = max.z;

	if(p0.x > v0.x)
		p0.x = v0.x;
	if(p0.y > v0.y)
		p0.y = v0.y;
	if(p0.z > v0.z)
		p0.z = v0.z;

	if(p1.x < v1.x)
		p1.x = v1.x;
	if(p1.y < v1.y)
		p1.y = v1.y;
	if(p1.z < v1.z)
		p1.z = v1.z;

	min = glm::vec4(objBox.x1,objBox.y1,objBox.z0,1);
	max = glm::vec4(objBox.x0,objBox.y0,objBox.z1,1);

	min = min * transform;
	max = max * transform;

	min.x > max.x ? v1.x = min.x, v0.x = max.x : v0.x = min.x, v1.x = max.x;
	min.y > max.y ? v1.y = min.y, v0.y = max.y : v0.y = min.y, v1.y = max.y;
	min.z > max.z ? v1.z = min.z, v0.z = max.z : v0.z = min.z, v1.z = max.z;

	if(p0.x > v0.x)
		p0.x = v0.x;
	if(p0.y > v0.y)
		p0.y = v0.y;
	if(p0.z > v0.z)
		p0.z = v0.z;

	if(p1.x < v1.x)
		p1.x = v1.x;
	if(p1.y < v1.y)
		p1.y = v1.y;
	if(p1.z < v1.z)
		p1.z = v1.z;

	min = glm::vec4(objBox.x1,objBox.y0,objBox.z1,1);
	max = glm::vec4(objBox.x0,objBox.y1,objBox.z0,1);

	min = min * transform;
	max = max * transform;

	min.x > max.x ? v1.x = min.x, v0.x = max.x : v0.x = min.x, v1.x = max.x;
	min.y > max.y ? v1.y = min.y, v0.y = max.y : v0.y = min.y, v1.y = max.y;
	min.z > max.z ? v1.z = min.z, v0.z = max.z : v0.z = min.z, v1.z = max.z;

	if(p0.x > v0.x)
		p0.x = v0.x;
	if(p0.y > v0.y)
		p0.y = v0.y;
	if(p0.z > v0.z)
		p0.z = v0.z;

	if(p1.x < v1.x)
		p1.x = v1.x;
	if(p1.y < v1.y)
		p1.y = v1.y;
	if(p1.z < v1.z)
		p1.z = v1.z;

	bbox = BoundingBox(p1,p0);
}

bool Instance::hit(const Ray& ray, float& tmin, ShadeRec& sr) const
{
	float t;

	Ray transformedRay(glm::vec3(glm::vec4(ray.getOrigin(),1) * invTransform),
		glm::vec3(glm::vec4(ray.getDirection(),0) * invTransform));

	if(object->hit(transformedRay,t,sr))
	{
		if(object->getMaterial()!=NULL)
			material = object->getMaterial();
		if(!transformTexture)
			sr.localHitPoint = ray.getOrigin() + ray.getDirection() * t;

		tmin = t;
		sr.normal = glm::normalize(glm::vec3(glm::vec4(sr.normal,0) * transform));
		return true;
	}
	return false;
}

bool Instance::shadowHit(const Ray& ray, float& tmin) const
{
	float t;

	Ray transformedRay(glm::vec3(glm::vec4(ray.getOrigin(),1) * invTransform),
		glm::vec3(glm::vec4(ray.getDirection(),0) * invTransform));

	if(object->shadowHit(transformedRay,t))
	{
		tmin = t;
		return true;
	}
	return false;
}

void Instance::setTransform(const glm::mat4& value)
{
	transform = glm::transpose(value);
	invTransform = glm::inverse(glm::transpose(value));
	computeBoundingBox();
}

Instance::~Instance()
{
	if(object != NULL)
	{
		delete object;
		object = NULL;
	}
}

void Instance::setObject(GeometricObject* value)
{
	if(object != NULL)
	{
		delete object;
		object = NULL;
	}

	object = value;
	computeBoundingBox();
}
