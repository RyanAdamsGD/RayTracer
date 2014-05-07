#include "GlassOfWater.h"
#include "Disk.h"
#include "Instance.h"
#include "ConcavePartCylinder.h"
#include "ConvexPartCylinder.h"
#include "ConcavePartTorus.h"
#include "Annulus.h"
#include "DebugMemory.h"

GlassOfWater::GlassOfWater(void)
:height(3.0f), innerRadius(1.0f), wallThickness(0.1f),baseThickness(0.2f),
waterHeight(2.3f), meniscusRadius(0.05f)
{
	buildComponents();
}


GlassOfWater::~GlassOfWater(void)
{
}

GlassOfWater::GlassOfWater(float height,float innerRadius, float wallThickness, float baseThickness, 
float waterHeight, float meniscusRadius)
:height(height), innerRadius(innerRadius), wallThickness(wallThickness),baseThickness(baseThickness),
waterHeight(waterHeight), meniscusRadius(meniscusRadius)
{
	buildComponents();
}

//void GlassOfWater::buildComponents()
//{
//	// build the glass parts
//	
//	//rim
//	addObject(new Annulus(glm::vec3(0, height, 0), glm::vec3(0, 1, 0), innerRadius, innerRadius + wallThickness));
//	//bottom					   	
//	addObject(new Disk(glm::vec3(0), glm::vec3(0, -1, 0), innerRadius + wallThickness));  
//	// inner curved surface of glass
//	addObject(new ConcavePartCylinder(waterHeight + meniscusRadius, height, innerRadius)); 
//	// outer curved surface of glass			 
//	addObject(new ConvexPartCylinder(0, height, innerRadius + wallThickness));
//	
//	
//	// build the water parts
//	// top of water
//	addObject(new Disk(	glm::vec3(0, waterHeight, 0), glm::vec3(0, 1, 0), innerRadius - meniscusRadius));
//
//	// bottom of water						
//	addObject(new Disk(glm::vec3(0, baseThickness, 0), glm::vec3(0, -1, 0), innerRadius));
//
//	// curved surface of water				
//	addObject(new ConvexPartCylinder(baseThickness,	waterHeight + meniscusRadius, innerRadius));
//												
//	
//	// build the meniscus: we need an instance for this
//		
//	Instance* meniscus_ptr = new Instance (new ConcavePartTorus(innerRadius - meniscusRadius, meniscusRadius,
//																0, 360,			// azimuth angle - phi - range
//																270, 360));		// polar angle - theta - range
//	meniscus_ptr->setTransform(glm::translate(0.0f, waterHeight + meniscusRadius, 0.0f));													
//	addObject(meniscus_ptr);
//}

void GlassOfWater::buildComponents()
{
	// build the glass parts
	
	//rim
	addObject(new Annulus(glm::vec3(0, height, 0), glm::vec3(0, 1, 0), innerRadius, innerRadius + wallThickness));
	//bottom					   	
	addObject(new Disk(glm::vec3(0), glm::vec3(0, -1, 0), innerRadius + wallThickness));  
	// inner curved surface of glass
	addObject(new ConcavePartCylinder(waterHeight + meniscusRadius, height, innerRadius)); 
	// outer curved surface of glass			 
	addObject(new ConvexPartCylinder(0, height, innerRadius + wallThickness));
	
	
	// build the water parts
	// top of water
	addObject(new Disk(	glm::vec3(0, waterHeight, 0), glm::vec3(0, 1, 0), innerRadius));

	// bottom of water						
	addObject(new Disk(glm::vec3(0, baseThickness, 0), glm::vec3(0, -1, 0), innerRadius));

	// curved surface of water				
	addObject(new ConvexPartCylinder(baseThickness,	waterHeight, innerRadius));
												
	
	// build the meniscus: we need an instance for this
		
	//Instance* meniscus_ptr = new Instance (new ConcavePartTorus(innerRadius - meniscusRadius, meniscusRadius,
	//															0, 360,			// azimuth angle - phi - range
	//															270, 360));		// polar angle - theta - range
	//meniscus_ptr->setTransform(glm::translate(0.0f, waterHeight + meniscusRadius, 0.0f));													
	//addObject(meniscus_ptr);
}

void GlassOfWater::setGlassAirMaterial(Material* value)
{
	for(int i=0;i<4;i++)
		objects[i]->setMaterial(value);
}

void GlassOfWater::setWaterAirMaterial(Material* value)
{
	objects[4]->setMaterial(value);
	//objects[7]->setMaterial(value);
}

void GlassOfWater::setWaterGlassMaterial(Material* value)
{
	/*for(int i=5;i<7;i++)
		objects[i]->setMaterial(value);*/
	for(int i=5;i<7;i++)
		objects[i]->setMaterial(value);
}