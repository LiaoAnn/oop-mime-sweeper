/***********************************************************************
 * File: RunMode.h
 * Author: �Ӫîa
 * Create Date: 2023/04/16
 * Editor: �Ӫîa�B���ʦw
 * Update Date: 2023/04/26
 * Description: Run mode selection
***********************************************************************/
#pragma once
#ifndef RunMode_H
#define RunMode_H
#include <QtWidgets/QApplication>
#include <qdebug.h>
#include <qbuffer.h>
#include <vector>
#include <qstring.h>
#include "StartWindow.h"
#include "CommandMode.h"
#include "CommandLine.h"
#include <iostream>

using namespace std;

int RunGUI(int argc, char* argv[]);
int RunCommandFile(char* arg1, char* arg2);
int RunCommandInput();

enum GameState
{
	STANDBY,
	PLAYING,
	END
};

class GameGlobal {
public:
	static GameState gameState;
	static bool loadedMap;
	static bool isGameEnd;
	static bool isGameWin;
};
# endif
