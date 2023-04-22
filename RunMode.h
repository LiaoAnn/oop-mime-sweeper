#pragma once

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
	LOADING,
	PLAYING,
	END
};

class GameGlobal {
public:
	static GameState gameState;
};
