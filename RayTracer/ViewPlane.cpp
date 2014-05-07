#include "ViewPlane.h"
#include "Sampler.h"
#include "MultiJittered.h"
#include "Regular.h"
#include "DebugMemory.h"

ViewPlane::ViewPlane(int hres, int vres, float pixelSize, float gamma)
	:hres(hres),vres(vres),pixelSize(pixelSize),gamma(gamma),invGamma(1/gamma),
	sampler(NULL),numSamples(0),maxDepth(1)
{
}

void ViewPlane::setSamples(const int numOfSamples)
{
	numSamples = numOfSamples;

	if(sampler)
	{
		delete sampler;
		sampler = NULL;
	}

	if(numSamples > 1)
	{
		sampler = new MultiJittered(numSamples);
	}
	else
	{
		sampler = new Regular(1);
	}
}

void ViewPlane::setSampler(Sampler* sampler)
{
	if(this->sampler)
	{
		delete this->sampler;
		this->sampler = NULL;
	}

	numSamples = sampler->getNumSamples();
	this->sampler = sampler;
}

ViewPlane::~ViewPlane()
{
	if(sampler != NULL)
	{
		delete sampler;
		sampler = NULL;
	}
}

ViewPlane::ViewPlane(const ViewPlane& value)
{
	hres = value.hres;
	vres = value.vres;
	pixelSize = value.pixelSize;
	gamma = value.gamma;
	invGamma = value.invGamma;
	numSamples = value.numSamples;
	maxDepth = value.maxDepth;

	sampler = value.sampler->clone();
}