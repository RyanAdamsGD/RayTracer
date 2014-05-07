#ifndef RAY_H
#define RAY_H
#include "glm\gtx\transform.hpp"
#include "TypeDefs.h"

class Ray
{
	glm::vec3 origin;
	glm::vec3 direction;
public:
	Ray(const glm::vec3& origin,const glm::vec3& direction);
	Ray(const Ray& r);

	const glm::vec3& getOrigin() const {return origin;}
	void setOrigin(const glm::vec3& origin) {this->origin = origin;}
	const glm::vec3& getDirection() const {return direction;}
	void setDirection(const glm::vec3& direction) {this->direction = glm::normalize(direction);}
};

#endif