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
	int width=10;
	int height=10;
	int mines=10;
	QSpinBox* widthBox;
	QSpinBox* heightBox;
	QSpinBox* minesBox;
	Ui::QtWidgetsApplicationClass ui;
};