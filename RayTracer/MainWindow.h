#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui\qwidget.h>
#include <Qt\qtimer.h>
#include "IUpdatable.h"
namespace Neumont{class Slider;}
class QCheckBox;
class QtPaintWindow;
class World;

class MainWindow : public QWidget
{
	Q_OBJECT
		QWidget* DebugMenu;
		QtPaintWindow* QtWindow;
		World* world;

		void createRayTraceThread();
		int count;
protected:
		void timerEvent(QTimerEvent* e);
	private slots:
		void guiValueChanged();
public:
	bool use3d;
	MainWindow();
};

#endif