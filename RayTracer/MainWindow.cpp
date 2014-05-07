#include "MainWindow.h"
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qcheckbox>
#include <QtGui\qlabel>
#include <Qt\qdebug.h>
#include "QTDebugMenu.h"
#include "QtPaintWindow.h"
#include "World.h"
#include "boost\thread\thread.hpp"
#include "FastDelegate.h"
#include "Camera.h"

#define NUM_OF_SCENES 1

MainWindow::MainWindow()
	:count(0)
{
	this->startTimer(80);
	int vres = 800;
	int hres = 1000;

	setMinimumSize(vres,hres);
	QVBoxLayout *mainLayout;
	setLayout(mainLayout=new QVBoxLayout);

	//Debug menu layout
	/*QHBoxLayout* rowLayout2;
	mainLayout->addLayout(rowLayout2 = new QHBoxLayout);
	mainLayout->addWidget(DebugMenu = new QWidget);
	QTDebugMenu::Init(DebugMenu);*/

	QHBoxLayout* rowLayout3;
	mainLayout->addLayout(rowLayout3 = new QHBoxLayout);

	mainLayout->addWidget(QtWindow = new QtPaintWindow(this));

	createRayTraceThread();
}

void MainWindow::guiValueChanged()
{

}

void MainWindow::timerEvent(QTimerEvent* e)
{
	QTDebugMenu::update();
	QtWindow->update();
	if(world != NULL && world->finished)
	{
		std::cout<<"image complete"<<std::endl;
		QtWindow->writeToFile();
		delete world;
		world = NULL;


	

		if(count < NUM_OF_SCENES)
			createRayTraceThread();
		else
			close();
	}
}

void MainWindow::createRayTraceThread()
{
	count++;
	int vres = 800;
	int hres = 800;
	world = new World();
	world->init(QtWindow,vres,hres);	
	boost::thread thrd(fastdelegate::MakeDelegate(world->camera,&Camera::renderScene),world);
}