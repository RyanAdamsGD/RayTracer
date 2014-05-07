#ifndef NROOKS_H
#define NROOKS_H
#include "glm\gtx\transform.hpp"
#include <vector>
#include "TypeDefs.h"
#include "Sampler.h"

class NRooks:public Sampler
{
	virtual void generateSamples();
	void shuffleXCoordinates();
	void shuffleYCoordinates();
public:
	virtual Sampler* clone()const {return new NRooks(*this);}
	NRooks(uint numSamples);
	~NRooks(void);
};

#endif