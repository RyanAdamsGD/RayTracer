#ifndef GLASSOFWATER_H
#define GLASSOFWATER_H
#include "Compound.h"

class GlassOfWater: public Compound 
{
protected:
	float height;
	float innerRadius;
	float wallThickness;
	float baseThickness;
	float waterHeight;
	float meniscusRadius;	

public:
	GlassOfWater(void);   									
	GlassOfWater(float height,float innerRadius, float wallThickness, float baseThickness, 
		float waterHeight, float meniscusRadius);

	virtual ~GlassOfWater(void);
	
	void buildComponents(void);

	void setGlassAirMaterial(Material* value);
	void setWaterAirMaterial(Material* value); 
	void setWaterGlassMaterial(Material* value); 
};

#endif