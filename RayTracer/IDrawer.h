#ifndef IDRAWER_H
#define IDRAWER_H
#include "glm\gtx\transform.hpp"

class IDrawer
{
protected:
	int hres,vres;
public:
	bool painting;
	IDrawer():painting(true){}
	virtual void displayPixel(int pixelX, int pixelY, const glm::vec3& color) = 0;
	virtual void setHRes(int value) {hres = value;}
	virtual void setVRes(int value) {vres = value;}
};

#endif