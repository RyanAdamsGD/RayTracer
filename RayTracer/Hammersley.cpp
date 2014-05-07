#include "Hammersley.h"
#include "DebugMemory.h"

Hammersley::Hammersley(uint numSamples)
	:Sampler(numSamples)
{
	generateSamples();
}


Hammersley::~Hammersley(void)
{
}

void Hammersley::generateSamples()
{
	for (int p = 0; p < numSets; p++)		
		for (int j = 0; j < numSamples; j++) 
		{
			glm::vec2 pv((float) j / (float) numSamples, phi(j));
			samples.push_back(pv);
		}
}

float Hammersley::phi (int j)
{
	float x = 0.0;
	float f = 0.5;

	while(j)
	{
		x += f * (float)(!j & 1);
		j /= 2;
		f *= 0.5;
	}
	return x;
}
