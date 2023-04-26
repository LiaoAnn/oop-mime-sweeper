/***********************************************************************
 * File: StartWindow.cpp
 * Author: ¼BÄ£®¦
 * Create Date: 2023/04/16
 * Editor: ¼BÄ£®¦
 * Update Date: 2023/04/26
 * Description:  The source file of StartWindow.h
***********************************************************************/
#include "StartWindow.h"
#include "GameWindow.h"
#include "generateMinesweeperBoard.h"
#include <QApplication>
#include <QFileDialog>
#include <qmessagebox.h>
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
	this->setFixedSize(800, 300);
	this->setWindowTitle("Minesweeper");
	// Set All Buttons and Boxes
	generateBox = new QGroupBox(this);
	generateBox->setGeometry(QRect(QPoint(20, 10), QSize(760, 80)));
	QLabel* label_Column = new QLabel("Column", generateBox);
	label_Column->setAlignment(Qt::AlignCenter);
	label_Column->setGeometry(QRect(QPoint(20, 20), QSize(60, 30)));
	QLabel* label_Row = new QLabel("Row", generateBox);
	label_Row->setAlignment(Qt::AlignCenter);
	label_Row->setGeometry(QRect(QPoint(180, 20), QSize(60, 30)));
	QLabel* label_Mines = new QLabel("Mines", generateBox);
	label_Mines->setAlignment(Qt::AlignCenter);
	label_Mines->setGeometry(QRect(QPoint(340, 20), QSize(60, 30)));
	widthBox = new QSpinBox(generateBox);
	widthBox->setRange(1, 40);
	widthBox->setSingleStep(1);
	widthBox->setValue(10);
	widthBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
	widthBox->setAccelerated(true);
	widthBox->setKeyboardTracking(false);
	widthBox->setGeometry(QRect(QPoint(80, 20), QSize(100, 30)));
	this->widthBox = widthBox;
	heightBox = new QSpinBox(generateBox);
	heightBox->setRange(1, 40);
	heightBox->setSingleStep(1);
	heightBox->setValue(10);
	heightBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
	heightBox->setAccelerated(true);
	heightBox->setKeyboardTracking(false);
	heightBox->setGeometry(QRect(QPoint(240, 20), QSize(100, 30)));
	this->heightBox = heightBox;
	minesBox = new QDoubleSpinBox(generateBox);
	minesBox->setRange(1, 100);
	minesBox->setSingleStep(1);
	minesBox->setValue(10);
	minesBox->setDecimals(0);
	minesBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
	minesBox->setAccelerated(true);
	minesBox->setKeyboardTracking(false);
	minesBox->setGeometry(QRect(QPoint(400, 20), QSize(100, 30)));
	this->minesBox = minesBox;
	mineUnitBox = new QComboBox(generateBox);
	mineUnitBox->addItem("Mines");
	mineUnitBox->addItem("Mines%");
	mineUnitBox->setGeometry(QRect(QPoint(510, 20), QSize(100, 30)));
	readfileBox = new QGroupBox(this);
	readfileBox->setGeometry(QRect(QPoint(20, 100), QSize(760, 90)));
	readfileBox->setDisabled(true);
	lineEdit = new QLineEdit(readfileBox);
	lineEdit->setGeometry(QRect(QPoint(20, 20), QSize(670, 30)));
	QPushButton* BrowseBtn = new QPushButton("Browse", readfileBox);
	BrowseBtn->setGeometry(QRect(QPoint(690, 20), QSize(50, 30)));
	QGroupBox* groupBox3 = new QGroupBox(this);
	groupBox3->setGeometry(QRect(QPoint(20, 200), QSize(760, 90)));
	gen_RB = new QRadioButton("Random mode", groupBox3);
	gen_RB->setGeometry(QRect(QPoint(20, 20), QSize(120, 30)));
	gen_RB->setChecked(true);
	lfd_RB = new QRadioButton("File mode", groupBox3);
	lfd_RB->setGeometry(QRect(QPoint(180, 20), QSize(100, 30)));
	QPushButton* button2 = new QPushButton("Load", groupBox3);
	button2->setGeometry(QRect(QPoint(500, 20), QSize(100, 30)));
	QPushButton* button = new QPushButton("Start", groupBox3);
	button->setGeometry(QRect(QPoint(620, 20), QSize(100, 30)));

	// Connect signals and slots
	connect(button, &QPushButton::clicked, this, &StartWindow::Startgame);
	connect(widthBox, &QSpinBox::valueChanged, this, &StartWindow::setWidth);
	connect(heightBox, &QSpinBox::valueChanged, this, &StartWindow::setHeight);
	connect(minesBox, &QDoubleSpinBox::valueChanged, this, &StartWindow::setMines);
	connect(mineUnitBox, &QComboBox::currentIndexChanged, this, &StartWindow::setMinesUnit);
	connect(BrowseBtn, &QPushButton::clicked, this, &StartWindow::browseFile);
	connect(gen_RB, &QRadioButton::clicked, this, &StartWindow::sourceMode);
	connect(lfd_RB, &QRadioButton::clicked, this, &StartWindow::sourceMode);
	connect(button2, &QPushButton::clicked, this, &StartWindow::loadFile);
	// Load BGM and sound effects
	bgmPlayer = new QMediaPlayer(this);
	bgmPlayer->setSource(QUrl::fromLocalFile("bgm.wav"));
	bgmPlayer->setLoops(-1);
	clickPlayer = new QMediaPlayer(this);
	clickPlayer->setSource(QUrl::fromLocalFile("click.wav"));
	boomPlayer = new QMediaPlayer(this);
	boomPlayer->setSource(QUrl::fromLocalFile("boom.wav"));
	system("cls"); // clear the console
}

