/***********************************************************************
 * File: GameWindow.cpp
 * Author: ¹ù§Ê¦w
 * Create Date: 2023/04/16
 * Editor: ¹ù§Ê¦w¡B¼BÄ£®¦
 * Update Date: 2023/04/26
 * Description: Game Window
***********************************************************************/
#include <iostream>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtMultimedia/QMediaPlayer>
#include "GameWindow.h"
#include "MineSweeperElement.h"
#include "generateMinesweeperBoard.h"
#include "StartWindow.h"
#include "Positioin.h"
 
// Intent: Constructor
// Pre: parent, from is QT windwos , board is a int pointer , width, height, mines are int
// Post: no return
GameWindow::GameWindow(QWidget* parent, StartWindow* from, int** board, int width, int height, int mines) : QMainWindow(parent)
{

	ui.setupUi(this);
	// Set up the Window and variables
	this->lastWindow = from;
	this->mapWidth = width;
	this->mapHeight = height;
	this->mapMines = mines;
	this->setFixedSize(width * 30 + 20, height * 30 + 40);
	this->layout = board;
	this->mapBlanks = mapWidth * mapHeight - mapMines;
	this->mineList = new MineSweeperElement * [mapMines];
	// Add menu Actions
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
	// Set up  Background Music
	bgmOutput = new QAudioOutput(this);
	bgmOutput->setVolume(0.05);
	lastWindow->bgmPlayer->setAudioOutput(bgmOutput);
	lastWindow->bgmPlayer->play();
	// Set up Sound Effect
	clickOutput = new QAudioOutput(this);
	clickOutput->setVolume(0.1);
	boomOutput = new QAudioOutput(this);
	boomOutput->setVolume(0.1);
	lastWindow->clickPlayer->setAudioOutput(clickOutput);
	lastWindow->boomPlayer->setAudioOutput(boomOutput);
} 
// Intent: Destructor
// Pre: no variable requiremnet
// Post: no return
GameWindow::~GameWindow()
{
	// Stop the BGM
	lastWindow->bgmPlayer->stop();
	// Delete all the objects
	for (int i = 0; i < mapHeight; i++)
		delete objectList[i];
	delete objectList;
	for (int i = 0; i < mapHeight; i++)
		delete layout[i];
	delete layout;
}
// Intent: intercept the close event
// Pre: event is a QCloseEvent pointer
// Post: no return
void GameWindow::closeEvent(QCloseEvent* event)
{
	if (status)
	{
		event->ignore();
		std::cout << "<Quit> : Failed" << std::endl;
		return;
	}
	std::cout << "<Quit> : Success" << std::endl;
	this->~GameWindow();
	// Show the Start window
	lastWindow->show();
}
// Intent: print the GameBoard
// Pre: no variable requiremnet
// Post: no return
void  GameWindow::drawOut()
{
	int mineCount = 0;
	// Set up the GameBoard
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
			if (layout[i][j] == -1)
			{
				mineList[mineCount] = objectList[i][j];
				mineCount++;
			}
			connect(objectList[i][j], &QPushButton::clicked, this, &GameWindow::onButtonLeftClicked);
			objectList[i][j]->setContextMenuPolicy(Qt::CustomContextMenu); // to link menu event to button
			connect(objectList[i][j], &QPushButton::customContextMenuRequested, this, &GameWindow::onButtonRightClicked);
		}
	}
}
// Intent: button sweep event slot function
// Pre: a MineSweeperElement pointer as sender will be passed in, no variable requiremnet
// Post: no return
void GameWindow::onButtonLeftClicked()
{
	lastWindow->clickPlayer->play();
	MineSweeperElement* button = qobject_cast<MineSweeperElement*>(sender());
	if (!status)
	{
		std::cout << "<LeftClick " << button->getPosition().x << " " << button->getPosition().y << "> : Failed" << std::endl;
		return;
	}
	if (button->isFlagged() || button->isSwept() || button->isConfused())
	{
		std::cout << "<LeftClick " << button->getPosition().x << " " << button->getPosition().y << "> : Failed" << std::endl;
		return;
	}
	std::cout << "<LeftClick " << button->getPosition().x << " " << button->getPosition().y << "> : Success" << std::endl;
	int returnSignal = buttonSweep(button);
	openedBlanks += returnSignal;
	button->setClicked(true);
	if (openedBlanks == mapBlanks)
	{
		status = 0;
		for (int i = 0; i < mapMines; i++)
		{
			mineList[i]->flag();
		}
		std::cout << "You win" << std::endl;
		QMessageBox* messageBox = new QMessageBox(
			QMessageBox::Information,
			"You Win",
			"You Win",
			QMessageBox::Retry | QMessageBox::Close, // «ö¶s
			this);
		QAbstractButton* retryButton = messageBox->button(QMessageBox::Retry);
		QAbstractButton* closeButton = messageBox->button(QMessageBox::Close);
		retryButton->setText("Replay");
		closeButton->setText("Quit");
		int ret = messageBox->exec();
		if (ret == QMessageBox::Retry) {
			std::cout << "<Replay> : Success" << std::endl;
			this->close();
		}
		else if (ret == QMessageBox::Close) {
			std::cout << "<Quit> : Success" << std::endl;
			this->close();
			lastWindow->close();
		}
	}
	if (returnSignal == -1)
	{
		status = 0;
		lastWindow->boomPlayer->play();
		for (int i = 0; i < mapMines; i++)
		{
			mineList[i]->setChecked(true);
			mineList[i]->disply();
		}
		std::cout << "You lose the game" << std::endl;
		QMessageBox* messageBox = new QMessageBox(
			QMessageBox::Information,
			"You Lose",
			"You Lose",
			QMessageBox::Retry | QMessageBox::Close, // «ö¶s
			this);
		QAbstractButton* retryButton = messageBox->button(QMessageBox::Retry);
		QAbstractButton* closeButton = messageBox->button(QMessageBox::Close);
		retryButton->setText("Replay");
		closeButton->setText("Quit");
		int ret = messageBox->exec();
		if (ret == QMessageBox::Retry) {
			std::cout << "<Replay> : Success" << std::endl;
			this->close();
		}
		else if (ret == QMessageBox::Close) {
			std::cout << "<Quit> : Success" << std::endl;
			this->close();
			lastWindow->close();
		}
	}
}
// Intent: button flag event slot function
// Pre: a MineSweeperElement pointer as sender will be passed in, no variable requiremnet
// Post: no return
void GameWindow::onButtonRightClicked()
{
	QMediaPlayer* player = new QMediaPlayer(this);
	lastWindow->clickPlayer->play();

	MineSweeperElement* button = qobject_cast<MineSweeperElement*>(sender());
	if (!status)
	{
		std::cout << "<RightClick " << button->getPosition().x << " " << button->getPosition().y << "> : Failed" << std::endl;
		return;
	}
	if (button->isSwept())
	{
		std::cout << "<RightClick " << button->getPosition().x << " " << button->getPosition().y << "> : Failed" << std::endl;
		return;
	}
	else
	{
		flags += buttonSign(button);
		std::cout << "<RightClick " << button->getPosition().x << " " << button->getPosition().y << "> : Success" << std::endl;
		return;
	}
}
// Intent: button sweep 
// Pre: button is a MineSweeperElement pointer
// Post: return the number of swept buttons
int GameWindow::buttonSweep(MineSweeperElement* button)
{
	// actually already check if the button is swept in the onButtonLeftClicked function , but still check here for safety
	int sweptCount = 0;
	if (button->isSwept() == false)
	{
		if (button->getValue() == -1)
		{
			button->boom();
			return -1;
		}
		else
		{
			if (button->isFlagged())
				button->unflag();
			if (button->isConfused())
				button->unconfuse();
			button->setClicked(true);
			button->disply();
			sweptCount++;
			if (button->getValue() == 0)
				sweptCount += buttonDiffusion(button);
		}
	}
	return sweptCount;
}
// Intent: button diffusion
// Pre: button is a MineSweeperElement pointer
// Post: return the number of swept buttons
int GameWindow::buttonDiffusion(MineSweeperElement* button)
{
	int sweptCount = 0;
	Position position = button->getPosition();

	if (button->getPosition().x != 0)
	{
		sweptCount += buttonSweep(objectList[position.y][position.x - 1]);
		if (position.y != 0)
			sweptCount += buttonSweep(objectList[position.y - 1][position.x - 1]);
		if (position.y % mapHeight != mapHeight - 1)
			sweptCount += buttonSweep(objectList[position.y + 1][position.x - 1]);
	}
	if (position.x % mapWidth != mapWidth - 1)
	{
		sweptCount += buttonSweep(objectList[position.y][position.x + 1]);
		if (position.y != 0)
			sweptCount += buttonSweep(objectList[position.y - 1][position.x + 1]);
		if (position.y % mapHeight != mapHeight - 1)
			sweptCount += buttonSweep(objectList[position.y + 1][position.x + 1]);
	}
	if (position.y != 0)
		sweptCount += buttonSweep(objectList[position.y - 1][position.x]);
	if (position.y % mapHeight != mapHeight - 1)
		sweptCount += buttonSweep(objectList[position.y + 1][position.x]);
	return sweptCount;
}
// Intent: button sign
// Pre: button is a MineSweeperElement pointer
// Post: return 1 if the button is flagged, return -1 if the button is confused, return 0 if the button is unflagged
int GameWindow::buttonSign(MineSweeperElement* button)
{

	if (button->isFlagged())
	{
		button->unflag();
		button->confuse();
		return 0;
	}
	else if (button->isConfused())
	{
		button->unconfuse();
		return -1;
	}
	else
	{
		button->flag();
		return 1;
	}
}
// Intent: print the game board on the console
// Pre: no variable requirement
// Post: no return
void GameWindow::printGameBoard()
{
	std::cout << "<Print GameBoard> : " << std::endl;
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (objectList[i][j]->isFlagged())
				std::cout << "f ";
			else if (objectList[i][j]->isSwept() && objectList[i][j]->getValue() < 0)
				std::cout << "X ";
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
// Intent: print the game state on the console
// Pre: no variable requirement
// Post: no return
void GameWindow::printGameState()
{
	std::cout << "<Print GameState> : " << std::endl;
	if (status)
		std::cout << "Playing" << std::endl;
	else
		std::cout << "GameOver" << std::endl;
}
// Intent: print the game answer on the console
// Pre: no variable requirement
// Post: no return
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
// Intent: print the game map on the console
// Pre: no variable requirement
// Post: no return
void GameWindow::printBombCount()
{
	std::cout << "<Print BombCount> : " << std::endl;
	std::cout << mapMines << std::endl;
}
// Intent: print the game map on the console
// Pre: no variable requirement
// Post: no return
void GameWindow::printOpenBlankCount()
{
	std::cout << "<Print OpenBlankCount> : " << std::endl;
	std::cout << openedBlanks << std::endl;
}
// Intent: print the game map on the console
// Pre: no variable requirement
// Post: no return
void GameWindow::printRemainBlankCount()
{
	std::cout << "<Print RemainBlankCount> : " << std::endl;
	std::cout << mapBlanks - openedBlanks << std::endl;
}
// Intent: print the game map on the console
// Pre: no variable requirement
// Post: no return
void GameWindow::printFlagCount()
{
	std::cout << "<Print FlagCount> : " << std::endl;
	std::cout << flags << std::endl;
}
