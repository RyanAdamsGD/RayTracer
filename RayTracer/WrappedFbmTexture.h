#ifndef WRAPPEDFBMTEXTURE_H
#define WRAPPEDFBMTEXTURE_H
#include "Texture.h"
class LatticeNoise;

class WrappedFbmTexture: public Texture
{
	LatticeNoise* noise;
	glm::vec3 colorMin;
	glm::vec3 colorMax;
	float expansionNumber;

public:
	WrappedFbmTexture(void);
	virtual ~WrappedFbmTexture();
	virtual glm::vec3 getColor(const ShadeRec& sr)const;

	inline void setColorMin(const glm::vec3& value) {colorMin=value;}
	inline void setColorMax(const glm::vec3& value) {colorMax=value;}
	void setNoise(LatticeNoise* value);
};

#endif