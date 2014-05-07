#include "FbmTexture.h"
#include "CubicNoise.h"
#include "ShadeRec.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

FbmTexture::FbmTexture(void)
	:noise(new CubicNoise),colorMax(1),colorMin(0)
{
}

glm::vec3 FbmTexture::getColor(const ShadeRec& sr)const
{
	return lerp(noise->valueFBM(sr.localHitPoint), colorMin, colorMax);
}

FbmTexture::~FbmTexture()
{
	if(noise != NULL)
	{
		delete noise;
		noise = NULL;
	}
}

void FbmTexture::setNoise(LatticeNoise* value)
{
	if(noise != NULL)
	{
		delete noise;
		noise = NULL;
	}

	noise = value;
}