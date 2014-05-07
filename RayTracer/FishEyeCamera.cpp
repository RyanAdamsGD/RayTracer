#include "FishEyeCamera.h"
#include "TypeDefs.h"
#include "ViewPlane.h"
#include "Tracer.h"
#include "World.h"
#include "Ray.h"
#include "Sampler.h"
#include "DebugMemory.h"

FishEyeCamera::FishEyeCamera(const glm::vec3& eye, const glm::vec3& lookat,float psiMax,
		const glm::vec3& up,float exposureTime)
		:Camera(eye,lookat,up,exposureTime), psiMax(psiMax)
{
}

FishEyeCamera::FishEyeCamera(const glm::vec3& eye, const glm::vec3& lookat,float psiMax
		,float exposureTime)
		:Camera(eye,lookat,glm::vec3(0,1,0),exposureTime),psiMax(psiMax)
{
}

void FishEyeCamera::renderScene(World* world)
{
	glm::vec3 pixelColor;
	ViewPlane viewPlane(world->getViewPlane());
	Ray ray = Ray(glm::vec3(),glm::vec3());
	int depth = 0;
	glm::vec2 pixelPoint, samplePoint;
	float radiusSqaured;

	ray.setOrigin(eye);
	
	for(uint r=0;r<viewPlane.getVRes();r++)
		for(uint c=0; c<viewPlane.getHRes();c++)
		{
			pixelColor = glm::vec3(0.0f);

			for(uint j=0;j<viewPlane.getNumSamples();j++)
			{
				samplePoint = viewPlane.getSampler()->sampleUnitSquare();
				pixelPoint.x = viewPlane.getPixelSize() * (c - 0.5f * viewPlane.getHRes() + samplePoint.x);
				pixelPoint.y = viewPlane.getPixelSize() * (r - 0.5f * viewPlane.getVRes() + samplePoint.y);
				ray.setDirection(rayDirection(pixelPoint,viewPlane.getHRes(),viewPlane.getVRes(),viewPlane.getPixelSize(),&radiusSqaured));

				if(radiusSqaured <= 1.0f)
					pixelColor += world->getTracer()->traceRay(ray,depth);
			}

			pixelColor /= viewPlane.getNumSamples();
			pixelColor *= exposureTime;
			world->displayPixel(r,c,pixelColor);
		}
}

glm::vec3 FishEyeCamera::rayDirection(const glm::vec2& point, int hres, int vres,
	float pixelSize, float* radiusSquared) const
{
	//compute the normalized device coordinates
	glm::vec2 normalizedPoint(2.0f / (pixelSize * hres) * point.x, 2.0f / (pixelSize * vres) * point.y);

	*radiusSquared = normalizedPoint.x * normalizedPoint.x + normalizedPoint.y * normalizedPoint.y;

	if(*radiusSquared <= 1.0f)
	{
		float radius = sqrt(*radiusSquared);
		float psi = radius * psiMax * PI_OVER_180;
		float sinPsi = sin(psi);
		float cosPsi = cos(psi);
		glm::vec3 direction = sinPsi * (normalizedPoint.x / radius) * u +
			sinPsi * (normalizedPoint.y / radius) * v - cosPsi * w;
		return direction;
	}
	else
		return glm::vec3(0.0f);
}
