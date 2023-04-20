#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication.h"
#include <QSpinBox>
#include <QLabel>
#include <QUrl>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <QLineEdit>
#include <qradiobutton.h>
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
	void setMinesUnit();
	void browseFile();
	void sourceMode();
	//void ramdomMode();
private:
	int width = 10;
	int height = 10;
	bool minesUnit = false;
	double mines = 10;
	int** layout = nullptr;
	QSpinBox* widthBox;
	QSpinBox* heightBox;
	QDoubleSpinBox* minesBox;
	QComboBox* mineUnitBox;
	QLineEdit* lineEdit;
	QRadioButton* radioBtn1;
	QRadioButton* radioBtn2;
	QGroupBox* groupBox;
	QGroupBox* groupBox2;
	Ui::QtWidgetsApplicationClass ui;
};