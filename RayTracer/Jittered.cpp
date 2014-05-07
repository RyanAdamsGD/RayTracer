#include "Jittered.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

Jittered::Jittered(uint numSamples)
	:Sampler(numSamples)
{
	generateSamples();
}

void Jittered::generateSamples()
{
	int n = (int) sqrt((float)numSamples);

	for(uint p=0;p<numSets;p++)
		for(uint j=0;j<n;j++)
			for(uint k=0;k<n;k++)
			{
				glm::vec2 sp((k + rand_float()) / n, (j + rand_float()) /n);
				samples.push_back(sp);
			}


}