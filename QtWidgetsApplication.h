#pragma once
#include <QtWidgets/QMainWindow>
#include "QtWidgetsApplication.h"
#include "ui_QtWidgetsApplication.h"
#include "StartWindow.h"

class QtWidgetsApplication : public QMainWindow
{
	Q_OBJECT

public:
	QtWidgetsApplication(QWidget* parent, StartWindow* from, int width, int height, int mines);
	~QtWidgetsApplication();

	void closeEvent(QCloseEvent* event);

private:
	StartWindow* from;
	Ui::QtWidgetsApplicationClass ui;
};
