#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication.h"
#include <QSpinBox>
class StartWindow : public QMainWindow
{
	Q_OBJECT

public:
	StartWindow(QWidget* parent = nullptr);
	~StartWindow();
	void Startgame();
	void setWidth();
	void setHeight();
	void setMines();
private:
	int width=1;
	int height=1;
	int mines=1;
	QSpinBox* widthBox;
	QSpinBox* heightBox;
	QSpinBox* minesBox;
	Ui::QtWidgetsApplicationClass ui;
};