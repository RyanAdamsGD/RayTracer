#ifndef TEXTURE_H
#define TEXTURE_H
#include "glm\gtx\transform.hpp"
class ShadeRec;

class Texture
{
public:
	virtual void cleanUp() {}
	Texture(void);
	virtual ~Texture();

	virtual glm::vec3 getColor(const ShadeRec& sr)const;
};

#endif