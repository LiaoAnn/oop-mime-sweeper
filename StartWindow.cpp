#include "StartWindow.h"
#include "qpushbutton.h"
#include "QtWidgetsApplication.h"
#include <QtWidgets/QApplication>
#include <QSpinBox>
#include <QUrl>

StartWindow::StartWindow(QWidget* parent)
	: QMainWindow(parent)
{	
	ui.setupUi(this);
	QPushButton* button = new QPushButton("Start", this);
	this->resize(500, 150);
	button->setGeometry(QRect(QPoint(350, 50), QSize(100, 30)));
	connect(button, &QPushButton::clicked, this, &StartWindow::Startgame);
	widthBox = new QSpinBox(this);
	widthBox->setRange(1, 40);
	widthBox->setSingleStep(1);
	widthBox->setValue(10);
	widthBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
	widthBox->setAccelerated(true);
	widthBox->setKeyboardTracking(false);
	widthBox->setGeometry(QRect(QPoint(50, 50), QSize(100, 30)));
	this->widthBox = widthBox;
	heightBox = new QSpinBox(this);
	heightBox->setRange(1, 40);
	heightBox->setSingleStep(1);
	heightBox->setValue(10);
	heightBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
	heightBox->setAccelerated(true);
	heightBox->setKeyboardTracking(false);
	heightBox->setGeometry(QRect(QPoint(150, 50), QSize(100, 30)));
	this->heightBox = heightBox;
	minesBox = new QSpinBox(this);
	minesBox->setRange(1, 100);
	minesBox->setSingleStep(1);
	minesBox->setValue(10);
	minesBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
	minesBox->setAccelerated(true);
	minesBox->setKeyboardTracking(false);
	minesBox->setGeometry(QRect(QPoint(250, 50), QSize(100, 30)));
	this->minesBox = minesBox;
	connect(widthBox, &QSpinBox::valueChanged, this, &StartWindow::setWidth);
	connect(heightBox, &QSpinBox::valueChanged, this, &StartWindow::setHeight);
	connect(minesBox, &QSpinBox::valueChanged, this, &StartWindow::setMines);
}
StartWindow::~StartWindow()
{

}
void StartWindow::Startgame()
{
	QtWidgetsApplication* window = new QtWidgetsApplication(this, this, width, height, mines);
	window->resize(width * 30 + 20, height * 30 + 30);
	window->move(100, 100);
	time_t t = time(0);
	QString Title = QString::fromStdString("build time : ") + ctime(&t);
	window->setWindowTitle(Title);
	window->show();
	this->hide();
}
void StartWindow::setWidth()
{
	this->width = this->widthBox->value();
	minesBox->setRange(1, width * height);
}
void StartWindow::setHeight()
{
	this->height = this->heightBox->value();
	minesBox->setRange(1, width * height);
}
void StartWindow::setMines()
{
	this->mines = this->minesBox->value();
}
