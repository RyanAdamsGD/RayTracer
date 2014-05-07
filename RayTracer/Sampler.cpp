#include "Sampler.h"
#include "HelperFunctions.h"
#include <algorithm>
#include "TypeDefs.h"
#include "DebugMemory.h"

//i use 83 sets because it is a prime number unlikely to align with the resolution
Sampler::Sampler(uint numSamples)
	:numSamples(numSamples),currentNumSamplePoints(0),jump(0),numSets(83)
{
	setupShuffledIndicies();
}

Sampler::Sampler(uint numSamples, uint numSets)
	:numSamples(numSamples),currentNumSamplePoints(0),jump(0),numSets(numSets)
{
	setupShuffledIndicies();
}

void Sampler::shuffleYCoordinates()
{
	for (int p = 0; p < numSets; p++)
		for (int i = 0; i <  numSamples - 1; i++) {
			int target = (int)rand_float(0,int(0xffffffff)) % numSamples + p * numSamples;
			float temp = samples[i + p * numSamples + 1].x;
			samples[i + p * numSamples + 1].x = samples[target].x;
			samples[target].x = temp;
		}
}

void Sampler::shuffleXCoordinates()
{
	for (int p = 0; p < numSets; p++)
		for (int i = 0; i <  numSamples - 1; i++) {
			int target = (int)rand_float(0,int(0xffffffff)) % numSamples + p * numSamples;
			float temp = samples[i + p * numSamples + 1].y;
			samples[i + p * numSamples + 1].y = samples[target].y;
			samples[target].y = temp;
		}
}

glm::vec2 Sampler::sampleUnitSquare()
{
	//start of a new pixel
	if(currentNumSamplePoints % numSamples == 0)
	{
		jump = (uint)(rand_float() * (numSets-1)) * numSamples;
	}
	return (samples[jump + shuffledIndicies[jump + currentNumSamplePoints++ % numSamples]]);
}

glm::vec2 Sampler::sampleUnitDisk()
{
	//start of a new pixel
	if(currentNumSamplePoints % numSamples == 0)
	{
		jump = (uint)(rand_float() * (numSets-1)) * numSamples;
	}
	return (diskSamples[jump + shuffledIndicies[jump + currentNumSamplePoints++ % numSamples]]);
}

glm::vec3 Sampler::sampleHemisphere()
{
	//start of a new pixel
	if(currentNumSamplePoints % numSamples == 0)
	{
		jump = (uint)(rand_float() * (numSets-1)) * numSamples;
	}
	return (hemisphereSamples[jump + shuffledIndicies[jump + currentNumSamplePoints++ % numSamples]]);
}

void Sampler::setupShuffledIndicies()
{
	shuffledIndicies.reserve(numSamples * numSets);
	std::vector<int> indicies;

	for(uint j=0;j<numSamples;j++)
		indicies.push_back(j);

	for(uint p=0;p<numSets;p++)
	{
		random_shuffle(indicies.begin(),indicies.end());

		for(uint j=0;j<numSamples;j++)
			shuffledIndicies.push_back(indicies[j]);
	}

}

void Sampler::mapSamplesToUnitDisk()
{
	uint size = samples.size();
	float r, phi;
	glm::vec2 samplePoint;

	diskSamples.reserve(size);

	for(uint j=0;j<size;j++)
	{
		//map samples to [-1,1] [-1,1]
		samplePoint.x = 2.0 * samples[j].x - 1.0;
		samplePoint.x = 2.0 * samples[j].y - 1.0;

		//sector 1 & 2
		if(samplePoint.x > -samplePoint.y)
		{
			//sector 1
			if(samplePoint.x > samplePoint.y)
			{
				r = samplePoint.x;
				phi = samplePoint.y/ samplePoint.x;
			}
			//sector 2
			else
			{
				r = samplePoint.x;
				phi = 2.0 - samplePoint.x/samplePoint.y;
			}
		}
		//sector 3 & 4
		else
		{
			//sector3
			if(samplePoint.x > samplePoint.y)
			{
				r = -samplePoint.x;
				phi = 4.0 + samplePoint.y/ samplePoint.x;
			}
			//sector 4
			else
			{
				r = -samplePoint.x;
				//avoid divide by zero if at the origin
				if(samplePoint.y != 0.0)
				{
					phi = 2.0 - samplePoint.x/samplePoint.y;
				}
				else
				{
					phi = 0.0;
				}
			}
		}

		phi *= PI_OVER_4;

		diskSamples[j].x = r * cos(phi);
		diskSamples[j].y = r * sin(phi);
	}
}

Sampler::~Sampler()
{
	shuffledIndicies.clear();
	samples.clear();
	diskSamples.clear();
	hemisphereSamples.clear();
}

void Sampler::mapSamplesToHemisphere(const float e)
{
	uint size = samples.size();
	hemisphereSamples.reserve(numSamples * numSets);

	for(uint j=0;j<size;j++)
	{
		float cosPhi = cos(2.0f * PI * samples[j].x);
		float sinPhi = sin(2.0f * PI * samples[j].x);
		float cosTheta = pow((1.0f - samples[j].y), 1.0f / (e + 1.0f));
		float sinTheta = sqrt(1.0f - cosTheta * cosTheta);
		hemisphereSamples.push_back(glm::vec3(sinTheta* cosPhi,sinTheta * sinPhi, cosTheta));
	} 
}

Sampler::Sampler(const Sampler& s)
	:numSamples(s.numSamples),numSets(s.numSets),shuffledIndicies(),samples(),
	diskSamples(),hemisphereSamples(),currentNumSamplePoints(s.currentNumSamplePoints),
	jump(s.jump)
{
	shuffledIndicies = s.shuffledIndicies;
	samples = s.samples;
	diskSamples = s.diskSamples;
	hemisphereSamples = s.hemisphereSamples;
}

glm::vec2 Sampler::sampleOneSet()
{
	return(samples[currentNumSamplePoints++ % numSamples]);  
}