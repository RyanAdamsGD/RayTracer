#include "World.h"
#include "GeometricObject.h"
#include "MultipleObjects.h"
#include "Sphere.h"
#include "Plane.h"
#include "HelperFunctions.h"
#include "Sampler.h"
#include "MultiJittered.h"
#include "PinHoleCamera.h"
#include "RayCast.h"
#include "PointLight.h"
#include "Matte.h"
#include "AmbientOccluder.h"
#include "Regular.h"
#include "Phong.h"
#include "Instance.h"
#include "Triangle.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "Grid.h"
#include "Whitted.h"
#include "Reflective.h"
#include "Rect.h"
#include "Transparent.h"
#include "SVMatte.h"
#include "ImageTexture.h"
#include "FileLoader.h"
#include "ConstantColor.h"
#include "WoodTexture.h"
#include "RectangularMapping.h"
#include "Dielectric.h"
#include "Checker3D.h"
#include "Cylinder.h"
#include "GlassOfWater.h"
#include "AreaLighting.h"
#include "AreaLight.h"
#include "Emissive.h"
#include "Box.h"
#include "ConcavePartCylinder.h"
#include "ConvexPartCylinder.h"
#include "Disk.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

//////////////////////////////////////
/////2 Sphere and plane with shadows
//////////////////////////////////////
//
//void World::buildScene(int vres,int hres)
//{
//	int num_samples = 16;
//
//	viewPlane.setHRes(400);
//	viewPlane.setVRes(400);
//	viewPlane.setPixelSize(0.5);
//	viewPlane.setSamples(num_samples); 
//	
//	tracer = new RayCast(this);
//	
//	AmbientOccluder* ambient = new AmbientOccluder(true,glm::vec3(1.0),0.3);
//	ambient->setSampler(new Regular(16));
//	setAmbientLight(ambient);
//	
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera(glm::vec3(0, 0, 500)
//		,glm::vec3(-5, 0, 0),850.0);   
//	setCamera(pinhole_ptr);
//	
//	PointLight* light_ptr2 = new PointLight(false,3.0,glm::vec3(1.0),glm::vec3(100, 50, 150));
//	addLight(light_ptr2);
//
//	Matte* matte_ptr1 = new Matte;
//	matte_ptr1->setKAmbient(0.25);	
//	matte_ptr1->setKDiffuse(0.65);
//	matte_ptr1->setColor(glm::vec3(1, 1, 0));	  				// yellow	
//	Sphere*	sphere_ptr1 = new Sphere(glm::vec3(10, -5, 0), 27); 
//	sphere_ptr1->setMaterial(matte_ptr1);	   							
//	addObject(sphere_ptr1);
//	
//	Matte* matte_ptr2 = new Matte;
//	matte_ptr2->setKAmbient(0.15);	
//	matte_ptr2->setKDiffuse(0.85);
//	matte_ptr2->setColor(glm::vec3(0.71, 0.40, 0.16));   		// brown
//	Sphere*	sphere_ptr2 = new Sphere(glm::vec3(-25, 10, 5), 27); 			
//	sphere_ptr2->setMaterial(matte_ptr2);							
//	addObject(sphere_ptr2);
//	
//	Matte* matte_ptr3 = new Matte;
//	matte_ptr3->setKAmbient(0.15);	
//	matte_ptr3->setKDiffuse(0.5);
//	matte_ptr3->setColor(glm::vec3(0, 0.4, 0.2));				// dark green
//	Plane* plane_ptr = new Plane(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)); 
//	plane_ptr->setMaterial(matte_ptr3);								
//	addObject(plane_ptr);
//}

//////////////////////////////////
/// Ambient Occluded Sphere
/////////////////////////////////
//void World::buildScene(int vres,int hres)
//{
////		int num_samples = 1;   	// for Figure 17.4(a)
////	int num_samples = 16;  	// for Figure 17.4(b)
////	int num_samples = 64;  	// for Figure 17.4(c)
////	int num_samples = 256;	// for Figure 17.4(d)
//	int num_samples = 1024;	// for Figure 17.4(d)
//	
//		viewPlane.setHRes(400);	  		
//		viewPlane.setVRes(400);
//		viewPlane.setSamples(num_samples);  
//	
//	tracer = new RayCast(this);
//		
//	MultiJittered* sampler_ptr = new MultiJittered(num_samples);
//	
//	AmbientOccluder* occluder_ptr = new AmbientOccluder(true,glm::vec3(1.0),1.0);
//	occluder_ptr->setSampler(sampler_ptr);
//	ambientLight = occluder_ptr;	
//	
//		
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera(glm::vec3(25, 20, -45),glm::vec3(0, 1, 0),5000);
//	pinhole_ptr->computeUVW();     
//	setCamera(pinhole_ptr);
//	
//	// sphere
//	
//	Matte* matte_ptr1 = new Matte;			
//	matte_ptr1->setKAmbient(0.75);		
//	matte_ptr1->setKDiffuse(0);
//	matte_ptr1->setColor(glm::vec3(1, 1, 0));   // yellow
//		
//	Sphere* sphere_ptr = new Sphere (glm::vec3(0, 1, 0), 1);  
//	sphere_ptr->setMaterial(matte_ptr1);
//	addObject(sphere_ptr);	
//	
//	// ground plane
//	
//	Matte* matte_ptr2 = new Matte;			
//	matte_ptr2->setKAmbient(0.75);		
//	matte_ptr2->setKDiffuse(0);
//	matte_ptr2->setColor(glm::vec3(1.0));        
//	
//	Plane* plane_ptr = new Plane(glm::vec3(0), glm::vec3(0, 1, 0));
//	plane_ptr->setMaterial(matte_ptr2);
//	addObject(plane_ptr);
//}

//////////////////////////////
///Glossy specular transformed sphere
//////////////////////////////
//void World::buildScene(int vres,int hres)
//{
//	int num_samples = 16;
//
//	viewPlane.setHRes(400);
//	viewPlane.setVRes(400);
//	viewPlane.setSamples(16);
//
//	tracer = new RayCast(this);
//
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera();
//	pinhole_ptr->setEye(glm::vec3(100, 0, 100));   
//	pinhole_ptr->setLookAt(glm::vec3(0, 1, 0)); 	 
//	pinhole_ptr->setViewPlaneDistance(8000);	
//	pinhole_ptr->computeUVW();
//	setCamera(pinhole_ptr);
//
//	PointLight* light_ptr = new PointLight(true,3.0,glm::vec3(1),glm::vec3(50,50,1));
//	addLight(light_ptr);
//
//	AmbientOccluder* ambient = new AmbientOccluder(true,glm::vec3(1.0),0.3);
//	ambient->setSampler(new Regular(16));
//	setAmbientLight(ambient);
//
//	Phong* phong_ptr = new Phong;			
//	phong_ptr->setColor(glm::vec3(0.75));  
//	phong_ptr->setKAmbient(0.25); 
//	phong_ptr->setKDiffuse(0.8);
//	phong_ptr->setKSpecular(0.15); 
//	phong_ptr->setExponent(50.0);  
//
//	Instance* ellipsoid_ptr = new Instance(new Sphere(glm::vec3(0.0),1.0));
//	ellipsoid_ptr->setMaterial(phong_ptr);
//	glm::mat4 transform = glm::scale(2.0, 3.0, 1.0) * glm::rotate(45.0,1.0,0.0,0.0) * glm::translate(0.0, 1.0, 0.0); 
//	ellipsoid_ptr->setTransform(transform);
//	addObject(ellipsoid_ptr);
//}

//////////////////////////////
////Three triangles
/////////////////////////////
//void World::buildScene(int vres,int hres) 
//{
//	int num_samples = 16;
//
//	viewPlane.setHRes(400);
//	viewPlane.setVRes(400);
//	viewPlane.setSamples(num_samples);
//
//	tracer = new RayCast(this);
//
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
//	pinhole_ptr->setEye(glm::vec3(25, 200, 100));  
//	pinhole_ptr->setLookAt(glm::vec3(-0.5, 0, 0));  
//	pinhole_ptr->setViewPlaneDistance(8000);	
//	pinhole_ptr->computeUVW();
//	setCamera(pinhole_ptr);
//
//	MultiJittered* sampler_ptr = new MultiJittered(num_samples);
//	AmbientOccluder* occluder_ptr = new AmbientOccluder(true,glm::vec3(1.0),1.0);
//	occluder_ptr->setSampler(sampler_ptr);
//	ambientLight = occluder_ptr;
//
//	PointLight* light_ptr1 = new PointLight(true,1.0,glm::vec3(1.0),glm::vec3());
//	light_ptr1->setPosition(glm::vec3(1.5, 6, 1));
//	light_ptr1->setIntensity(3.0);
//	light_ptr1->setUseShadows(true);
//	addLight(light_ptr1);
//
//
//	// yellow triangle
//
//	Phong* matte_ptr1 = new Phong;			
//	matte_ptr1->setKAmbient(0.25); 
//	matte_ptr1->setKDiffuse(0.75);
//	matte_ptr1->setKSpecular(0.30);
//	matte_ptr1->setExponent(30);
//	matte_ptr1->setColor(glm::vec3(1, 1, 0));
//
//	Triangle* triangle_ptr1 = new Triangle(glm::vec3(2, 0.5, 5), glm::vec3(2, 1.5, -5), glm::vec3(-1, 0, -4)); 
//	triangle_ptr1->setMaterial(matte_ptr1);
//	addObject(triangle_ptr1);
//
//
//	//dark green triangle (transformed)
//
//	Phong* matte_ptr2 = new Phong;			
//	matte_ptr2->setKAmbient(0.25); 
//	matte_ptr2->setKDiffuse(0.75);
//	matte_ptr2->setKSpecular(0.30);
//	matte_ptr2->setExponent(30);
//	matte_ptr2->setColor(glm::vec3(0.0, 0.5, 0.41));
//
//	Instance* triangle_ptr2 = new Instance(new Triangle(glm::vec3(2, 1, 5), glm::vec3(2, 0.5, -5), glm::vec3(-1, -1, -4))); 
//	triangle_ptr2->setTransform(glm::rotate(-120.0,0.0,1.0,0.0));
//	triangle_ptr2->setMaterial(matte_ptr2);
//	addObject(triangle_ptr2);
//
//
//	//brown triangle (transformed)
//
//	Phong* matte_ptr3 = new Phong;			
//	matte_ptr3->setKAmbient(0.25); 
//	matte_ptr3->setKDiffuse(0.75);
//	matte_ptr3->setKSpecular(0.30);
//	matte_ptr3->setExponent(30);
//	matte_ptr3->setColor(glm::vec3(0.71, 0.40, 0.16));
//
//	Instance* triangle_ptr3 = new Instance(new Triangle(glm::vec3(2, 1, -5), glm::vec3(-1, 0, -4),glm::vec3(2, 0, 5))); 
//	triangle_ptr3->setTransform(glm::rotate(-240.0,0.0,1.0,0.0));
//	triangle_ptr3->setMaterial(matte_ptr3);
//	addObject(triangle_ptr3);
//}


///////////////////////////////////////
///100,000 sphere cube in under 20 secs
///////////////////////////////////////
//void World::buildScene(int vres,int hres) 
//{
//	int num_samples = 1;
//	
//	viewPlane.setHRes(800);
//	viewPlane.setVRes(800);
//	viewPlane.setSamples(num_samples);
//	
//	tracer = new RayCast(this);
//
//	ambientLight = new AmbientLight(true);
//	
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
//	pinhole_ptr->setEye(glm::vec3(10, 15, 30));
//	pinhole_ptr->setLookAt(glm::vec3(0.3, -1, 0));
//	pinhole_ptr->setViewPlaneDistance(7000); 
//	pinhole_ptr->computeUVW();
//	setCamera(pinhole_ptr);
//	
//	DirectionalLight* light_ptr = new DirectionalLight;   
//	light_ptr->setDirection(glm::vec3(-10, 20, 20));				
//	light_ptr->setIntensity(3.0);   
//	light_ptr->setUseShadows(true);
//	addLight(light_ptr);
//	
//	int num_spheres = 100000;
//	
//	float volume = 0.1 / num_spheres;
//	float radius = pow(0.75 * volume / 3.14159, 0.333333);
//	
//	Grid* grid_ptr = new Grid;  
//	
//	for (int j = 0; j < num_spheres; j++) {
//		Matte* matte_ptr = new Matte;
//		matte_ptr->setKAmbient(0.25);
//		matte_ptr->setKDiffuse(0.75);
//		matte_ptr->setColor(glm::vec3((float)rand_float(), (float)rand_float(), (float)rand_float()));
//		
//		Sphere*	sphere_ptr = new Sphere; 
//		sphere_ptr->setRadius(radius);
//		glm::vec3 center(rand_float(1.0,2.0), 
//								rand_float(1.0,2.0), 
//								rand_float(1.0,2.0));
//		sphere_ptr->setCenter(center);	
//		sphere_ptr->setMaterial(matte_ptr);
//		grid_ptr->addObject(sphere_ptr);
//	}	
//
//	grid_ptr->setupCells();
//	addObject(grid_ptr);
//}

///////////////////////////////////
///Hall of mirrors
//////////////////////////////////
//void World::buildScene(int vres,int hres) 
//{
//	int num_samples = 1;
//	
//	viewPlane.setHRes(800);	  		
//	viewPlane.setVRes(800);        
//	viewPlane.setSamples(num_samples);
//	viewPlane.setMaxDepth(6);
//	
//	tracer = new Whitted(this);
//	ambientLight = new AmbientLight(false);
//	ambientLight->setIntensity(0.0);
//			
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
//	
//	pinhole_ptr->setEye(glm::vec3(7.5, 3, 9.5));
//	pinhole_ptr->setLookAt(glm::vec3(0));
//	pinhole_ptr->setViewPlaneDistance(300);
//	pinhole_ptr->computeUVW(); 
//	setCamera(pinhole_ptr);
//	
//	
//	// four point lights near the ceiling
//	// these don't use distance attenuation
//
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->setPosition(glm::vec3(10, 10, 0)); 
//	light_ptr1->setIntensity(2.0); 
//	light_ptr1->setUseShadows(true); 
//    addLight(light_ptr1);
//    
//    PointLight* light_ptr2 = new PointLight;
//	light_ptr2->setPosition(glm::vec3(0, 10, 10)); 
//	light_ptr2->setIntensity(2.0); 
//	light_ptr2->setUseShadows(true); 
//    addLight(light_ptr2);
//    
//    PointLight* light_ptr3 = new PointLight;
//	light_ptr3->setPosition(glm::vec3(-10, 10, 0)); 
//	light_ptr3->setIntensity(2.0); 
//	light_ptr3->setUseShadows(true); 
//    addLight(light_ptr3);
//    
//    PointLight* light_ptr4 = new PointLight;
//	light_ptr4->setPosition(glm::vec3(0, 10, -10)); 
//	light_ptr4->setIntensity(2.0); 
//	light_ptr4->setUseShadows(true); 
//    addLight(light_ptr4);
//
//		
//	// sphere
//	// this is the only reflective object with a direct illumination shading component
//	
//	Transparent* glass_ptr = new Transparent;
//	glass_ptr->setKSpecular(0.5);
//	glass_ptr->setExponent(2000.0);
//	glass_ptr->setIor(1.0);		
//	glass_ptr->setKReflective(0.1);
//	glass_ptr->setKTransparent(0.8);
//	
//	Sphere* sphere_ptr1 = new Sphere(glm::vec3(0.0, 4.5, 0.0), 4.0);
//	sphere_ptr1->setMaterial(glass_ptr);
//	addObject(sphere_ptr1);
//		
//	
//	// the walls, the ceiling, and the floor of the room are defined as planes
//	// the shape is a cube
//	
//	float room_size = 11.0;
//	
//	// floor  (-ve yw)
//	
//	Matte* matte_ptr1 = new Matte;
//	matte_ptr1->setKAmbient(0.1);   
//	matte_ptr1->setKDiffuse(0.50);
//	matte_ptr1->setColor(glm::vec3(0.25));     // medium grey
//	
//	Plane* floor_ptr = new Plane(glm::vec3(0, -room_size,  0), glm::vec3(0, 1, 0));
//	floor_ptr->setMaterial(matte_ptr1);        
//	addObject(floor_ptr);
//	
//	
//	// ceiling  (+ve yw)
//	
//	Matte* matte_ptr2 = new Matte;   
//	matte_ptr2->setKAmbient(0.1);   
//	matte_ptr2->setKDiffuse(0.50);
//	matte_ptr2->setColor(glm::vec3(0.25));
//	
//	Plane* ceiling_ptr = new Plane(glm::vec3(0, room_size,  0), glm::vec3(0, -1, 0));
//	ceiling_ptr->setMaterial(matte_ptr2);        
//	addObject(ceiling_ptr);
//	
//	
//	// back wall  (-ve zw)
//	
//	Matte* matte_ptr3 = new Matte;
//	matte_ptr3->setKAmbient(0.15); 
//	matte_ptr3->setKDiffuse(0.60);
//	matte_ptr3->setColor(glm::vec3(0.5, 0.75, 0.75));     // cyan
//	
//	Plane* backWall_ptr = new Plane(glm::vec3(0, 0,  -room_size), glm::vec3(0, 0, 1));
//	backWall_ptr->setMaterial(matte_ptr3);        
//	addObject(backWall_ptr);
//	
//	// front wall  (+ve zw)
//	
//	Plane* frontWall_ptr = new Plane(glm::vec3(0, 0,  room_size), glm::vec3(0, 0, -1));
//	frontWall_ptr->setMaterial(matte_ptr3);        
//	addObject(frontWall_ptr);
//	
//	// left wall  (-ve xw)
//	
//	Matte* matte_ptr4 = new Matte;
//	matte_ptr4->setKAmbient(0.15); 
//	matte_ptr4->setKDiffuse(0.60);
//	matte_ptr4->setColor(glm::vec3(0.71, 0.40, 0.20));   // orange
//	
//	Plane* leftWall_ptr = new Plane(glm::vec3(-room_size, 0, 0), glm::vec3(1, 0, 0));
//	leftWall_ptr->setMaterial(matte_ptr4);        
//	addObject(leftWall_ptr);
//	
//	// right wall  (+ve xw)
//	
//	Plane* rightWall_ptr = new Plane(glm::vec3(room_size, 0, 0), glm::vec3(-1, 0, 0));
//	rightWall_ptr->setMaterial(matte_ptr4);        
//	addObject(rightWall_ptr);
//	
//	
//	// mirrors on the walls
//	// the right wall has no mirror
//	
//	float mirror_size 	= 8;  	// the mirror size
//	float offset 		= 1.0;  // the mirror offset from the walls
//	
//	// mirror material
//	// this has no direct illumination and a slight green tint
//	
//	Reflective* reflective_ptr2 = new Reflective;			
//	reflective_ptr2->setKAmbient(0); 
//	reflective_ptr2->setKDiffuse(0);
//	reflective_ptr2->setColor(glm::vec3(0.0)); 
//	reflective_ptr2->setKSpecular(0);
//	reflective_ptr2->setKReflective(0.9);
//	reflective_ptr2->setReflectiveColor(glm::vec3(0.9, 1.0, 0.9));  // light green
//	
//	// back wall mirror  (-ve zw)
//	
//	glm::vec3 p0;
//	glm::vec3 a, b;
//	
//	p0 = glm::vec3(-mirror_size, -mirror_size, -(room_size - offset));
//	a = glm::vec3(2.0 * mirror_size, 0, 0);
//	b = glm::vec3(0, 2.0 * mirror_size, 0);
//	glm::vec3 n(0, 0, 1);
//	Rect* rectangle_ptr1 = new Rect(p0, a, b, n);
//	rectangle_ptr1->setMaterial(reflective_ptr2); 
//	addObject(rectangle_ptr1);
//	
//	
//	// front wall mirror  (+ve zw)
//	
//	p0 = glm::vec3(-mirror_size, -mirror_size, +(room_size - offset));
//	n = glm::vec3(0, 0, -1);
//	Rect* rectangle_ptr2 = new Rect(p0, a, b, n);
//	rectangle_ptr2->setMaterial(reflective_ptr2); 
//	addObject(rectangle_ptr2);
//	
//	
//	// left wall mirror  (-ve xw)
//	
//	p0 = glm::vec3(-(room_size - offset), -mirror_size, +mirror_size);
//	a = glm::vec3(0, 0, -2.0 * mirror_size);
//	n = glm::vec3(1, 0, 0);
//	Rect* rectangle_ptr3 = new Rect(p0, a, b, n);
//	rectangle_ptr3->setMaterial(reflective_ptr2); 
//	addObject(rectangle_ptr3);
//
//
//	// horizontal mirror underneath the sphere
//	// this has no direct illumination and a lemon color
//	
//	Reflective* reflective_ptr3 = new Reflective;			
//	reflective_ptr3->setKAmbient(0); 
//	reflective_ptr3->setKDiffuse(0);
//	reflective_ptr3->setColor(glm::vec3(0.0)); 
//	reflective_ptr3->setKSpecular(0);
//	reflective_ptr3->setKReflective(1);
//	reflective_ptr3->setReflectiveColor(glm::vec3(1, 1, 0.5));  // lemon
//	
//	float yw = -4.0;   // the yw location of the mirror
//	
//	p0 = glm::vec3(-mirror_size, yw, -mirror_size);
//	a = glm::vec3(0, 0, 2.0 * mirror_size);
//	b = glm::vec3(2.0 * mirror_size, 0, 0);
//	n = glm::vec3(0, 1, 0);
//	Rect* rectangle_ptr4 = new Rect(p0, a, b, n);
//	rectangle_ptr4->setMaterial(reflective_ptr3); 
//	addObject(rectangle_ptr4);
//}

//////////////////////////////////
///4 reflective spheres
//////////////////////////////////
//void World::buildScene(int vres,int hres) 
//{
//	int num_samples = 1;
//	
//	viewPlane.setHRes(800);  
//	viewPlane.setVRes(800);
//	viewPlane.setSamples(num_samples);
//	viewPlane.setMaxDepth(12);
//		
//	tracer = new Whitted(this);
//
//	AmbientLight* ambient_ptr = new AmbientLight(true);
//	ambient_ptr->setIntensity(0.5);
//	setAmbientLight(ambient_ptr);	
//					
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
//	pinhole_ptr->setEye(glm::vec3(0,0.05,0.0));  
//	pinhole_ptr->setLookAt(glm::vec3(0.0, 1.0,0.0));  
//	pinhole_ptr->setViewPlaneDistance(600.0);
//	pinhole_ptr->computeUVW(); 
//	setCamera(pinhole_ptr);
//	
//	
//	PointLight* light_ptr = new PointLight;
//	light_ptr->setPosition(glm::vec3(0, 20, 20));     
//	light_ptr->setIntensity(5.0); 
//	light_ptr->setUseShadows(false);
//	//addLight(light_ptr);	
//	
//	
//	// the four spheres
//		
//	float ka = 0.75;
//	float kd = 0.75;
//	float ks = 0.1;
//	float e = 20.0;
//	float kr = 1.0;
//	
//	Reflective* reflective_ptr1 = new Reflective;
//	reflective_ptr1->setKAmbient(ka); 
//	reflective_ptr1->setKDiffuse(kd); 
//	reflective_ptr1->setKSpecular(ks);  
//	reflective_ptr1->setColor(glm::vec3(0.168, 0.171, 0.009));    	// pink
//	reflective_ptr1->setExponent(e);
//	reflective_ptr1->setKReflective(kr);
//	
//	Sphere* sphere_ptr1 = new Sphere(glm::vec3(0.0, 1.414, 0.0), 0.866);
//	sphere_ptr1->setMaterial(reflective_ptr1);
//	addObject(sphere_ptr1);
//	
//	
//	Reflective* reflective_ptr2 = new Reflective;
//	reflective_ptr2->setKAmbient(ka); 
//	reflective_ptr2->setKDiffuse(kd); 
//	reflective_ptr2->setColor(glm::vec3(0.094, 0.243, 0.029));   	// green
//	reflective_ptr2->setKSpecular(ks);    
//	reflective_ptr2->setExponent(e);
//	reflective_ptr2->setKReflective(kr);
//	
//	Sphere* sphere_ptr2 = new Sphere(glm::vec3(0.0, 0.0, 1.0), 0.866);
//	sphere_ptr2->setMaterial(reflective_ptr2);
//	addObject(sphere_ptr2);
//	
//	
//	Reflective* reflective_ptr3 = new Reflective;
//	reflective_ptr3->setKAmbient(ka); 
//	reflective_ptr3->setKDiffuse(kd);
//	reflective_ptr3->setColor(glm::vec3(0.243, 0.018, 0.164));     	// red 
//	reflective_ptr3->setKSpecular(ks);    
//	reflective_ptr3->setExponent(e);
//	reflective_ptr3->setKReflective(kr);
//	
//	Sphere* sphere_ptr3 = new Sphere(glm::vec3(0.866, 0.0, -0.5), 0.866);
//	sphere_ptr3->setMaterial(reflective_ptr3);
//	addObject(sphere_ptr3);
//	
//	
//	Reflective* reflective_ptr4 = new Reflective;
//	reflective_ptr4->setKAmbient(ka); 
//	reflective_ptr4->setKDiffuse(kd); 
//	reflective_ptr4->setColor(glm::vec3(0.094, 0.1, 0.243));    		// blue
//	reflective_ptr4->setKSpecular(ks);    
//	reflective_ptr4->setExponent(e);
//	reflective_ptr4->setKReflective(kr);
//	
//	Sphere* sphere_ptr4 = new Sphere(glm::vec3(-0.866, 0.0, -0.5), 0.866);
//	sphere_ptr4->setMaterial(reflective_ptr4);
//	addObject(sphere_ptr4);
//}

//void World::buildScene(int vres,int hres)
//{
//	int num_samples = 1024;
//	
//	viewPlane.setHRes(600);	  		
//	viewPlane.setVRes(600);
//	viewPlane.setSamples(num_samples);		
//	viewPlane.setMaxDepth(6);			// for Figure 27.13(a)
////	vp.set_max_depth(4);			// for Figure 27.13(b)
////	vp.set_max_depth(5);			// for Figure 27.13(c)	
//	
//	backgroundColor = glm::vec3(0.0, 0.3, 0.25);
//	
//	tracer = new Whitted(this);
//	
//	AmbientLight* ambient_ptr = new AmbientLight(false);
//	ambient_ptr->setIntensity(0.25);
//	setAmbientLight(ambient_ptr);
//		
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
//	pinhole_ptr->setEye(glm::vec3(-8, 5.5, 40));   
//	pinhole_ptr->setLookAt(glm::vec3(1, 4, 0));    
//	pinhole_ptr->setViewPlaneDistance(2400.0);  
//	pinhole_ptr->computeUVW();     
//	setCamera(pinhole_ptr);
//	
//	
//	// point light 
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->setPosition(glm::vec3(40, 50, 0)); 
//	light_ptr1->setIntensity(4.5);
//	light_ptr1->setUseShadows(true);
//	addLight(light_ptr1);
//	
//
//	// point light 
//	
//	PointLight* light_ptr2 = new PointLight;
//	light_ptr2->setPosition(glm::vec3(-10, 20, 10)); 
//	light_ptr2->setIntensity(4.5);
//	light_ptr2->setUseShadows(true);
//	addLight(light_ptr2);
//	
//	
//	// directional light 
//	
//	DirectionalLight* light_ptr3 = new DirectionalLight;
//	light_ptr3->setDirection(glm::vec3(-1, 0, 0)); 
//	light_ptr3->setIntensity(4.5);
//	light_ptr3->setUseShadows(true);
//	addLight(light_ptr3);
//	
//	
//	// transparent sphere
//	
//	Transparent* glass_ptr = new Transparent;
//	glass_ptr->setKSpecular(0.5);
//	glass_ptr->setExponent(2000.0);
//	glass_ptr->setIor(1.75);		
//	glass_ptr->setKReflective(0.1);
//	glass_ptr->setKTransparent(01.0);
//	addMaterial(glass_ptr);
//	
//	/*Sphere* sphere_ptr1 = new Sphere(glm::vec3(0.0, 4.5, 0.0), 3.0);
//	sphere_ptr1->setMaterial(glass_ptr);
//	addObject(sphere_ptr1);*/
//
//	Box *box_ptr = new Box(glm::vec3(-2.0f,0.5f,-2.0f),glm::vec3(2.0f,6.5f,2.0f));
//	box_ptr->setMaterial(glass_ptr);
//	addObject(box_ptr);
//	
//	
//	// red sphere
//		
//	Reflective*	reflective_ptr = new Reflective;
//	reflective_ptr->setKAmbient(0.3);
//	reflective_ptr->setKDiffuse(0.3); 
//	reflective_ptr->setColor(glm::vec3(1.0,0.0,0.0)); 
//	reflective_ptr->setKSpecular(0.2);
//	reflective_ptr->setExponent(2000.0);
//	reflective_ptr->setKReflective(0.25);
//	addMaterial(reflective_ptr);
//	
//	Sphere* sphere_ptr2 = new Sphere(glm::vec3(4, 4, -6), 3);
//	sphere_ptr2->setMaterial(reflective_ptr);
//	addObject(sphere_ptr2);
//
//	Checker3D* checker_ptr = new Checker3D;
//	checker_ptr->setSize(4);
//	checker_ptr->setColor1(glm::vec3(0.75));  
//	checker_ptr->setColor2(glm::vec3(1.0f));
//	
//	SVMatte* sv_matte_ptr = new SVMatte;		
//	sv_matte_ptr->setKAmbient(0.5);
//	sv_matte_ptr->setKDiffuse(0.35);
//	sv_matte_ptr->setTexture(checker_ptr);	
//	addMaterial(sv_matte_ptr);
//	
//	// rectangle
//	
//	glm::vec3 p0(-20, 0, -100);
//	glm::vec3 a(0, 0, 120);
//	glm::vec3 b(40, 0, 0);
//	
//	Rect* rectangle_ptr = new Rect(p0, a, b); 
//	rectangle_ptr->setMaterial(sv_matte_ptr);
//	addObject(rectangle_ptr);		
//}

uint count = 00;

/////////////cloth scene/////////////
//void World::buildScene(int vres,int hres)
//{
//	int num_samples = 16;
//	
//	viewPlane.setHRes(800);	  		
//	viewPlane.setVRes(800);
//	viewPlane.setSamples(num_samples);		
//	viewPlane.setMaxDepth(6);
//
//	PointLight* light_ptr0 = new PointLight;
//	light_ptr0->setColor(glm::vec3(1.0));
//	light_ptr0->setIntensity(.75);
//	light_ptr0->setPosition(glm::vec3(-45.0,50.0,-28.0));
//	addLight(light_ptr0);
//
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->setColor(glm::vec3(1.0));
//	light_ptr1->setIntensity(.55);
//	light_ptr1->setPosition(glm::vec3(-40.0,42.0,-100.0));
//	addLight(light_ptr1);
//	
//	backgroundColor = glm::vec3(0.0, 0.0, 0.0);
//	
//	tracer = new Whitted(this);
//	
//	AmbientLight* ambient_ptr = new AmbientLight(false,1.0f,glm::vec3(1.0f));
//	setAmbientLight(ambient_ptr);
//		
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
//	//move from 12 to 17
//	float beta = (float)(count) / 100.0f;
//	float cameraX = lerp(beta,12.0f,17.0f);
//	pinhole_ptr->setEye(glm::vec3(17, 4, 9));   
//	pinhole_ptr->setLookAt(glm::vec3(-14.0f,5.5f,-60.0f));    
//	pinhole_ptr->setViewPlaneDistance(600.0);  
//	pinhole_ptr->computeUVW();     
//	setCamera(pinhole_ptr);
//
//	ImageTexture* woodTexture = new ImageTexture;
//	woodTexture->setImage(FileLoader::loadImage("redPlanks.png"));
//
//	ImageTexture* outside_ptr = new ImageTexture;
//	outside_ptr->setImage(FileLoader::loadImage("nightSky1.png"));
//
//	ImageTexture* picture_ptr = new ImageTexture;
//	picture_ptr->setImage(FileLoader::loadImage("TheCurseOfJamieKing.png"));
//
//	SVMatte *pictureMatte_ptr = new SVMatte;
//	pictureMatte_ptr->setTexture(picture_ptr);
//	pictureMatte_ptr->setKAmbient(0.35f);
//	pictureMatte_ptr->setKDiffuse(1.0f);
//	addMaterial(pictureMatte_ptr);
//
//	SVMatte *wood_matte_ptr = new SVMatte;
//	wood_matte_ptr->setTexture(woodTexture);
//	wood_matte_ptr->setKAmbient(0.35f);
//	wood_matte_ptr->setKDiffuse(1.0f);
//	addMaterial(wood_matte_ptr);
//
//	SVMatte *outsideMatte_ptr = new SVMatte;
//	outsideMatte_ptr->setTexture(outside_ptr);
//	outsideMatte_ptr->setKAmbient(0.70f);
//	outsideMatte_ptr->setKDiffuse(0.0f);
//	outsideMatte_ptr->setHasShadows(false);
//	addMaterial(outsideMatte_ptr);
//
//	Transparent* curtainMatte_ptr = new Transparent;			
//	curtainMatte_ptr->setKAmbient(0.35f); 
//	curtainMatte_ptr->setKDiffuse(1.0f);
//	curtainMatte_ptr->setKSpecular(0.80f);
//	curtainMatte_ptr->setExponent(300);
//	curtainMatte_ptr->setIor(1.0f);
//	curtainMatte_ptr->setKTransparent(0.05f);
//	curtainMatte_ptr->setColor(glm::vec3(0.3f, 0.2f, 0.91f));
//	addMaterial(curtainMatte_ptr);
//
//	Matte* frameMatte_ptr = new Matte;
//	frameMatte_ptr->setColor(glm::vec3(0.8f));
//	frameMatte_ptr->setKAmbient(0.35f);
//	frameMatte_ptr->setKDiffuse(1.0f);
//	addMaterial(frameMatte_ptr);
//
//	Dielectric* glassMatte_ptr = new Dielectric;
//	glassMatte_ptr->setKSpecular(0.7f);
//	glassMatte_ptr->setExponent(2000.0f);
//	glassMatte_ptr->setEtaOut(1.0f);
//	glassMatte_ptr->setEtaIn(1.5f);
//	glassMatte_ptr->setColorFilterIn(glm::vec3(0.65f,0.75f,0.85f));
//	glassMatte_ptr->setColorFilterOut(glm::vec3(1.0f));
//	addMaterial(glassMatte_ptr);
//
//	Grid* grid = new Grid;
//	grid->readSmoothUVTriangle("wall.rbn",glm::translate(0.0f,0.0f,-10.0f));
//	for(uint i=0;i<grid->numberOfMeshes;i++)
//		grid->setMaterial(wood_matte_ptr,i);
//	grid->setupCells();
//	addObject(grid);
//
//	Grid* grid0 = new Grid;
//	grid0->readSmoothUVTriangle("floor1.rbn",glm::translate(0.0f,0.0f,-45.0f));
//	for(uint i=0;i<grid0->numberOfMeshes;i++)
//	{
//			grid0->setMaterial(wood_matte_ptr,i);
//	}
//	grid0->setupCells();
//	addObject(grid0);
//
//	Grid* grid2 = new Grid;
//	grid2->readSmoothUVTriangle("wall.rbn",glm::rotate(90.0f,0.0f,1.0f,0.0f) * glm::translate(-5.0f,0.0f,0.0f));
//	for(uint i=0;i<grid2->numberOfMeshes;i++)
//		grid2->setMaterial(wood_matte_ptr,i);
//	grid2->setupCells();
//	addObject(grid2);
//
//	Grid* grid3 = new Grid;
//	grid3->readFlatTriangle("windowFrame.rbn",glm::translate(0.0f,0.0f,-10.0f));
//	for(uint i=0;i<grid3->numberOfMeshes;i++)
//		grid3->setMaterial(frameMatte_ptr,i);
//	grid3->setupCells();
//	addObject(grid3);
//
//	Grid* grid4 = new Grid;
//	grid4->readFlatTriangle("windowGlass.rbn",glm::translate(0.0f,0.0f,-10.0f));
//	for(uint i=0;i<grid4->numberOfMeshes;i++)
//		grid4->setMaterial(glassMatte_ptr,i);
//	grid4->setupCells();
//	grid4->setCastShadows(false);
//	addObject(grid4);
//
//	Grid* grid6 = new Grid;
//	grid6->readSmoothUVTriangle("outsideLayer1.rbn");
//	for(uint i=0;i<grid6->numberOfMeshes;i++)
//		grid6->setMaterial(outsideMatte_ptr,i);
//	grid6->setupCells();
//	addObject(grid6);
//
//	//moving curtain
//	Grid* grid1 = new Grid;
//	char* fileName = new char[33];
//	sprintf(fileName,"cloth scene\\clothModelL%04d.rbn",count);
//	grid1->readSmoothTriangle(fileName,glm::translate(0.0f,-1.5f,-10.0f));
//	delete [] fileName;
//	for(uint i=0;i<grid1->numberOfMeshes;i++)
//		grid1->setMaterial(curtainMatte_ptr,i);
//	grid1->setupCells();
//	addObject(grid1);
//
//	Grid* grid7 = new Grid;
//	fileName = new char[33];
//	sprintf(fileName,"cloth scene\\clothModelR%04d.rbn",count++);
//	grid7->readSmoothTriangle(fileName,glm::translate(0.0f,-1.5f,-10.0f));
//	delete [] fileName;
//	for(uint i=0;i<grid7->numberOfMeshes;i++)
//		grid7->setMaterial(curtainMatte_ptr,i);
//	grid7->setupCells();
//	addObject(grid7);
//
//	Grid* grid8 = new Grid;
//	grid8->readSmoothUVTriangle("picture.rbn",glm::translate(15.0f,13.0f,-20.0f)* glm::scale(glm::vec3(0.21f)));
//	for(uint i=0;i<grid8->numberOfMeshes;i++)
//		grid8->setMaterial(pictureMatte_ptr,i);
//	grid8->setupCells();
//	//addObject(grid8);
//
//	Grid* grid9 = new Grid;
//	grid9->readSmoothUVTriangle("pictureFrame.rbn",glm::translate(15.0f,13.0f,-20.0f) * glm::scale(glm::vec3(0.2f)));
//	for(uint i=0;i<grid9->numberOfMeshes;i++)
//		grid9->setMaterial(frameMatte_ptr,i);
//	grid9->setupCells();
//	//addObject(grid9);
//	std::string input;
//	std::cin>> input;
//}

///////////water scene//////////////////////////
//void World::buildScene(int vres,int hres)
//{
//	int num_samples = 16;
//	
//	viewPlane.setHRes(800);	  		
//	viewPlane.setVRes(800);
//	viewPlane.setSamples(num_samples);		
//	viewPlane.setMaxDepth(8);
//
//	tracer = new Whitted(this);
//	
//	AmbientLight* ambient_ptr = new AmbientLight(false,1.0f,glm::vec3(0.5f));
//	setAmbientLight(ambient_ptr);
//	
//	PointLight* light_ptr = new PointLight;
//	light_ptr->setPosition(glm::vec3(350, 150, 140));     
//	light_ptr->setIntensity(0.9); 
//	addLight(light_ptr);	
//
//	//rotate Camera start -120 80 -120 rotate 45 then rotate -90
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
//	float angle;
//	if(count < 300)
//		angle = lerp(count/300.0f,-45.0f,90.0f);
//	else
//	{
//		if(count > 400)
//			angle = lerp((400-300)/300.0f,90.0f,0.0f);
//		else
//			angle = lerp((count-300)/300.0f,90.0f,0.0f);
//	}
//
//	/*float lerpValueX;
//	float lerpValueY;
//	float lerpValueZ;
//	if(count < 200)
//	{
//		lerpValueX = lerp(count/200.0f, 40.0f, 30.0f);
//		lerpValueY = lerp(count/200.0f,-40.0f, -90.0f);
//		lerpValueZ = lerp(count/200.0f,-80.0f, -60.0f);
//	}
//	else
//	{
//		lerpValueX	= 30.0f;
//		lerpValueY	= -90.0f;
//		lerpValueZ	= -60.0f;
//	}*/
//
//	glm::vec3 eyePosition = glm::vec3(glm::vec4(-120.0f,70.0f,120.0f,0.0f) * glm::rotate(angle,0.0f,1.0f,0.0f));
//	pinhole_ptr->setEye(eyePosition);   
//	pinhole_ptr->setLookAt(glm::vec3(0.0f,-20.0f,0.0f));    
//	pinhole_ptr->setViewPlaneDistance(800.0f);  
//	pinhole_ptr->computeUVW();     
//	setCamera(pinhole_ptr);
//
//	ImageTexture* groundTexture = new ImageTexture;
//	groundTexture->setImage(FileLoader::loadImage("stone.png"));
//
//	SVMatte* groundMatte = new SVMatte;
//	groundMatte->setTexture(groundTexture);
//	groundMatte->setKAmbient(1.0f);
//	groundMatte->setKDiffuse(1.0f);
//	addMaterial(groundMatte);
//
//	Dielectric* waterAirMatte_ptr = new Dielectric;
//	waterAirMatte_ptr->setKSpecular(0.7f);
//	waterAirMatte_ptr->setExponent(200.0f);
//	waterAirMatte_ptr->setEtaOut(1.0f);
//	waterAirMatte_ptr->setEtaIn(1.3f);
//	waterAirMatte_ptr->setColorFilterIn(glm::vec3(0.75f,0.85f,0.95f));
//	waterAirMatte_ptr->setColorFilterOut(glm::vec3(1.0f));
//	addMaterial(waterAirMatte_ptr);
//
//	char* fileName = new char[35];
//	sprintf(fileName,"water scene\\rain%04d.rbn",count);
//	Grid* grid2 = FileLoader::loadSphereFile(fileName,glm::translate(-10.0f,-6.5f,0.0f) * glm::scale(glm::vec3(3.5f,3.5f,4.35f)));
//	delete [] fileName;
//	((Compound*)grid2)->setMaterial(waterAirMatte_ptr);
//	grid2->setupCells();
//	addObject(grid2);
//
//	Grid* grid = new Grid;
//	fileName = new char[35];
//	sprintf(fileName,"water scene\\waterModel%04d.rbn",count++);
//	grid->readSmoothTriangle(fileName,glm::translate(-10.0f,-6.5f,0.0f) * glm::scale(glm::vec3(3.5f,3.5f,4.35f)));
//	delete [] fileName;
//	for(uint i=0;i<grid->numberOfMeshes;i++)
//		grid->setMaterial(waterAirMatte_ptr,i);
//	grid->setupCells();
//	grid->setCastShadows(false);
//	addObject(grid);
//
//	Grid* grid1 = new Grid;
//	grid1->readSmoothUVTriangle("groundForPuddle.rbn",glm::scale(glm::vec3(0.87f)));
//	for(uint i=0;i<grid1->numberOfMeshes;i++)
//		grid1->setMaterial(groundMatte,i);
//	grid1->setupCells();
//	addObject(grid1);
//}

//////glass of water/////////////
//void World::buildScene(int vres,int hres) 
//{
//	int num_samples = 16;
//	
//	viewPlane.setHRes(600);	  		
//	viewPlane.setVRes(600);
//	viewPlane.setSamples(num_samples);
//	viewPlane.setMaxDepth(10);
//	
//	backgroundColor = glm::vec3(0.5);
//	
//	tracer = new Whitted(this);
//	
//	AmbientLight* ambient_ptr = new AmbientLight(false);
//	ambient_ptr->setIntensity(0.5);
//	setAmbientLight(ambient_ptr);
//	
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
//	pinhole_ptr->setEye(glm::vec3(5, 6, 10)); 
//	pinhole_ptr->setLookAt(glm::vec3(0, 1, 0)); 
//	pinhole_ptr->setViewPlaneDistance(2000.0);			
//	pinhole_ptr->computeUVW();     
//	setCamera(pinhole_ptr);
//	
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->setPosition(glm::vec3(40, 50, 30)); 
//	light_ptr1->setIntensity(3.0);    
//	light_ptr1->setUseShadows(true);
//	addLight(light_ptr1);
//
//
//	// materials for the glass of water
//	
//	// glass-air boundary
//	
//	glm::vec3 glass_color(0.65, 1, 0.75);   
//	glm::vec3 water_color(1, 0.25, 1);       
//	
//	Dielectric* glass_ptr = new Dielectric;
//	glass_ptr->setEtaIn(1.50);			// glass  
//	glass_ptr->setEtaOut(1.0);			// air
//	glass_ptr->setColorFilterIn(glass_color);
//	glass_ptr->setColorFilterOut(glm::vec3(1.0));  
//	
//	// water-air boundary
//	
//	Dielectric* water_ptr = new Dielectric;
//	water_ptr->setEtaIn(1.33);			// water
//	water_ptr->setEtaOut(1.0);			// air
//	water_ptr->setColorFilterIn(water_color);
//	water_ptr->setColorFilterOut(glm::vec3(1.0));
//
//	// water-glass boundary
//
//	Dielectric* dielectric_ptr = new Dielectric;
//	dielectric_ptr->setEtaIn(1.33); 		// water
//	dielectric_ptr->setEtaOut(1.50); 		// glass
//	dielectric_ptr->setColorFilterIn(water_color);
//	dielectric_ptr->setColorFilterOut(glass_color);
//	
//	
//	// Define the GlassOfWater object
//	// The parameters below are the default values, but using the constructor that
//	// takes these as arguments makes it easier to experiment with different values
//	
//	double height 			= 2.0;
//	double inner_radius 	= 0.9;
//	double wall_thickness 	= 0.1;  
//	double base_thickness 	= 0.3;
//	double water_height 	= 1.5;
//	double meniscus_radius 	= 0.1;
//	
//	GlassOfWater* glass_of_water_ptr = new GlassOfWater(height,
//														inner_radius,
//														wall_thickness,  
//														base_thickness,
//														water_height,
//														meniscus_radius);
//	
//	glass_of_water_ptr->setGlassAirMaterial(glass_ptr);
//	glass_of_water_ptr->setWaterAirMaterial(water_ptr);
//	glass_of_water_ptr->setWaterGlassMaterial(dielectric_ptr);
//	addObject(glass_of_water_ptr);
//	
//	// define the straw
//	
//	Matte* matte_ptr = new Matte;
//	matte_ptr->setColor(glm::vec3(1, 1, 0));  			
//	matte_ptr->setKAmbient(0.25);	
//	matte_ptr->setKDiffuse(0.65);
//	matte_ptr->setHasShadows(false);  // there are no shadows cast on the straw
//	
//	Instance* straw_ptr = new Instance(new Cylinder(-1.2f, 1.7f, 0.05f));
//	straw_ptr->setMaterial(matte_ptr);
//	straw_ptr->setTransform(glm::translate(0.0f, 1.25f, 0.0f) * glm::rotate(0.0f,0.0f,0.0f,1.0f));
//	addObject(straw_ptr);
//	
//	// ground plane
//
//	Checker3D* checker_ptr = new Checker3D;
//	checker_ptr->setSize(0.5); 
//	checker_ptr->setColor1(glm::vec3(0.75f)); 
//	checker_ptr->setColor2(glm::vec3(1.0f));
//	
//	SVMatte* sv_matte_ptr = new SVMatte;		
//	sv_matte_ptr->setKAmbient(0.5);
//	sv_matte_ptr->setKDiffuse(0.75);
//	sv_matte_ptr->setTexture(checker_ptr);
//	
//	Plane* plane_ptr = new Plane(glm::vec3(0, -0.01, 0), glm::vec3(0, 1, 0));
//	plane_ptr->setMaterial(sv_matte_ptr);
//	addObject(plane_ptr);
//
//	////////28.11//////////
//}

////////////// area lighting//////////
//void World::buildScene(int vres,int hres)
//{
//	int num_samples = 64;  
//	
//	Sampler* sampler_ptr = new MultiJittered(num_samples);
//
//	viewPlane.setHRes(600);
//	viewPlane.setVRes(600);
//	viewPlane.setMaxDepth(0);
//	viewPlane.setSampler(sampler_ptr);	
//
//	backgroundColor = glm::vec3(0.5f);
//
//	AmbientLight* ambient_ptr = new AmbientLight(true,0.1f,glm::vec3(1.0f));
//	setAmbientLight(ambient_ptr);
//
//	tracer = new AreaLighting(this);
//
//	PinHoleCamera* camera = new PinHoleCamera;
//	camera->setEye(glm::vec3(-20, 10, 20));
//	camera->setLookAt(glm::vec3(0, 2, 0)); 	
//	camera->setViewPlaneDistance(1080);          
//	camera->computeUVW();     
//	setCamera(camera); 
//
//	
//	Emissive* emissive_ptr = new Emissive;
//	emissive_ptr->setRadianceScale(20.0f);   
//	emissive_ptr->setColor(glm::vec3(1.0f));
//
//	// sphere for a spherical light
//	// the center and radius are the same as for the disk
//
//	float width = 4.0;
//	float radius = 0.56 * width;
//	glm::vec3 center(0.0, 17.0, -7.0);	
//	glm::vec3 normal(0, 0, 1);
//	
//	Sphere* sphere_ptr = new Sphere(center, radius);
//	sphere_ptr->setMaterial(emissive_ptr);
//	sphere_ptr->setSampler(sampler_ptr);
//	sphere_ptr->setCastShadows(false);
//	addObject(sphere_ptr);
//
//	/*Disk* disk_ptr = new Disk(center, normal, radius);
//	disk_ptr->setMaterial(emissive_ptr);
//	disk_ptr->setSampler(sampler_ptr);
//	disk_ptr->setCastShadows(false);
//	disk_ptr->compueUVW();
//	addObject(disk_ptr);*/
//	
//	AreaLight* area_light_ptr = new AreaLight(true,glm::vec3(1.0),1.0f);
//	area_light_ptr->setObject(sphere_ptr);
//	area_light_ptr->setUseShadows(true);
//	addLight(area_light_ptr);
//	
//	
//	// Four axis aligned boxes
//		
//	float box_width 	= 1.0; 		// x dimension
//	float box_depth 	= 1.0; 		// z dimension
//	float box_height 	= 4.5; 		// y dimension
//	float gap			= 3.0; 
//	
//	Matte* matte_ptr1 = new Matte;			
//	matte_ptr1->setKAmbient(0.25); 
//	matte_ptr1->setKDiffuse(0.75);
//	matte_ptr1->setColor(glm::vec3(0.4, 0.7, 0.4));     // green
//	
//	glm::vec3 min = glm::vec3(- 1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth);
//	glm::vec3 max = glm::vec3(-1.5 * gap  - box_width, box_height, 0.5 * box_depth);
//
//	Sphere* sphere = new Sphere(min,2.0f);
//	sphere->setMaterial(matte_ptr1);
//	addObject(sphere);
//	
//	Sphere* box_ptr1 = new Sphere(glm::vec3(- 0.5 * gap - box_width, 0.0, -0.5 * box_depth), 
//							2.0f); 
//	box_ptr1->setMaterial(matte_ptr1);
//	addObject(box_ptr1);
//		
//	Sphere* box_ptr2 = new Sphere(glm::vec3(0.5 * gap, 0.0, -0.5 * box_depth), 
//							2.0f);
//	box_ptr2->setMaterial(matte_ptr1);
//	addObject(box_ptr2);
//	
//	Sphere* box_ptr3 = new Sphere(glm::vec3(1.5 * gap + box_width, 0.0, -0.5 * box_depth), 
//							2.0f);
//	box_ptr3->setMaterial(matte_ptr1);
//	addObject(box_ptr3);
//
//		
//	// ground plane
//	
//	Matte* matte_ptr2 = new Matte;			
//	matte_ptr2->setKAmbient(0.1); 
//	matte_ptr2->setKDiffuse(0.90);
//	matte_ptr2->setColor(glm::vec3(1.0));
//		
//	Plane* plane_ptr = new Plane(glm::vec3(0.0), glm::vec3(0, 1, 0)); 
//	plane_ptr->setMaterial(matte_ptr2);
//	addObject(plane_ptr);
//}


////////////////////////////
/////hair scene
///////////////////////////
//void World::buildScene(int vres,int hres) 
//{
//	int num_samples = 16;
//	
//	viewPlane.setHRes(800);	  		
//	viewPlane.setVRes(800);
//	viewPlane.setSamples(num_samples);
//	viewPlane.setMaxDepth(3);
//	
//	backgroundColor = glm::vec3(0.5);
//	
//	tracer = new Whitted(this);
//	
//	AmbientLight* ambient_ptr = new AmbientLight(false);
//	ambient_ptr->setIntensity(0.75);
//	setAmbientLight(ambient_ptr);
//	
//	glm::vec3 eyePosition(22,1,18);
//
//	if(count > 100)
//	{
//		float rotation = lerp(float(count - 100.0f) / 400.0f,0.0f,360.0f);
//		eyePosition = glm::vec3(glm::vec4(eyePosition,0.0f) * glm::rotate(rotation,0.0f,1.0f,0.0f));
//	}
//
//
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
//	pinhole_ptr->setEye(eyePosition); 
//	pinhole_ptr->setLookAt(glm::vec3(0, -10, 0)); 
//	pinhole_ptr->setViewPlaneDistance(800.0);			
//	pinhole_ptr->computeUVW();     
//	setCamera(pinhole_ptr);
//	
//	PointLight* light_ptr = new PointLight;
//	light_ptr->setPosition(glm::vec3(20, 15, 15)); 
//	light_ptr->setIntensity(2.0);    
//	light_ptr->setUseShadows(true);
//	addLight(light_ptr);
//	
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->setPosition(glm::vec3(-20, 15, -15)); 
//	light_ptr1->setIntensity(2.0);    
//	light_ptr1->setUseShadows(true);
//	addLight(light_ptr1);
//
//	Phong* hair_matte_ptr = new Phong;
//	hair_matte_ptr->setColor(glm::vec3(116/255.0f,42/255.0f,15/255.0f));
//	hair_matte_ptr->setExponent(500.0f);
//	hair_matte_ptr->setKAmbient(0.3f);
//	hair_matte_ptr->setKDiffuse(0.7f);
//	hair_matte_ptr->setKSpecular(1.0f);
//	addMaterial(hair_matte_ptr);
//
//	Phong* skin_matte_ptr = new Phong;
//	skin_matte_ptr->setColor(glm::vec3(1.0f,220/255.0f,178/255.0f));
//	skin_matte_ptr->setExponent(500.0f);
//	skin_matte_ptr->setKAmbient(0.3f);
//	skin_matte_ptr->setKDiffuse(0.5f);
//	skin_matte_ptr->setKSpecular(1.0f);
//	addMaterial(skin_matte_ptr);
//
//	Grid* grid1 = new Grid;
//	grid1->readSmoothTriangle("headWithBody.rbn",glm::translate(0.0f, -9.0f, 0.1f) * glm::scale(glm::vec3(0.1f,0.1f,0.09f)));
//	for(uint i=0;i<grid1->numberOfMeshes;i++)
//		grid1->setMaterial(skin_matte_ptr,i);
//	grid1->setupCells();
//	addObject(grid1);
//
//	char* fileName = new char[35];
//	sprintf(fileName,"hair scene\\hair%04d.rbn",count++);
//	uint size;
//	Grid** grid2 = FileLoader::loadCylinderFile(fileName,size);
//	delete [] fileName;
//	for(uint i=0;i<size;i++)
//	{
//		grid2[i]->setMaterial(hair_matte_ptr,0);
//		grid2[i]->setupCells();
//		addObject(grid2[i]);
//	}
//}

///////////Plane//////////
//void World::buildScene(int vres,int hres)
//{
//	int num_samples = 8;
//	
//	viewPlane.setHRes(hres);	  		
//	viewPlane.setVRes(vres);
//	viewPlane.setSamples(num_samples);		
//	viewPlane.setMaxDepth(6);
//
//	PointLight* light_ptr0 = new PointLight;
//	light_ptr0->setColor(glm::vec3(1.0));
//	light_ptr0->setIntensity(.75);
//	light_ptr0->setPosition(glm::vec3(-45.0,50.0,-28.0));
//	addLight(light_ptr0);
//
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->setColor(glm::vec3(1.0));
//	light_ptr1->setIntensity(.55);
//	light_ptr1->setPosition(glm::vec3(-40.0,42.0,-100.0));
//	addLight(light_ptr1);
//	
//	backgroundColor = glm::vec3(0.0, 0.0, 0.0);
//	
//	tracer = new Whitted(this);
//	
//	AmbientLight* ambient_ptr = new AmbientLight(false,1.0f,glm::vec3(1.0f));
//	setAmbientLight(ambient_ptr);
//		
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
//	//move from 12 to 17
//	float beta = (float)(count) / 100.0f;
//	float cameraX = lerp(beta,12.0f,17.0f);
//	pinhole_ptr->setEye(glm::vec3(1200, 400, 1400));   
//	pinhole_ptr->setLookAt(glm::vec3(0,0.0f,0.0f));    
//	pinhole_ptr->setViewPlaneDistance(1200.0);  
//	pinhole_ptr->computeUVW();     
//	setCamera(pinhole_ptr);
//
//	ImageTexture* woodTexture = new ImageTexture;
//	woodTexture->setImage(FileLoader::loadImage("diff.png"));
//
//	SVMatte *wood_matte_ptr = new SVMatte;
//	wood_matte_ptr->setTexture(woodTexture);
//	wood_matte_ptr->setKAmbient(0.35f);
//	wood_matte_ptr->setKDiffuse(1.0f);
//	addMaterial(wood_matte_ptr);
//
//	Dielectric* glassMatte_ptr = new Dielectric;
//	glassMatte_ptr->setKSpecular(0.7f);
//	glassMatte_ptr->setExponent(2000.0f);
//	glassMatte_ptr->setEtaOut(1.0f);
//	glassMatte_ptr->setEtaIn(1.5f);
//	glassMatte_ptr->setColorFilterIn(glm::vec3(0.65f,0.75f,0.85f));
//	glassMatte_ptr->setColorFilterOut(glm::vec3(1.0f));
//	addMaterial(glassMatte_ptr);
//
//	Grid* grid = new Grid;
//	grid->readFlatUVTriangle("planeBody.rbn",glm::scale(2.0f,2.0f,2.0f));
//	for(uint i=0;i<grid->numberOfMeshes;i++)
//		grid->setMaterial(wood_matte_ptr,i);
//	grid->setupCells();
//	addObject(grid);
//
//	Grid* grid1 = new Grid;
//	grid1->readFlatUVTriangle("planeNose.rbn",glm::scale(2.0f,2.0f,2.0f));
//	for(uint i=0;i<grid1->numberOfMeshes;i++)
//		grid1->setMaterial(wood_matte_ptr,i);
//	grid1->setupCells();
//	addObject(grid1);
//
//	Grid* grid0 = new Grid;
//	grid0->readSmoothTriangle("planeGlass.rbn",glm::scale(2.0f,2.0f,2.0f));
//	for(uint i=0;i<grid0->numberOfMeshes;i++)
//			grid0->setMaterial(glassMatte_ptr,i);
//	grid0->setupCells();
//	addObject(grid0);
//
//	Checker3D* checker_ptr = new Checker3D;
//	checker_ptr->setSize(500.0); 
//	checker_ptr->setColor1(glm::vec3(0.75f)); 
//	checker_ptr->setColor2(glm::vec3(1.0f));
//	
//	SVMatte* sv_matte_ptr = new SVMatte;		
//	sv_matte_ptr->setKAmbient(0.5);
//	sv_matte_ptr->setKDiffuse(0.75);
//	sv_matte_ptr->setTexture(checker_ptr);
//	
//	Plane* plane_ptr = new Plane(glm::vec3(0, -0.01, 0), glm::vec3(0, 1, 0));
//	plane_ptr->setMaterial(sv_matte_ptr);
//	addObject(plane_ptr);
//}

void World::buildScene(int vres,int hres)
{
	int num_samples = 16;
	
	viewPlane.setHRes(hres);	  		
	viewPlane.setVRes(vres);
	viewPlane.setSamples(num_samples);		
	viewPlane.setMaxDepth(12);

	PointLight* light_ptr0 = new PointLight;
	light_ptr0->setColor(glm::vec3(1.0));
	light_ptr0->setIntensity(.75);
	light_ptr0->setPosition(glm::vec3(-45.0,50.0,-28.0));
	addLight(light_ptr0);

	PointLight* light_ptr1 = new PointLight;
	light_ptr1->setColor(glm::vec3(1.0));
	light_ptr1->setIntensity(.55);
	light_ptr1->setPosition(glm::vec3(-40.0,42.0,-100.0));
	addLight(light_ptr1);
	
	backgroundColor = glm::vec3(0.0, 0.0, 0.0);
	
	tracer = new Whitted(this);
	
	AmbientLight* ambient_ptr = new AmbientLight(false,1.0f,glm::vec3(1.0f));
	setAmbientLight(ambient_ptr);
		
	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
	//move from 12 to 17
	float beta = (float)(count) / 100.0f;
	float cameraX = lerp(beta,12.0f,17.0f);
	pinhole_ptr->setEye(glm::vec3(100, 80, -200));   
	pinhole_ptr->setLookAt(glm::vec3(0,30.0f,0.0f));    
	pinhole_ptr->setViewPlaneDistance(1200.0);  
	pinhole_ptr->computeUVW();     
	setCamera(pinhole_ptr);

	float ka = 0.75;
	float kd = 0.75;
	float ks = 0.1;
	float e = 20.0;
	float kr = 1.0;

	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->setKAmbient(ka); 
	reflective_ptr1->setKDiffuse(kd); 
	reflective_ptr1->setKSpecular(ks);  
	reflective_ptr1->setColor(glm::vec3(0.168, 0.171, 0.009));    	// pink
	reflective_ptr1->setExponent(e);
	reflective_ptr1->setKReflective(kr);

	Grid* grid = new Grid;
	grid->readSmoothTriangle("accessories.rbn",glm::scale(5.0f,5.0f,5.0f) * glm::translate(glm::vec3(0,10,0)));
	for(uint i=0;i<grid->numberOfMeshes;i++)
		grid->setMaterial(reflective_ptr1,i);
	grid->setupCells();
	addObject(grid);

	Grid* grid1 = new Grid;
	grid1->readSmoothTriangle("helmetBase.rbn",glm::scale(5.0f,5.0f,5.0f) * glm::translate(glm::vec3(0,10,0)));
	for(uint i=0;i<grid1->numberOfMeshes;i++)
		grid1->setMaterial(reflective_ptr1,i);
	grid1->setupCells();
	addObject(grid1);

	Grid* grid2 = new Grid;
	grid2->readSmoothTriangle("helmetBottom.rbn",glm::scale(.5f,0.5f,0.5f));
	for(uint i=0;i<grid2->numberOfMeshes;i++)
		grid2->setMaterial(reflective_ptr1,i);
	grid2->setupCells();
	addObject(grid2);

	Grid* grid3 = new Grid;
	grid3->readSmoothTriangle("topVisor.rbn",glm::scale(5.0f,5.0f,5.0f) * glm::translate(glm::vec3(0,10,0)));
	for(uint i=0;i<grid3->numberOfMeshes;i++)
		grid3->setMaterial(reflective_ptr1,i);
	grid3->setupCells();
	addObject(grid3);

	Grid* grid4 = new Grid;
	grid4->readSmoothTriangle("visorPart2.rbn",glm::scale(5.0f,5.0f,5.0f) * glm::translate(glm::vec3(0,10,0)));
	for(uint i=0;i<grid4->numberOfMeshes;i++)
		grid4->setMaterial(reflective_ptr1,i);
	grid4->setupCells();
	addObject(grid4);

	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->setSize(100.0); 
	checker_ptr->setColor1(glm::vec3(0.75f)); 
	checker_ptr->setColor2(glm::vec3(1.0f));
	
	SVMatte* sv_matte_ptr = new SVMatte;		
	sv_matte_ptr->setKAmbient(0.5);
	sv_matte_ptr->setKDiffuse(0.75);
	sv_matte_ptr->setTexture(checker_ptr);
	
	Plane* plane_ptr = new Plane(glm::vec3(0, -0.01, 0), glm::vec3(0, 1, 0));
	plane_ptr->setMaterial(sv_matte_ptr);
	addObject(plane_ptr);
}

//void World::buildScene(int vres,int hres)
//{
//	int num_samples = 8;
//	
//	viewPlane.setHRes(hres);	  		
//	viewPlane.setVRes(vres);
//	viewPlane.setSamples(num_samples);		
//	viewPlane.setMaxDepth(12);
//
//	PointLight* light_ptr0 = new PointLight;
//	light_ptr0->setColor(glm::vec3(1.0));
//	light_ptr0->setIntensity(.75);
//	light_ptr0->setPosition(glm::vec3(-45.0,50.0,-28.0));
//	addLight(light_ptr0);
//
//	PointLight* light_ptr1 = new PointLight;
//	light_ptr1->setColor(glm::vec3(1.0));
//	light_ptr1->setIntensity(.55);
//	light_ptr1->setPosition(glm::vec3(-40.0,42.0,-100.0));
//	addLight(light_ptr1);
//	
//	backgroundColor = glm::vec3(0.0, 0.0, 0.0);
//	
//	tracer = new Whitted(this);
//	
//	AmbientLight* ambient_ptr = new AmbientLight(false,1.0f,glm::vec3(1.0f));
//	setAmbientLight(ambient_ptr);
//		
//	PinHoleCamera* pinhole_ptr = new PinHoleCamera;
//	//move from 12 to 17
//	float beta = (float)(count) / 100.0f;
//	float cameraX = lerp(beta,12.0f,17.0f);
//	pinhole_ptr->setEye(glm::vec3(600, 500, 1200));   
//	pinhole_ptr->setLookAt(glm::vec3(0,0.0f,0.0f));    
//	pinhole_ptr->setViewPlaneDistance(1200.0);  
//	pinhole_ptr->computeUVW();     
//	setCamera(pinhole_ptr);
//
//	float ka = 0.75;
//	float kd = 0.75;
//	float ks = 0.1;
//	float e = 20.0;
//	float kr = 1.0;
//
//	Reflective* reflective_ptr1 = new Reflective;
//	reflective_ptr1->setKAmbient(ka); 
//	reflective_ptr1->setKDiffuse(kd); 
//	reflective_ptr1->setKSpecular(ks);  
//	reflective_ptr1->setColor(glm::vec3(0.168, 0.171, 0.009));    	// pink
//	reflective_ptr1->setExponent(e);
//	reflective_ptr1->setKReflective(kr);
//
//	Grid* grid = new Grid;
//	grid->readSmoothTriangle("blackAccessories.rbn",glm::translate(glm::vec3(0,10,0)));
//	for(uint i=0;i<grid->numberOfMeshes;i++)
//		grid->setMaterial(reflective_ptr1,i);
//	grid->setupCells();
//	addObject(grid);
//
//	Grid* grid1 = new Grid;
//	grid1->readSmoothTriangle("body.rbn",glm::translate(glm::vec3(0,10,0)));
//	for(uint i=0;i<grid1->numberOfMeshes;i++)
//		grid1->setMaterial(reflective_ptr1,i);
//	grid1->setupCells();
//	addObject(grid1);
//
//	Grid* grid2 = new Grid;
//	grid2->readSmoothTriangle("guitarHead.rbn",glm::translate(glm::vec3(0,10,0)));
//	for(uint i=0;i<grid2->numberOfMeshes;i++)
//		grid2->setMaterial(reflective_ptr1,i);
//	grid2->setupCells();
//	addObject(grid2);
//
//	Grid* grid3 = new Grid;
//	grid3->readSmoothTriangle("screws.rbn",glm::translate(glm::vec3(0,10,0)));
//	for(uint i=0;i<grid3->numberOfMeshes;i++)
//		grid3->setMaterial(reflective_ptr1,i);
//	grid3->setupCells();
//	addObject(grid3);
//
//	Grid* grid4 = new Grid;
//	grid4->readSmoothTriangle("shineyMetalParts.rbn",glm::translate(glm::vec3(0,10,0)));
//	for(uint i=0;i<grid4->numberOfMeshes;i++)
//		grid4->setMaterial(reflective_ptr1,i);
//	grid4->setupCells();
//	addObject(grid4);
//
//	Grid* grid5 = new Grid;
//	grid5->readSmoothTriangle("greyParts.rbn",glm::translate(glm::vec3(0,10,0)));
//	for(uint i=0;i<grid5->numberOfMeshes;i++)
//		grid5->setMaterial(reflective_ptr1,i);
//	grid5->setupCells();
//	addObject(grid5);
//
//	Grid* grid6 = new Grid;
//	grid6->readSmoothTriangle("strings.rbn",glm::translate(glm::vec3(0,10,0)));
//	for(uint i=0;i<grid6->numberOfMeshes;i++)
//		grid6->setMaterial(reflective_ptr1,i);
//	grid6->setupCells();
//	addObject(grid6);
//
//	Checker3D* checker_ptr = new Checker3D;
//	checker_ptr->setSize(100.0); 
//	checker_ptr->setColor1(glm::vec3(0.75f)); 
//	checker_ptr->setColor2(glm::vec3(1.0f));
//	
//	SVMatte* sv_matte_ptr = new SVMatte;		
//	sv_matte_ptr->setKAmbient(0.5);
//	sv_matte_ptr->setKDiffuse(0.75);
//	sv_matte_ptr->setTexture(checker_ptr);
//	
//	Plane* plane_ptr = new Plane(glm::vec3(0, -0.01, 0), glm::vec3(0, 1, 0));
//	plane_ptr->setMaterial(sv_matte_ptr);
//	addObject(plane_ptr);
//}