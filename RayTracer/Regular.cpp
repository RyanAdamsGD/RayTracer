#include "Regular.h"
#include "DebugMemory.h"

Regular::Regular(uint numSamples)
	:Sampler(numSamples)
{
	generateSamples();
}

Regular::Regular(const Regular& value)
	:Sampler(value)
{
}

void Regular::generateSamples()
{
	int n = (int) sqrtf(numSamples);

	for (int j=0;j<numSets;j++)
		for (int p=0;p<n;p++)		
			for (int q=0;q<n;q++)
				samples.push_back(glm::vec2((q + 0.5) / n, (p + 0.5) / n));
}