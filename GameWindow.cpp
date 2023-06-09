#include <iostream>
#include <QTimer>
#include <QMessageBox>
#include "GameWindow.h"
#include "MineSweeperElement.h"
#include "generateMinesweeperBoard.h"
#include "StartWindow.h"
#include "Positioin.h"

GameWindow::GameWindow(QWidget* parent, StartWindow* from, int width, int height, int mines) : QMainWindow(parent)
{
	ui.setupUi(this);
	// Set up the window
	this->lastWindow = from;
	this->mapWidth = width;
	this->mapHeight = height;
	this->mapMines = mines;
	this->setFixedSize(width * 30 + 20, height * 30 + 40);
	printMenu = this->menuBar()->addMenu("Print");
	printMenu->addAction("GameBoard", this, &GameWindow::printGameBoard);
	printMenu->addAction("GameState", this, &GameWindow::printGameState);
	printMenu->addAction("GameAnswer", this, &GameWindow::printGameAnswer);
	printMenu->addAction("BombCount", this, &GameWindow::printBombCount);
	printMenu->addAction("FlagCount", this, &GameWindow::printFlagCount);
	printMenu->addAction("OpenBlankCount", this, &GameWindow::printOpenBlankCount);
	printMenu->addAction("RemainBlankCount", this, &GameWindow::printRemainBlankCount);
	// Remove all toolbars
	QList<QToolBar*> allToolBars = this->findChildren<QToolBar*>();
	foreach(QToolBar * tb, allToolBars)
		this->removeToolBar(tb);

	layout = generateMinesweeperBoard(mapWidth, mapHeight, mines); // Generate the board
	mapBlanks = mapWidth * mapHeight - mapMines;
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &GameWindow::showNextButton);
	if (width * height <= 100)
		timer->start(2);
	else if (width * height <= 500)
		timer->start(1);
	else
		timer->start(0);
}

GameWindow::~GameWindow()
{
	for (int i = 0; i < mapHeight; i++)
		delete layout[i];
	delete layout;
	std::cout << "<Quit> : succeed" << std::endl;
}
void GameWindow::closeEvent(QCloseEvent* event)
{
	while (MineSweeperElement::m_objects.size() > 0)
	{
		MineSweeperElement* element = MineSweeperElement::m_objects[0];
		element->~MineSweeperElement();
		MineSweeperElement::m_objects.erase(MineSweeperElement::m_objects.begin());
	}
	for (int i = 0; i < mapHeight; i++)
		delete objectList[i];
	delete objectList;
	this->~GameWindow();
	lastWindow->show();
}
void  GameWindow::drawOut()
{
	objectList = new MineSweeperElement * *[mapHeight];
	for (int i = 0; i < mapHeight; i++)
	{
		objectList[i] = new MineSweeperElement * [mapWidth];
		for (int j = 0; j < mapWidth; j++)
		{
			MineSweeperInput* input = new MineSweeperInput();
			Position position = { j, i };
			input->position = &position;
			input->parent = this;
			input->value = layout[i][j];
			objectList[i][j] = new MineSweeperElement(input);
			connect(objectList[i][j], &QPushButton::clicked, this, &GameWindow::onButtonLeftClicked);
			objectList[i][j]->setContextMenuPolicy(Qt::CustomContextMenu); // to link menu event to button
			connect(objectList[i][j], &QPushButton::customContextMenuRequested, this, &GameWindow::onButtonRightClicked);
		}
	}
	// make all element invisable for testing objectList is working
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			objectList[i][j]->hide();
		}
	}
	// make all element visable by 0.5 second gap 
}
void GameWindow::showNextButton()
{
	static int i = 0, j = 0;
	if (i < mapHeight && j < mapWidth) {
		objectList[i][j]->show();
		j++;
		if (j == mapWidth) {
			j = 0;
			i++;
		}
	}
	else {
		timer->stop();
		i = 0;
		j = 0;
	}
}
void GameWindow::onButtonLeftClicked()
{
	MineSweeperElement* button = qobject_cast<MineSweeperElement*>(sender());
	int r = sweep(button);
	openedBlanks += r;
	if (openedBlanks == mapBlanks)
	{
		QMessageBox::information(this, "You Win", "You Win");
		button->win();
		status = 0;
	}
	if (r == -1)
	{
		QMessageBox::information(this, "You Lose", "You Lose");
		status = 0;
	}
}
void GameWindow::onButtonRightClicked()
{
	MineSweeperElement* button = qobject_cast<MineSweeperElement*>(sender());
	if (button->isSwept())
	{
		std::cout << "<RightClick " << button->getPosition().x << " " << button->getPosition().y << "> : Failed" << std::endl;
		return;
	}
	else
	{
		flags += button->onButtonRightClicked();
		std::cout << "<RightClick " << button->getPosition().x << " " << button->getPosition().y << "> : Success" << std::endl;
		return;
	}
}
int  GameWindow::sweep(MineSweeperElement* button)
{

	if (button->isFlagged() || button->isSwept() || button->isConfused())
	{
		std::cout << "<LeftClick " << button->getPosition().x << " " << button->getPosition().y << "> : Failed" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "<LeftClick " << button->getPosition().x << " " << button->getPosition().y << "> : Success" << std::endl;
		return button->sweep();
	}
}

void GameWindow::printGameBoard()
{
	std::cout << "<Print GameBoard> : " << std::endl;
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (objectList[i][j]->isFlagged())
				std::cout << "f ";
			else if (objectList[i][j]->isSwept() && objectList[i][j]->getValue() != -1)
				std::cout << objectList[i][j]->getValue() << " ";
			else if (objectList[i][j]->isConfused())
				std::cout << "? ";
			else
				std::cout << "# ";

		}
		std::cout << std::endl;
	}
}
void GameWindow::printGameState()
{
	std::cout << "<Print GameState> : " << std::endl;
	if (status)
		std::cout << "Playing" << std::endl;
	else
		std::cout << "GameOver" << std::endl;
}

void GameWindow::printGameAnswer()
{
	std::cout << "<Print GameAnswer> : " << std::endl;
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (layout[i][j] == -1)
				std::cout << "X ";
			else
				std::cout << layout[i][j] << " ";

		}
		std::cout << std::endl;
	}
}
void GameWindow::printBombCount()
{
	std::cout << "<Print BombCount> : " << std::endl;
	std::cout << mapMines << std::endl;
}

void GameWindow::printOpenBlankCount()
{
	std::cout << "<Print OpenBlankCount> : " << std::endl;
	std::cout << openedBlanks << std::endl;
}

void GameWindow::printRemainBlankCount()
{
	std::cout << "<Print RemainBlankCount> : " << std::endl;
	std::cout << mapBlanks - openedBlanks << std::endl;
}
void GameWindow::printFlagCount()
{
	std::cout << "<Print FlagCount> : " << std::endl;
	std::cout << flags << std::endl;
}
