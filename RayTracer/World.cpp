#include "World.h"
#include "Ray.h"
#include "IDrawer.h"
#include "GeometricObject.h"
#include "HelperFunctions.h"
#include "Sampler.h"
#include "Tracer.h"
#include "DebugMemory.h"
#include "Camera.h"
#include "Light.h"
#include "Texture.h"
#include "Material.h"
#include "BRDF.h"
#include "BTDF.h"

World::World()
	:viewPlane(10,10,1.0,1.0),backgroundColor(0.0),camera(NULL),ambientLight(NULL),
	tracer(NULL),showOutOfGamut(false),finished(false)
{

}

void World::displayPixel(const int row, const int column, const glm::vec3& pixelColor) const
{
	glm::vec3 mappedColor;
	if(showOutOfGamut)
		mappedColor = clampToColor(pixelColor);
	else
		mappedColor = maxToOne(pixelColor);

	if(viewPlane.getGamma() != 1.0)
	{
		mappedColor.x = pow(mappedColor.x,viewPlane.getInvGamma());
		mappedColor.y = pow(mappedColor.y,viewPlane.getInvGamma());
		mappedColor.z = pow(mappedColor.z,viewPlane.getInvGamma());
	}
	
	drawer->displayPixel(column,row,mappedColor);
}


void World::init(IDrawer* drawer,int vres, int hres)
{
	buildScene(vres,hres);
	this->drawer = drawer;
	drawer->setHRes(viewPlane.getHRes());
	drawer->setVRes(viewPlane.getVRes());
}

void World::renderScene() const
{
	glm::vec3 pixelColor;

	Ray ray(glm::vec3(0.0),glm::vec3(0.0,0.0,-1.0));
	float zw = 100;
	glm::vec2 samplePoint;
	glm::vec2 pixelPoint;

	for(int r=0;r<viewPlane.getVRes();r++)//up
	{
		for(int c=0;c<viewPlane.getHRes();c++)//across
		{
			pixelColor = glm::vec3(1.0);
			for(uint j=0;j<viewPlane.getNumSamples();j++)
			{
				samplePoint = viewPlane.getSampler()->sampleUnitSquare();
				pixelPoint.x = viewPlane.getPixelSize() * (c - 0.5 * viewPlane.getHRes() + samplePoint.x);
				pixelPoint.y = viewPlane.getPixelSize() * (-r + 0.5 * viewPlane.getVRes() + samplePoint.y);
				ray.setOrigin(glm::vec3(pixelPoint.x,pixelPoint.y,zw));
				pixelColor += tracer->traceRay(ray);
			}	
			pixelColor /= viewPlane.getNumSamples();
			displayPixel(c,r,pixelColor);

		}
	}
	drawer->painting = false;
}

void World::renderPerspective() const
{
	//change these to change perspective
	float eye = 100.0;
	float eyeDistanceFromViewPlane = 10.0;


	glm::vec3 pixelColor;
	Ray ray(glm::vec3(0.0,0.0,eye),glm::vec3(0.0,0.0,-1.0));
	glm::vec2 samplePoint;
	glm::vec2 pixelPoint;

	for(int r=0;r<viewPlane.getVRes();r++)//up
	{
		for(int c=0;c<viewPlane.getHRes();c++)//across
		{
			ray.setDirection(glm::normalize(glm::vec3(viewPlane.getPixelSize() * (c - 0.5 * (viewPlane.getHRes() - 1.0)),
				viewPlane.getPixelSize() * (r - 0.5 * (viewPlane.getVRes() - 1.0)), -eyeDistanceFromViewPlane)));

			pixelColor = tracer->traceRay(ray);
			displayPixel(c,r,pixelColor);
		}
	}
	drawer->painting = false;
}

ShadeRec World::hitObjects(const Ray& ray)
{
	ShadeRec sr(*this);
	float t;
	float u, v;
	glm::vec3 normal;
	glm::vec3 localHitPoint;
	float tmin = kHugeValue;
	uint numObjects = objects.size();
	Material* material;

	for(uint i=0;i<numObjects;i++)
	{
		if(objects[i]->hit(ray,t,sr) && t < tmin)
		{
			sr.hitObject = true;
			u = sr.u;
			v = sr.v;
			tmin = t;
			//check to see if it's null since grids set the material in the hit
			if(sr.material == NULL)
				material =  objects[i]->getMaterial();
			else
				material = sr.material;
			sr.hitPoint = ray.getOrigin() + t * ray.getDirection();
			normal = sr.normal;
			localHitPoint = sr.localHitPoint;
		}
	}

	if(sr.hitObject)
	{
		sr.t = tmin;
		sr.u = u;
		sr.v = v;
		sr.normal = normal;
		sr.localHitPoint = localHitPoint;
		sr.material = material;
	}
	return sr;
}

World::~World()
{
	if(tracer != NULL)
	{
		delete tracer;
		tracer=NULL;
	}

	if(camera != NULL)
	{
		delete camera;
		camera = NULL;
	}

	if(drawer != NULL)
	{
		drawer=NULL;
	}

	for(uint i=0;i<objects.size();i++)
	{
		if(objects[i] != NULL)
		{
			delete objects[i];
			objects[i] = NULL;
		}
	}
	objects.clear();

	for(uint i=0;i<lights.size();i++)
	{
		delete lights[i];
		lights[i] = NULL;
	}
	lights.clear();

	if(ambientLight != NULL)
	{
		delete ambientLight;
		ambientLight = NULL;
	}

	for(uint i=0;i<materials.size();i++)
	{
		if(materials[i] != NULL)
		{
			delete materials[i];
			materials[i] = NULL;
		}
	}
	materials.clear();

	for(uint i=0;i<samplers.size();i++)
	{
		if(samplers[i] != NULL)
		{
			delete samplers[i];
			samplers[i] = 0;
		}
	}
	samplers.clear();
}

void World::addLight(Light* light)
{
	lights.push_back(light);
}

glm::vec3 World::maxToOne(const glm::vec3& color) const
{
	float maxValue = max(color.r, max(color.g, color.b));
	if(maxValue > 1.0)
		return color/maxValue;
	else
		return color;
}

glm::vec3 World::clampToColor(const glm::vec3& rawColor) const
{
	glm::vec3 color(rawColor);

	if(rawColor.r > 1.0 || rawColor.g > 1.0 || rawColor.b > 1.0)
		color = glm::vec3(1,0,0);

	return color;
}

void World::addMaterial(Material* value)
{
	materials.push_back(value);
}

void World::addSampler(Sampler* value)
{
	samplers.push_back(value);
}