#include "QtPaintWindow.h"
#include "Qt\qpainter.h"
#include "Qt\qevent.h"
#include "boost\thread\thread.hpp"
#include <fstream>

QtPaintWindow::QtPaintWindow(QWidget* widget)
	:QWidget(widget),image(),pixelCount(0)
{
	widget->setMinimumSize(1000,800);
	widget->setAttribute(Qt::WA_OpaquePaintEvent);
}

void QtPaintWindow::paintEvent(QPaintEvent* e)
{
	QPainter painter;
	drawImage();
}

void QtPaintWindow::displayPixel(int pixelX, int pixelY, const glm::vec3& color)
{
	Pixel pixel(color * 255.0f,pixelX,pixelY);
	QRgb colorValue = qRgb(pixel.color.r,pixel.color.g,pixel.color.b);
	image.setPixel(pixel.x,pixel.y,colorValue);
}

void QtPaintWindow::drawImage()
{
	QPainter painter(this);
	painter.drawImage(0,0,image);
}

void QtPaintWindow::writeToImage()
{
}

void QtPaintWindow::setHRes(int value)
{
	hres = value;
	image = QImage(hres,vres,QImage::Format::Format_RGB32);
}

void QtPaintWindow::setVRes(int value)
{
	vres = value;
	image = QImage(hres,vres,QImage::Format::Format_RGB32);
}

void QtPaintWindow::writeToFile()
{
	bool fileWritten = false;
	int attempts = 0;
	const char* imageName = getFileName();
	while(!fileWritten && attempts < 5)
	{
		fileWritten = image.save(imageName,"PNG",-1);
		attempts++;
	}
	pixelCount = 0;
	delete imageName;
	image = QImage(vres,hres,QImage::Format::Format_RGB32);
}

char* QtPaintWindow::getFileName()const 
{
	char* fileName = new char[14];
	int existingFileCount = 0;
	while(true)
	{
		sprintf(fileName,"image%04d.png",existingFileCount);
		std::ifstream file(fileName,std::ios::binary);
		//look until we find an open file name
		if(!file || existingFileCount > 9999)
			break;
		existingFileCount++;
	}
	return fileName;
}
