#include "PinHoleCamera.h"
#include "Ray.h"
#include "World.h"
#include "Sampler.h"
#include "Tracer.h"
#include "boost\thread\thread.hpp"
#include "FastDelegate.h"
#include "HelperFunctions.h"
#include "DebugMemory.h"

PinHoleCamera::PinHoleCamera()
	:viewPlaneDistance(100.0),zoom(1.0)
{
}

PinHoleCamera::PinHoleCamera(const glm::vec3& eye,const glm::vec3& lookat,float viewPlaneDistance,
	const glm::vec3& up,float zoom,float exposureTime)
	:Camera(eye,lookat,up,exposureTime),viewPlaneDistance(viewPlaneDistance),zoom(zoom)
{
}

PinHoleCamera::PinHoleCamera(const glm::vec3& eye,const glm::vec3& lookat,float viewPlaneDistance,
	float zoom,float exposureTime)
	:Camera(eye,lookat,glm::vec3(0,1,0),exposureTime),viewPlaneDistance(viewPlaneDistance),zoom(zoom)
{
}

void PinHoleCamera::renderScene(World* world)
{
	ViewPlane viewPlane = ViewPlane(world->getViewPlane());

	viewPlane.setPixelSize(viewPlane.getPixelSize()/zoom);
	int* pixel;

	for(int r=0;r<viewPlane.getVRes();r++)
		for(int c=0;c<viewPlane.getHRes();c++)
		{
			pixel = new int[2];
			pixel[0] = r; pixel[1] = c;
			pixels.push(pixel);
		}


	boost::thread** thrds = (boost::thread**) malloc(sizeof(boost::thread*) * NUMBER_OF_THREADS);
	for(uint t=0;t<NUMBER_OF_THREADS;t++)
	{
		thrds[t] = new boost::thread(fastdelegate::MakeDelegate(this,&PinHoleCamera::displayPixel),world);
	}
	
	for(uint t=0;t<NUMBER_OF_THREADS;t++)
	{
		thrds[t]->join();
		delete thrds[t];
	}
	free(thrds);
	world->finished = true;
}

void PinHoleCamera::displayPixel(World* world)
{
	ViewPlane viewPlane = ViewPlane(world->getViewPlane());
	viewPlane.setPixelSize(viewPlane.getPixelSize()/zoom);
	int depth = 0; //recursion depth
	Ray ray = Ray(glm::vec3(),glm::vec3());
	glm::vec3 pixelColor = glm::vec3(0.0f);
	glm::vec2 samplePoint, pixelPoint;
	ray.setOrigin(eye);
	std::queue<int*> pixelsGrabbbed;
	int* pixel;
	int row, column;

	//grab a couple pixels
	mtx.lock();
	while(pixels.size() > 0)
	{
		uint size = pixels.size();
		uint numberOfPixelsToGrab = ceil(size * 0.1 / NUMBER_OF_THREADS);
		numberOfPixelsToGrab = max(numberOfPixelsToGrab,10);

		for(uint i=0;i<numberOfPixelsToGrab && i< size;i++)
		{
			pixelsGrabbbed.push(pixels.front());
			pixels.pop();
		}
		mtx.unlock();

		while(pixelsGrabbbed.size() > 0)
		{
			pixel = pixelsGrabbbed.front();
			pixelsGrabbbed.pop();
			row = pixel[0];
			column = pixel[1];
			delete[] pixel;

			pixelColor = glm::vec3(0);

			for(int j=0;j<viewPlane.getNumSamples();j++)
			{
				samplePoint = viewPlane.getSampler()->sampleUnitSquare();
				pixelPoint.x = viewPlane.getPixelSize() * (column - 0.5f * viewPlane.getHRes() + samplePoint.x);
				pixelPoint.y = viewPlane.getPixelSize() * (row - 0.5f * viewPlane.getVRes() + samplePoint.y);
				ray.setDirection(rayDirection(pixelPoint));

				pixelColor += world->getTracer()->traceRay(ray,depth);
			}

			pixelColor /= viewPlane.getNumSamples();
			pixelColor *= exposureTime;
			world->displayPixel(row,column,pixelColor);
		}
		mtx.lock();
	}
	mtx.unlock();
}

glm::vec3 PinHoleCamera::rayDirection(const glm::vec2& point) const
{
	glm::vec3 dir = point.x * u + point.y * v - viewPlaneDistance * w;
	return glm::normalize(dir);
}
