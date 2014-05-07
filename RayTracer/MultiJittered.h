#ifndef MULTIJITTERED_H
#define MULTIJITTERED_H
#include "glm\gtx\transform.hpp"
#include <vector>
#include "TypeDefs.h"
#include "Sampler.h"

class MultiJittered:public Sampler
{
	virtual void generateSamples();
public:
	virtual Sampler* clone()const {return new MultiJittered(*this);}
	MultiJittered(uint numSamples);
	MultiJittered(uint numSamples, uint numSets);
	MultiJittered(const MultiJittered& value);
};

#endif