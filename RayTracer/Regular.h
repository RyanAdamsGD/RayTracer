#ifndef REGULAR_H
#define REGULAR_H
#include "glm\gtx\transform.hpp"
#include <vector>
#include "TypeDefs.h"
#include "Sampler.h"

class Regular:public Sampler
{
	virtual void generateSamples();
public:
	Regular(uint numSamples);
	Regular(const Regular& value);
	virtual Sampler* clone()const {return new Regular(*this);}
};

#endif