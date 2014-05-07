#ifndef PURERANDOM_H
#define PURERANDOM_H
#include "glm\gtx\transform.hpp"
#include <vector>
#include "TypeDefs.h"
#include "Sampler.h"

class PureRandom:public Sampler
{
	virtual void generateSamples();
public:
	PureRandom(uint numSamples);
	virtual Sampler* clone()const {return new PureRandom(*this);}
	~PureRandom(void);
};

#endif