#ifndef HAMMERSLEY_H
#define HAMMERSLEY_H
#include "glm\gtx\transform.hpp"
#include <vector>
#include "TypeDefs.h"
#include "Sampler.h"

class Hammersley:public Sampler
{
	float phi (int j);
	virtual void generateSamples();
public:
	virtual Sampler* clone()const {return new Hammersley(*this);}
	Hammersley(uint numSamples);
	~Hammersley(void);
};

#endif