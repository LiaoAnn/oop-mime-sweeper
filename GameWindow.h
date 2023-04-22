#pragma once
#include <QMainWindow>
#include <QtMultimedia>
#include "GameWindow.h"
#include "ui_QtWidgetsApplication.h"
#include "StartWindow.h"
#include "MineSweeperElement.h"
class GameWindow : public QMainWindow
{
	Q_OBJECT
public:
	GameWindow(QWidget*, StartWindow*, int, int, int);
	GameWindow(QWidget*, StartWindow*, int**, int, int, int);
	~GameWindow();
	void drawOut();
	void closeEvent(QCloseEvent*);
	void onButtonLeftClicked();
	void onButtonRightClicked();
	void showNextButton();
	int buttonSweep(MineSweeperElement*);
	int buttonDiffusion(MineSweeperElement*);
	int buttonSign(MineSweeperElement*);
	// print functions
	void printGameBoard();
	void printGameState();
	void printGameAnswer();
	void printBombCount();
	void printFlagCount();
	void printOpenBlankCount();
	void printRemainBlankCount();
private:
	QTimer* timer = nullptr;
	QMenu* printMenu = nullptr;
	QAudioOutput* audioOutput = nullptr;
	int** layout = nullptr;
	MineSweeperElement*** objectList = nullptr;
	MineSweeperElement** mineList = nullptr;
	int mapWidth = 0;
	int mapHeight = 0;
	int mapMines = 0;
	int mapBlanks = 0;
	int openedBlanks = 0;
	int flags = 0;
	bool status = true;
	StartWindow* lastWindow;
	Ui::QtWidgetsApplicationClass ui;
};