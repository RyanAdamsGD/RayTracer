#ifndef WORLD_H
#define WORLD_H
#include "ViewPlane.h"
#include "glm\gtx\transform.hpp"
#include "Ray.h"
#include "ShadeRec.h"
#include <vector>
class Light;
class Tracer;
class IDrawer;
class GeometricObject;
class Camera;
class Material;
class Texture;

class World
{
	bool showOutOfGamut;

	glm::vec3 backgroundColor;
	Tracer* tracer;
	IDrawer* drawer;
	Light* ambientLight;
	ViewPlane viewPlane;
	std::vector<Material*> materials;
	std::vector<Sampler*> samplers;

	void buildScene(int vres,int hres);
	void addMaterial(Material* value);
	void addSampler(Sampler* value);

public:
	std::vector<Light*> lights;
	std::vector<GeometricObject*> objects;
	Camera* camera;
	bool finished;

	World();
	~World();

	inline void addObject(GeometricObject* object) {objects.push_back(object);}
	inline const glm::vec3& getBackgroundColor() const {return backgroundColor;}
	inline const ViewPlane& getViewPlane() const {return viewPlane;}
	inline const Tracer* getTracer() const {return tracer;}
	inline Light* getAmbient() {return ambientLight;}
	inline void setAmbientLight(Light* value) {ambientLight = value;}
	inline void setCamera(Camera* value) {camera = value;}

	void init(IDrawer* drawer,int vres,int hres);
	void renderScene() const;
	void renderPerspective() const;
	void openWindow(const int hres, const int vres) const;
	void displayPixel(const int row, const int column, const glm::vec3& pixelColor) const;
	void addLight(Light* light);
	ShadeRec hitObjects(const Ray& ray);
	glm::vec3 maxToOne(const glm::vec3& color) const;
	glm::vec3 clampToColor(const glm::vec3& rawColor) const;
};

#endif