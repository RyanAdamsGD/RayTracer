#include "PureRandom.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

PureRandom::PureRandom(uint numSamples)
	:Sampler(numSamples)
{
	generateSamples();
}


PureRandom::~PureRandom(void)
{
}

void PureRandom::generateSamples()
{
	for (int p=0;p<numSets;p++)         
		for (int q=0; q<numSamples;q++)
			samples.push_back(glm::vec2(rand_float(), rand_float()));
}
