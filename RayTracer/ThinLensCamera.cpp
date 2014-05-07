#include "ThinLensCamera.h"
#include "World.h"
#include "Sampler.h"
#include "Tracer.h"
#include "DebugMemory.h"

ThinLensCamera::ThinLensCamera(const glm::vec3& eye, const glm::vec3& lookat,float viewPlaneDistance,
		const glm::vec3& up,float focalDistance, float lensRadius,float zoom,float exposureTime)
	:Camera(eye,lookat,up,exposureTime),lensRadius(lensRadius),focalPlaneDistance(focalDistance),
	viewPlaneDistance(viewPlaneDistance),zoom(zoom)
{
}

ThinLensCamera::ThinLensCamera(const glm::vec3& eye, const glm::vec3& lookat,float viewPlaneDistance
	,float focalDistance, float lensRadius,float zoom,float exposureTime)
	:Camera(eye,lookat,glm::vec3(0,1,0),exposureTime),lensRadius(lensRadius),
	focalPlaneDistance(focalDistance),viewPlaneDistance(viewPlaneDistance),zoom(zoom)
{
}

void ThinLensCamera::renderScene(World* world)
{
	ViewPlane viewPlane = ViewPlane(world->getViewPlane());
	viewPlane.getSampler()->mapSamplesToUnitDisk();
	glm::vec3 pixelColor;
	Ray ray = Ray(glm::vec3(),glm::vec3());
	int depth = 0; //recursion depth
	glm::vec2 samplePoint, pixelPoint,diskPoint,lensPoint;

	viewPlane.setPixelSize(viewPlane.getPixelSize()/zoom);

	for(int r=0;r<viewPlane.getVRes();r++)
		for(int c=0;c<viewPlane.getHRes();c++)
		{
			pixelColor = glm::vec3(0.0f);

			for(int n=0;n<viewPlane.getNumSamples();n++)
			{
				samplePoint = viewPlane.getSampler()->sampleUnitSquare();
				pixelPoint.x = viewPlane.getPixelSize() * (c - 0.5f * viewPlane.getHRes() + samplePoint.x);
				pixelPoint.y = viewPlane.getPixelSize() * (r - 0.5f * viewPlane.getVRes() + samplePoint.y);
				
				diskPoint = viewPlane.getSampler()->sampleUnitDisk();
				lensPoint = diskPoint * lensRadius;

				ray.setOrigin(eye + lensPoint.x * u + lensPoint.y * v);
				ray.setDirection(rayDirection(pixelPoint,lensPoint));

				pixelColor += world->getTracer()->traceRay(ray,depth);
			}

			pixelColor /= viewPlane.getNumSamples();
			pixelColor *= exposureTime;
			world->displayPixel(r,c,pixelColor);
		}
}

glm::vec3 ThinLensCamera::rayDirection(const glm::vec2 pixelPoint, const glm::vec2 lensPoint)const
{
	glm::vec2 focalPoint;
	
	focalPoint.x = pixelPoint.x * focalPlaneDistance / viewPlaneDistance;
	focalPoint.y = pixelPoint.y * focalPlaneDistance / viewPlaneDistance;

	glm::vec3 direction = (pixelPoint.x - lensPoint.x) * u + (pixelPoint.y - lensPoint.y) * v - focalPlaneDistance * w;
	return glm::normalize(direction);
}
