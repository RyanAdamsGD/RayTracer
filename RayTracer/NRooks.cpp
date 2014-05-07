#include "NRooks.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

NRooks::NRooks(uint numSamples)
	:Sampler(numSamples)
{
	generateSamples();
}


NRooks::~NRooks(void)
{
}

void NRooks::generateSamples()
{
	//generate samples along main diagonal
	glm::vec2 point;
	for(uint p=0;p<numSets;p++)
		for(uint j=0;j<numSamples;j++)
		{
			point.x = (j + rand_float()) / numSamples;
			point.y = (j + rand_float()) / numSamples;
			samples.push_back(point);
		}

	shuffleXCoordinates();
	shuffleYCoordinates();
}

void NRooks::shuffleXCoordinates()
{
	uint target;
	for(uint p=0;p<numSets;p++)
		for(uint i=0;i<numSamples-1;i++)
		{
			target = rand() % numSamples + p * numSamples;
			float valueToSwitch = samples[i + p * numSamples + 1].x;
			samples[i + p * numSamples + 1].x = samples[target].x;
			samples[target].x = valueToSwitch;
		}
}

void NRooks::shuffleYCoordinates()
{
	uint target;
	for(uint p=0;p<numSets;p++)
		for(uint i=0;i<numSamples-1;i++)
		{
			target = rand() % numSamples + p * numSamples;
			float valueToSwitch = samples[i + p * numSamples + 1].y;
			samples[i + p * numSamples + 1].y = samples[target].y;
			samples[target].y = valueToSwitch;
		}
}