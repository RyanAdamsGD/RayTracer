#ifndef VIEWPLANE_H
#define VIEWPLANE_H
#include "TypeDefs.h"
class Sampler;

class ViewPlane
{
	uint hres;
	uint vres;
	float pixelSize; //adjusts zoom
	float gamma;
	float invGamma;
	Sampler* sampler;
	uint numSamples;
	uint maxDepth;

public:
	ViewPlane(int hres, int vres, float pixelSize, float gamma);
	ViewPlane(const ViewPlane& value);
	~ViewPlane();
	void setSamples(const int numOfSamples);
	void setSampler(Sampler* sampler);


	inline void setHRes(const uint value) {hres = value;}
	inline void setVRes(const uint value) {vres = value;}
	inline void setPixelSize(float value) {pixelSize = value;}
	inline void setGamma(float value) {gamma = value; invGamma = 1/gamma;}
	inline void setInvGamma(float value) {invGamma = value; gamma = 1/invGamma;}
	inline void setMaxDepth(const uint value) {maxDepth = value;}

	inline uint getHRes() const {return hres;}
	inline uint getVRes() const {return vres;}
	inline float getPixelSize() const {return pixelSize;}
	inline float getGamma() const {return gamma;}
	inline float getInvGamma() const {return invGamma;}
	inline uint getNumSamples() const {return numSamples;}
	inline Sampler* getSampler() const {return sampler;}
	inline uint getMaxDepth() const {return maxDepth;}
};

#endif