#pragma once

#include "MineSweeperElement.h"
#include "CommandMode.h"
#include "MineSweeperElement.h"
#include "qstring.h"

void LoadBoardFile(QString fileName);
void GenerateMapCountMine(int row, int col, int mineCount);
void GenerateMapRateMine(int row, int col, double mineRate);
bool LeftClick(int row, int col);
bool RightClick(int row, int col);
bool ResetMap();

QString PrintMap();
QString PrintAnswer();
QString PrintGameState();
QString PrintGameState();
QString PrintBombCount();
QString PrintFlagCount();
QString PrintOpenBlankCount();
QString PrintRemainBlankCount();


