#include "LatticeNoise.h"
#include "HelperFunctions.h"
#include "MultiJittered.h"
#include "DebugMemory.h"

const unsigned char LatticeNoise::permutationTable[kTableSize] =
{
    225,155,210,108,175,199,221,144,203,116, 70,213, 69,158, 33,252,
    5, 82,173,133,222,139,174, 27,  9, 71, 90,246, 75,130, 91,191,
    169,138,  2,151,194,235, 81,  7, 25,113,228,159,205,253,134,142,
    248, 65,224,217, 22,121,229, 63, 89,103, 96,104,156, 17,201,129,
    36,  8,165,110,237,117,231, 56,132,211,152, 20,181,111,239,218,
    170,163, 51,172,157, 47, 80,212,176,250, 87, 49, 99,242,136,189,
    162,115, 44, 43,124, 94,150, 16,141,247, 32, 10,198,223,255, 72,
    53,131, 84, 57,220,197, 58, 50,208, 11,241, 28,  3,192, 62,202,
    18,215,153, 24, 76, 41, 15,179, 39, 46, 55,  6,128,167, 23,188,
    106, 34,187,140,164, 73,112,182,244,195,227, 13, 35, 77,196,185,
    26,200,226,119, 31,123,168,125,249, 68,183,230,177,135,160,180,
    12,  1,243,148,102,166, 38,238,251, 37,240,126, 64, 74,161, 40,
    184,149,171,178,101, 66, 29, 59,146, 61,254,107, 42, 86,154,  4,
    236,232,120, 21,233,209, 45, 98,193,114, 78, 19,206, 14,118,127,
    48, 79,147, 85, 30,207,219, 54, 88,234,190,122, 95, 67,143,109,
    137,214,145, 93, 92,100,245,  0,216,186, 60, 83,105, 97,204, 52
};

LatticeNoise::LatticeNoise(void)
	:numOctaves(1),gain(0.75),lacunarity(2.0),fbmMin(-1.0),fbmMax(1.0)
{
	initValueTable(seedValue);
	computeFbmBounds();
}

LatticeNoise::LatticeNoise(float gain, float lacunarity, const int numOctaves)
	:gain(gain),lacunarity(lacunarity),numOctaves(numOctaves)
{
	initValueTable(seedValue);
	computeFbmBounds();
}

void LatticeNoise::computeFbmBounds()
{
	if (gain == 1.0)
		fbmMax = numOctaves;
	else
		fbmMax = (1.0 - pow(gain, numOctaves)) / (1.0 - gain);
		
	fbmMin = -fbmMax;
}

void LatticeNoise::initValueTable(int seed)
{
	srand(seed);
	for(int i=0;i<kTableSize;i++)
		valueTable[i] = rand_float(-1.0f,1.0f);
}

float LatticeNoise::valueTurbulence(const glm::vec3& point)const
{
	//typical bounds are -1-1
	float amplitude = 1.0;
	float frequency = 1.0;
	float turbulence = 0.0;

	for(int j=0;j<numOctaves;j++)
	{
		turbulence += amplitude * fabs(valueNoise(frequency * point));
		amplitude *= 0.5;
		frequency *= 2.0;
	}

	turbulence /= fbmMax;

	return turbulence;
}

float LatticeNoise::valueFBM(const glm::vec3& point)const
{
	//typical bounds are -1-1
	float amplitude = 1.0;
	float frequency = 1.0;
	float fbm = 0.0;

	for(int j=0;j<numOctaves;j++)
	{
		fbm += amplitude * valueNoise(frequency * point);
		amplitude *= gain;
		frequency *= lacunarity;
	}

	fbm = (fbm - fbmMin) / (fbmMax - fbmMin);


	return fbm;
}

void LatticeNoise::setNumOctaves(int value) 
{
	numOctaves=value;
	computeFbmBounds();
}

void LatticeNoise::setGain(float value) 
{
	gain=value;
	computeFbmBounds();
}

void LatticeNoise::initVectorTable(int seedValue)
{
	float r1, r2;
	float x, y, z;
	float r, phi;
	
	srand(seedValue);
	MultiJittered* sampler = new MultiJittered(256,1);
   
    for (int j = 0; j < kTableSize; j++) {    	
    	glm::vec2 sample_point = sampler->sampleOneSet();  // on the unit square
    	r1 	= sample_point.x;
    	r2 	= sample_point.y;
    	z 	= 1.0 - 2.0 * r1;
    	r 	= sqrt(1.0 - z * z);
    	phi = TWO_PI * r2;
    	x 	= r * cos(phi);
    	y 	= r * sin(phi);
    	vectorTable[j] = glm::normalize(glm::vec3(x, y, z));   // random unit vector
    }
	
	delete sampler;
}

glm::vec3 LatticeNoise::vectorFBM(const glm::vec3& point)const
{
	float amplitude = 1.0;
	float frequency = 1.0;
	glm::vec3 sum(0.0);
			
	for (int j = 0; j < numOctaves; j++) 
	{
		sum += amplitude * vectorNoise(frequency * point); 
		amplitude *= gain; 
		frequency *= lacunarity;
	}
		
	return (sum);
}
