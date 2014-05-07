#ifndef JITTERED_H
#define JITTERED_H
#include "Sampler.h"

class Jittered:public Sampler
{
	virtual void generateSamples();
public:
	virtual Sampler* clone()const {return new Jittered(*this);}
	Jittered(uint numSamples);
};

#endif