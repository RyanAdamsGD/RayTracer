#include "SphereicalPanoramicCamera.h"
#include "TypeDefs.h"
#include "ViewPlane.h"
#include "Tracer.h"
#include "World.h"
#include "Ray.h"
#include "Sampler.h"
#include "DebugMemory.h"

SphereicalPanoramicCamera::SphereicalPanoramicCamera(const glm::vec3& eye, const glm::vec3& lookat,float verticalMax,
	float horizontalMax,const glm::vec3& up,float exposureTime)
	:Camera(eye,lookat,up,exposureTime),verticalMax(verticalMax),horizontalMax(horizontalMax)
{
}

SphereicalPanoramicCamera::SphereicalPanoramicCamera(const glm::vec3& eye, const glm::vec3& lookat,float verticalMax
	,float horizontalMax,float exposureTime)
	:Camera(eye,lookat,glm::vec3(0,1,0),exposureTime),verticalMax(verticalMax),horizontalMax(horizontalMax)
{
}

void SphereicalPanoramicCamera::renderScene(World* world)
{
	glm::vec3 pixelColor;
	ViewPlane viewPlane(world->getViewPlane());
	Ray ray = Ray(glm::vec3(),glm::vec3());
	int depth = 0;
	glm::vec2 pixelPoint, samplePoint;

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
				ray.setDirection(rayDirection(pixelPoint,viewPlane.getHRes(),viewPlane.getVRes(),viewPlane.getPixelSize()));

				pixelColor += world->getTracer()->traceRay(ray,depth);
			}

			pixelColor /= viewPlane.getNumSamples();
			pixelColor *= exposureTime;
			world->displayPixel(r,c,pixelColor);
		}
}

glm::vec3 SphereicalPanoramicCamera::rayDirection(const glm::vec2& point, int hres, int vres, float pixelSize) const
{
	//compute the normalized device coordinates
	glm::vec2 normalizedPoint(2.0f / (pixelSize * hres) * point.x, 2.0f / (pixelSize * vres) * point.y);

	float lambda = normalizedPoint.x * horizontalMax * PI_OVER_180;
	float psi = normalizedPoint.y * verticalMax * PI_OVER_180;

	float theta = 0.5f * PI - psi;
	float phi = PI - lambda;

	float sinTheta = sin(theta);

	glm::vec3 direction = sin(phi) * sinTheta * u +
		cos(theta) * v + cos(phi) * sinTheta * w;
	return direction;

}