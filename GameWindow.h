/***********************************************************************
 * File: GameWindow.h
 * Author: ¹ù§Ê¦w
 * Create Date: 2023/04/16
 * Editor: ¹ù§Ê¦w¡B¼BÄ£®¦
 * Update Date: 2023/04/26
 * Description: Game Window header
***********************************************************************/
#pragma once
#ifndef GameWindow_H
#define GameWindow_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include "GameWindow.h"
#include "StartWindow.h"
#include "MineSweeperElement.h"
class GameWindow : public QMainWindow
{
	Q_OBJECT
public:
	GameWindow(QWidget*, StartWindow*, int**, int, int, int);
	~GameWindow();
	void drawOut();
	void closeEvent(QCloseEvent*);
	void onButtonLeftClicked();
	void onButtonRightClicked();
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
	QAudioOutput* bgmOutput = nullptr;
	QAudioOutput* clickOutput = nullptr;
	QAudioOutput* boomOutput = nullptr;
	int** layout = nullptr;
	MineSweeperElement*** objectList = nullptr;
	MineSweeperElement** mineList = nullptr;
	int mapWidth = 0;
	int mapHeight = 0;
	int mapMines = 0;
	int mapBlanks = 0;
	int openedBlanks = 0;
	int flags = 0;
	bool status = true; // true: playing, false: game over
	StartWindow* lastWindow;
	Ui::QtWidgetsApplicationClass ui;
};
#endif
