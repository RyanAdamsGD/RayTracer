#include "Ray.h"


Ray::Ray(const glm::vec3& origin,const glm::vec3& direction)
	:origin(origin),direction(glm::normalize(direction))
{
}

Ray::Ray(const Ray& r)
	:origin(r.origin),direction(r.direction)
{
}
