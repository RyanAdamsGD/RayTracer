#include "WrappedFbmTexture.h"
#include "CubicNoise.h"
#include "ShadeRec.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

WrappedFbmTexture::WrappedFbmTexture(void)
	:noise(new CubicNoise),colorMax(1),colorMin(0),expansionNumber(2)
{
	noise->setNumOctaves(4);
	noise->setGain(0.25);
	noise->setLacunarity(2);
}

glm::vec3 WrappedFbmTexture::getColor(const ShadeRec& sr)const
{
	float noiseV = expansionNumber * noise->valueFBM(sr.localHitPoint);
	float value = noiseV - FLOOR(noiseV);

	return lerp(value, colorMin, colorMax);
}

WrappedFbmTexture::~WrappedFbmTexture()
{
	if(noise != NULL)
	{
		delete noise;
		noise = NULL;
	}
}

void WrappedFbmTexture::setNoise(LatticeNoise* value)
{
	if(noise != NULL)
	{
		delete noise;
		noise = NULL;
	}

	noise = value;
}