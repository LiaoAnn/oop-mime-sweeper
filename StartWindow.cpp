#include "StartWindow.h"
#include "ui_StartWindow.h"
#include "qpushbutton.h"
#include "GameWindow.h"
#include <QApplication>
#include <QSpinBox>
#include <QLabel>
#include <QUrl>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <QLineEdit>
#include <QFileDialog>
#include <qmessagebox.h>
#include <qradiobutton.h>
#include "generateMinesweeperBoard.h"
#include <fstream>
#include <iostream>

StartWindow::StartWindow(QWidget* parent) : QMainWindow(parent)
{

	ui.setupUi(this);
	// Remove all toolbars
	QList<QToolBar*> allToolBars = this->findChildren<QToolBar*>();
	foreach(QToolBar * tb, allToolBars)
		this->removeToolBar(tb);
	// Custom window
	this->setFixedSize(800, 600);
	groupBox = new QGroupBox(this);
	groupBox->setGeometry(QRect(QPoint(20, 10), QSize(760, 80)));
	QLabel* label_Column = new QLabel("Column", groupBox);
	label_Column->setAlignment(Qt::AlignCenter);
	label_Column->setGeometry(QRect(QPoint(20, 20), QSize(60, 30)));
	QLabel* label_Row = new QLabel("Row", groupBox);
	label_Row->setAlignment(Qt::AlignCenter);
	label_Row->setGeometry(QRect(QPoint(180, 20), QSize(60, 30)));
	QLabel* label_Mines = new QLabel("Mines", groupBox);
	label_Mines->setAlignment(Qt::AlignCenter);
	label_Mines->setGeometry(QRect(QPoint(340, 20), QSize(60, 30)));
	widthBox = new QSpinBox(groupBox);
	widthBox->setRange(1, 40);
	widthBox->setSingleStep(1);
	widthBox->setValue(10);
	widthBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
	widthBox->setAccelerated(true);
	widthBox->setKeyboardTracking(false);
	widthBox->setGeometry(QRect(QPoint(80, 20), QSize(100, 30)));
	this->widthBox = widthBox;
	heightBox = new QSpinBox(groupBox);
	heightBox->setRange(1, 40);
	heightBox->setSingleStep(1);
	heightBox->setValue(10);
	heightBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
	heightBox->setAccelerated(true);
	heightBox->setKeyboardTracking(false);
	heightBox->setGeometry(QRect(QPoint(240, 20), QSize(100, 30)));
	this->heightBox = heightBox;
	minesBox = new QDoubleSpinBox(groupBox);
	minesBox->setRange(1, 100);
	minesBox->setSingleStep(1);
	minesBox->setValue(10);
	minesBox->setDecimals(0);
	minesBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
	minesBox->setAccelerated(true);
	minesBox->setKeyboardTracking(false);
	minesBox->setGeometry(QRect(QPoint(400, 20), QSize(100, 30)));
	this->minesBox = minesBox;
	mineUnitBox = new QComboBox(groupBox);
	mineUnitBox->addItem("Mines");
	mineUnitBox->addItem("Mines%");
	mineUnitBox->setGeometry(QRect(QPoint(510, 20), QSize(100, 30)));
	groupBox2 = new QGroupBox(this);
	groupBox2->setGeometry(QRect(QPoint(20, 100), QSize(760, 90)));
	groupBox2->setDisabled(true);
	lineEdit = new QLineEdit(groupBox2);
	lineEdit->setGeometry(QRect(QPoint(20, 20), QSize(670, 30)));
	QPushButton* BrowseBtn = new QPushButton("Browse", groupBox2);
	BrowseBtn->setGeometry(QRect(QPoint(690, 20), QSize(50, 30)));
	QGroupBox* groupBox3 = new QGroupBox(this);
	groupBox3->setGeometry(QRect(QPoint(20, 200), QSize(760, 90)));
	radioBtn1 = new QRadioButton("Random mode", groupBox3);
	radioBtn1->setGeometry(QRect(QPoint(20, 20), QSize(120, 30)));
	radioBtn1->setChecked(true);
	radioBtn2 = new QRadioButton("File mode", groupBox3);
	radioBtn2->setGeometry(QRect(QPoint(180, 20), QSize(100, 30)));
	QPushButton* button2 = new QPushButton("Load", groupBox3);
	button2->setGeometry(QRect(QPoint(500, 20), QSize(100, 30)));
	QPushButton* button = new QPushButton("Start", groupBox3);
	button->setGeometry(QRect(QPoint(620, 20), QSize(100, 30)));

	connect(button, &QPushButton::clicked, this, &StartWindow::Startgame);
	connect(widthBox, &QSpinBox::valueChanged, this, &StartWindow::setWidth);
	connect(heightBox, &QSpinBox::valueChanged, this, &StartWindow::setHeight);
	connect(minesBox, &QDoubleSpinBox::valueChanged, this, &StartWindow::setMines);
	connect(mineUnitBox, &QComboBox::currentIndexChanged, this, &StartWindow::setMinesUnit);
	connect(BrowseBtn, &QPushButton::clicked, this, &StartWindow::browseFile);
	connect(radioBtn1, &QRadioButton::clicked, this, &StartWindow::sourceMode);
	connect(radioBtn2, &QRadioButton::clicked, this, &StartWindow::sourceMode);
	connect(button2, &QPushButton::clicked, this, &StartWindow::loadFile);
}
StartWindow::~StartWindow()
{

}
void StartWindow::Startgame()
{
	if (!canStart)
		return;
	GameWindow* window = new GameWindow(this, this, layout, width, height, mines);
	// lock the window size
	window->setFixedSize(window->size());
	window->move(this->geometry().topLeft().x(), this->geometry().topLeft().y());
	window->show();
	window->drawOut();
	canStart = false;
	layout = nullptr;
	this->hide();
}
void StartWindow::setWidth()
{
	this->width = this->widthBox->value();
	if (!minesUnit)
		minesBox->setRange(1, width * height);
}
void StartWindow::setHeight()
{
	this->height = this->heightBox->value();
	if (!minesUnit)
		minesBox->setRange(1, width * height);
}
void StartWindow::setMines()
{
	if (minesUnit)
		this->mines = this->minesBox->value() * width * height;
	else
		this->mines = this->minesBox->value();
}
void StartWindow::setMinesUnit()
{

	if (mineUnitBox->currentIndex() == 0)
	{
		minesUnit = false;
		minesBox->setDecimals(0);
		minesBox->setRange(1, width * height);
		minesBox->setSingleStep(1);
		minesBox->setValue(width * height * 0.1);
	}
	else
	{
		minesUnit = true;
		minesBox->setDecimals(2);
		minesBox->setRange(0, 1);
		minesBox->setSingleStep(0.05);
		minesBox->setValue(0.1);
	}
	setMines();
}

