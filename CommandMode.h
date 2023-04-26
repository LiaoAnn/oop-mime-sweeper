/***********************************************************************
 * File: CommandMode.h
 * Author: ÃÓªÃ®a
 * Create Date: 2023/04/16
 * Editor: ÃÓªÃ®a¡B¹ù§Ê¦w
 * Update Date: 2023/04/26
 * Description: Command mode
***********************************************************************/
#pragma once
#ifndef CommandMode_H
#define CommandMode_H
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
bool ExecuteCommand(QStringList commandList);
void LoadCommand(QStringList originCommand);
QString ExecutePrintCommand(QStringList commandList);
#endif
