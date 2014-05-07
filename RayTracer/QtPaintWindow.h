#ifndef QTPAINTWINDOW_H
#define QTPAINTWINDOW_H
#include <QtGui\qwidget.h>
#include "IDrawer.h"
#include "boost\thread\mutex.hpp"
#include <queue>

class QtPaintWindow:public QWidget, public IDrawer
{
	uint pixelCount;
	static const int BORDER = 5;
	int Width;
	int Height;
	int hres;
	int vres;
	QImage image;

	struct Pixel
	{
		glm::vec3 color;
		float x,y;
		Pixel(const glm::vec3& color,float x, float y) 
			: color(color),x(x),y(y){}
		Pixel(){};
	};

	std::queue<Pixel> totalImageSoFar;
	static const uint NUMBER_OF_PIXELS_TO_DRAW = 500;
	Pixel pixelsToAdd[NUMBER_OF_PIXELS_TO_DRAW];

	void drawImage();
	void paint();
	void writeToImage();
	char* getFileName()const;

public:
	QtPaintWindow(QWidget* widget);
	void paintEvent(QPaintEvent* e);
	void writeToFile();

	virtual void displayPixel(int pixelX, int pixelY, const glm::vec3& color);
	virtual void setHRes(int value);
	virtual void setVRes(int value);
};

#endif