void StartWindow::browseFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
	lineEdit->setText(fileName);
}

void StartWindow::sourceMode()
{
	if (radioBtn1->isChecked())
	{
		groupBox->setDisabled(false);
		groupBox2->setDisabled(true);
	}
	else
	{
		groupBox->setDisabled(true);
		groupBox2->setDisabled(false);
	}
}
void StartWindow::loadFile()
{
	if (radioBtn1->isChecked())
	{
		layout = generateMinesweeperBoard(width, height, mines);
	}
	else
	{
		std::ifstream file(lineEdit->text().toStdString());
		if (!file.is_open())
		{
			QMessageBox::warning(this, tr("Warning"), tr("File not found!"));
			return;
		}
		file >> height >> width;
		mineUnitBox-> setCurrentIndex(0);
		mines = 0;
		char** c_layout = new char* [height];
		for (int i = 0; i < height; i++)
		{
			c_layout[i] = new char[width];
			for (int j = 0; j < width; j++)
			{
				file >> c_layout[i][j];
				if(c_layout[i][j]=='X')
					mines ++;
			}
		}
		heightBox->setValue(height);
		widthBox->setValue(width);
		minesBox->setValue(mines);
		layout = transformationMinesweeperBoard(c_layout, width, height);
		for (int i = 0; i < height; i++)
			delete[] c_layout[i];
		delete[] c_layout;
	}
	canStart = 1;
}
