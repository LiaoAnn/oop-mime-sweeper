#include <QtWidgets/QApplication>
#include "StartWindow.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	StartWindow startWindow;
	startWindow.show();
	return a.exec();
}
