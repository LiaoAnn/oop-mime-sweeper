/***********************************************************************
 * File: StartWindow.h
 * Author: ¼BÄ£®¦
 * Create Date: 2023/04/16
 * Editor: ¼BÄ£®¦
 * Update Date: 2023/04/26
 * Description: The header file of StartWindow.cpp
***********************************************************************/
#pragma once
#ifndef StartWindow_H
#define StartWindow_H
#include <QtWidgets/QMainWindow>
#include <QSpinBox>
#include <QLabel>
#include <QUrl>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <QLineEdit>
#include <qradiobutton.h>
#include <QtMultimedia/QMediaPlayer>
#include "ui_QtWidgetsApplication.h"

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
	void loadFile();	
	QSpinBox* widthBox;
	QSpinBox* heightBox;
	QDoubleSpinBox* minesBox;
	QComboBox* mineUnitBox;
	QLineEdit* lineEdit;
	QRadioButton* gen_RB;
	QRadioButton* lfd_RB;
	QGroupBox* generateBox;
	QGroupBox* readfileBox;
	QMediaPlayer* bgmPlayer = nullptr;
	QMediaPlayer* clickPlayer = nullptr;
	QMediaPlayer* boomPlayer = nullptr;
	Ui::QtWidgetsApplicationClass ui;
private:
	int width = 10;
	int height = 10;
	bool minesUnit = false; // false = s , true = %
	double mines = 10;
	int** layout = nullptr;
	bool canStart = 0; // check if the game can start
};
#endif

