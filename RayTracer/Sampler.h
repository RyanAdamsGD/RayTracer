#ifndef SAMPLER_H
#define SAMPLER_H
#include "glm\gtx\transform.hpp"
#include <vector>
#include "TypeDefs.h"

class Sampler
{
protected:
	uint numSamples;
	uint numSets;
	std::vector<uint> shuffledIndicies;
	std::vector<glm::vec2> samples;
	std::vector<glm::vec2> diskSamples;
	std::vector<glm::vec3> hemisphereSamples;
	ulong currentNumSamplePoints; 
	uint jump; //we use this to keep from getting aliasing artifacts from matching aspect ratio
			   //and sample size
	void shuffleYCoordinates();
	void shuffleXCoordinates();

public:
	Sampler(uint numSamples);
	Sampler(uint numSamples, uint numSets);
	Sampler(const Sampler& value);
	virtual ~Sampler();
	virtual Sampler* clone() const = 0;
	virtual void generateSamples() = 0;

	void setupShuffledIndicies();
	void shuffleSamples();

	glm::vec2 sampleOneSet();
	glm::vec2 sampleUnitSquare(); //we really want to keep this parameterless since we call it in
								  //many places and don't want to try and keep the parameters in sync
	glm::vec2 sampleUnitDisk();
	glm::vec3 sampleHemisphere();

	void mapSamplesToUnitDisk();
	void mapSamplesToHemisphere(const float e);
	inline uint getNumSamples() {return numSamples;}
};

#endif