StartWindow::~StartWindow()
{

}
// Intent: to start the game
// Pre: no variable requirement
// Post: no return
void StartWindow::Startgame()
{
	// if no board loaded, then cannot start
	if (!canStart)
	{
		QMessageBox::warning(this, tr("Warning"), tr("No Board Loaded"));
		std::cout << "<Start> : Failed" << std::endl;
		return;
	}
	std::cout << "<Start> : Success" << std::endl;
	GameWindow* window = new GameWindow(this, this, layout, width, height, mines);
	// lock the window size
	window->setFixedSize(window->size());
	window->move(this->geometry().topLeft().x(), this->geometry().topLeft().y());
	window->show();
	window->drawOut();
	canStart = false;
	this->setWindowTitle("Minesweeper");
	// give the ownership of the layout to the game window
	layout = nullptr;
	// hide the start window
	this->hide();
}
// Intent: change the width of the board
// Pre: the event slot of the width box
// Post: no return
void StartWindow::setWidth()
{
	this->width = this->widthBox->value();
	if (!minesUnit)
		minesBox->setRange(1, width * height);
}
// Intent: change the height of the board
// Pre: the event slot of the height box
// Post: no return
void StartWindow::setHeight()
{
	this->height = this->heightBox->value();
	if (!minesUnit)
		minesBox->setRange(1, width * height);
}
// Intent: change the number of mines of the board
// Pre: the event slot of the mines box
// Post: no return
void StartWindow::setMines()
{
	if (minesUnit)
		this->mines = this->minesBox->value() * width * height;
	else
		this->mines = this->minesBox->value();
}
// Intent: change the mine unit of the board generation process
// Pre: the event slot of the mine unit box
// Post: no return
void StartWindow::setMinesUnit()
{

	if (mineUnitBox->currentIndex() == 0)
	{
		// change the range of the mines box to [1, width * height], and the step to 1
		minesUnit = false;
		minesBox->setDecimals(0);
		minesBox->setRange(1, width * height);
		minesBox->setSingleStep(1);
		minesBox->setValue(width * height * 0.1);
	}
	else
	{
		// change the range of the mines box to [0, 1], and the step to 0.05
		minesUnit = true;
		minesBox->setDecimals(2);
		minesBox->setRange(0, 1);
		minesBox->setSingleStep(0.05);
		minesBox->setValue(0.1);
	}
	setMines();
}
// Intent: to browse a file
// Pre: the event slot of the browse button
// Post: no return
void StartWindow::browseFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
	lineEdit->setText(fileName);
}
// Intent: to change the source mode
// Pre: the event slot of the radio buttons
// Post: no return
void StartWindow::sourceMode()
{
	if (gen_RB->isChecked())
	{
		generateBox->setDisabled(false);
		readfileBox->setDisabled(true);
	}
	else
	{
		generateBox->setDisabled(true);
		readfileBox->setDisabled(false);
	}
}
// Intent: to load a file
// Pre: the event slot of the load button
// Post: no return
void StartWindow::loadFile()
{
	if (gen_RB->isChecked())
	{
		layout = generateMinesweeperBoard(width, height, mines);
		if (!minesUnit)
			std::cout << "<Load RandomCount " << height << " " << width << " " << mines << "> : Success" << std::endl;
		else
			std::cout << "<Load RandomRate " << height << " " << width << " " << minesBox->value() << "> : Success" << std::endl;
		canStart = 1;
	}
	else
	{			
		std::ifstream file(lineEdit->text().toStdString());
		if (!file.is_open())
		{
			std::cout << "<Load BoardFile " << lineEdit->text().toStdString() << "> : Failed" << std::endl;
			QMessageBox::warning(this, tr("Warning"), tr("File not found!"));
			return;
		}
		file >> height >> width;
		mineUnitBox->setCurrentIndex(0);
		mines = 0;
		char** c_layout = new char* [height];
		for (int i = 0; i < height; i++)
		{
			c_layout[i] = new char[width];
			for (int j = 0; j < width; j++)
			{
				file >> c_layout[i][j];
				if (c_layout[i][j] == 'X')
					mines++;
			}
		}
		heightBox->setValue(height);
		widthBox->setValue(width);
		minesBox->setValue(mines);
		layout = transformationMinesweeperBoard(c_layout, width, height);
		for (int i = 0; i < height; i++)
			delete[] c_layout[i];
		delete[] c_layout;
		std::cout << "<Load BoardFile " << lineEdit->text().toStdString() << "> : Success" << std::endl;
		canStart = 1;
	}
	// set the window title
	this->setWindowTitle("Loaded " + QString::number(height) + "*" + QString::number(width) + "[" + QString::number(mines) + "] board");
}
