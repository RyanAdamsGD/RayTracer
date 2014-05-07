#ifndef FBMTEXTURE_H
#define FBMTEXTURE_H
#include "Texture.h"
class LatticeNoise;

class FbmTexture: public Texture
{
	glm::vec3 colorMin;
	glm::vec3 colorMax;
	LatticeNoise* noise;

public:
	FbmTexture(void);
	virtual ~FbmTexture();
	virtual glm::vec3 getColor(const ShadeRec& sr)const;

	inline void setColorMin(const glm::vec3& value) {colorMin=value;}
	inline void setColorMax(const glm::vec3& value) {colorMax=value;}
	void setNoise(LatticeNoise* value);
};

#endif