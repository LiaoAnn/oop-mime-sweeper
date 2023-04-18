#include "StartWindow.h"
#include "qpushbutton.h"
#include "QtWidgetsApplication.h"
#include <QtWidgets/QApplication>
#include <QSpinBox>
StartWindow::StartWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QPushButton *button = new QPushButton("Start", this);
	this->resize(500, 150);
	button->setGeometry(QRect(QPoint(350, 50), QSize(100, 30)));
	connect(button, &QPushButton::clicked, this, &StartWindow::Startgame);
		QSpinBox* widthInput = new QSpinBox(this);
		widthInput->setRange(1, 40); // 設置輸入範圍為0到100
		widthInput->setSingleStep(1); // 設置步長為1
		widthInput->setValue(10);
		widthInput->setButtonSymbols(QAbstractSpinBox::UpDownArrows); // 設置按鈕樣式為上下箭頭
		widthInput->setAccelerated(true); // 啟用加速功能，即長按加按減鈕時數字的變化速度會加快
		widthInput->setKeyboardTracking(false); // 禁用鍵盤追蹤，即只有在焦點在輸入框中時才會接收鍵盤輸入
		widthInput->setGeometry(QRect(QPoint(50, 50), QSize(100, 30)));
		this->widthBox = widthInput;
		QSpinBox* heightInput = new QSpinBox(this);
		heightInput->setRange(1, 40); // 設置輸入範圍為0到100
		heightInput->setSingleStep(1); // 設置步長為1
		heightInput->setValue(10);
		heightInput->setButtonSymbols(QAbstractSpinBox::UpDownArrows); // 設置按鈕樣式為上下箭頭
		heightInput->setAccelerated(true); // 啟用加速功能，即長按加按減鈕時數字的變化速度會加快
		heightInput->setKeyboardTracking(false); // 禁用鍵盤追蹤，即只有在焦點在輸入框中時才會接收鍵盤輸入
		heightInput->setGeometry(QRect(QPoint(150, 50), QSize(100, 30)));
		this->heightBox = heightInput;
		QSpinBox* mineNumbers = new QSpinBox(this);
		mineNumbers->setRange(1, 40); // 設置輸入範圍為0到100
		mineNumbers->setSingleStep(1); // 設置步長為1
		mineNumbers->setValue(10);
		mineNumbers->setButtonSymbols(QAbstractSpinBox::UpDownArrows); // 設置按鈕樣式為上下箭頭
		mineNumbers->setAccelerated(true); // 啟用加速功能，即長按加按減鈕時數字的變化速度會加快
		mineNumbers->setKeyboardTracking(false); // 禁用鍵盤追蹤，即只有在焦點在輸入框中時才會接收鍵盤輸入
		mineNumbers->setGeometry(QRect(QPoint(250, 50), QSize(100, 30)));
		this->minesBox = mineNumbers;
		connect(widthInput, &QSpinBox::valueChanged, this, &StartWindow::setWidth);
		connect(heightInput, &QSpinBox::valueChanged, this, &StartWindow::setHeight);
		connect(mineNumbers, &QSpinBox::valueChanged, this, &StartWindow::setMines);

}
StartWindow::~StartWindow()
{
	
}
void StartWindow::Startgame()
{
	QtWidgetsApplication* window = new QtWidgetsApplication(this,this,width,height,mines);
	// Set size and lock it
	window->resize(height *30+20, width *30+30);
	
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
}
void StartWindow::setHeight()
{
	this->height = this->heightBox->value();
}
void StartWindow::setMines()
{
	this->mines = this->minesBox->value();
}
