#include "QtWidgetsApplication.h"
#include <QtWidgets/QApplication>
#include <ctime>
#include <string>
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QtWidgetsApplication w;
	w.show();
	// Set size and lock it
	w.resize(320, 330);
	w.setMaximumSize(740, 750);
	w.setMinimumSize(740, 750);
	w.move(100, 100);
	time_t t = time(0);
	// set window title as now time
	QString Title = QString::fromStdString("build time : ") + ctime(&t);
	w.setWindowTitle(Title);
	return a.exec();
}
