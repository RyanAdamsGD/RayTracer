#include <Qt\qapplication.h>
#include "MainWindow.h"
#include "DebugMemory.h"
#include <Windows.h>

int main(int argc, char* argv[])
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	QApplication app(argc,argv);
	MainWindow widget;
	widget.show();
	return app.exec();
}