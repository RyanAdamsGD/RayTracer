#include "MultiJittered.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

MultiJittered::MultiJittered(uint numSamples)
	:Sampler(numSamples)
{
	generateSamples();
}

MultiJittered::MultiJittered(uint numSamples, uint numSets)
	:Sampler(numSamples, numSets)
{
	generateSamples();
}

MultiJittered::MultiJittered(const MultiJittered& value)
	:Sampler(value)
{
}

void MultiJittered::generateSamples()
{		
	// num_samples needs to be a perfect square

	int n = (int)sqrt((float)numSamples);
	float subcell_width = 1.0 / ((float) numSamples);

	// fill the samples array with dummy points to allow us to use the [ ] notation when we set the 
	// initial patterns

	glm::vec2 fill_point;
	for (uint j = 0; j < numSamples * numSets; j++)
		samples.push_back(fill_point);

	// distribute points in the initial patterns

	for (uint p = 0; p < numSets; p++) 
		for (uint i = 0; i < n; i++)		
			for (uint j = 0; j < n; j++) 
			{
				samples[i * n + j + p * numSamples].x = (i * n + j) * subcell_width + rand_float(0, subcell_width);
				samples[i * n + j + p * numSamples].y = (j * n + i) * subcell_width + rand_float(0, subcell_width);
			}

	// shuffle x coordinates

	for (uint p = 0; p < numSets; p++) 
		for (uint i = 0; i < n; i++)		
			for (uint j = 0; j < n; j++) 
			{
				uint k = rand_float(j, n - 1);
				float t = samples[i * n + j + p * numSamples].x;
				samples[i * n + j + p * numSamples].x = samples[i * n + k + p * numSamples].x;
				samples[i * n + k + p * numSamples].x = t;
			}

	// shuffle y coordinates

	for (int p = 0; p < numSets; p++)
		for (uint i = 0; i < n; i++)		
			for (uint j = 0; j < n; j++) 
			{
				uint k = rand_float(j, n - 1);
				float t = samples[j * n + i + p * numSamples].y;
				samples[j * n + i + p * numSamples].y = samples[k * n + i + p * numSamples].y;
				samples[k * n + i + p * numSamples].y = t;
			}
}
