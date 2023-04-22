#pragma once

#include "qbuffer.h"
#include "qfile.h"
#include <QtWidgets/QApplication>
#include <vector>

using namespace std;

const QString LOAD_COMMAND = "Load";
const QString LOAD_BOARD_FILE = "BoardFile";
const QString LOAD_RANDOM_COUNT = "RandomCount";
const QString LOAD_RANDOM_RATE = "RandomRate";

const QString START_GAME_COMMAND = "StartGame";
const QString PRINT_COMMAND = "Print";
const QString LEFT_CLICK_COMMAND = "LeftClick";
const QString RIGHT_CLICK_COMMAND = "RightClick";
const QString REPLAY_COMMAND = "Replay";
const QString QUIT_COMMAND = "Quit";

QStringList LoadFile(QString fileName);
bool ExecuteCommand(QString command, QString outputFileName);
void LoadCommand(QStringList originCommand);

