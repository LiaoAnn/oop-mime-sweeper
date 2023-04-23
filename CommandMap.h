#pragma once

#include "MineSweeperElement.h"
#include "CommandMode.h"
#include "MineSweeperElement.h"
#include "qstring.h"

void LoadBoardFile(QString fileName);
void GenerateMapCountMine(int row, int col, int mineCount);
void GenerateMapRateMine(int row, int col, double mineRate);
void PrintMap();
void PrintAnswer();
bool LeftClick(int row, int col);
bool RightClick(int row, int col);
bool ResetMap();
void PrintGameState();
void PrintGameState();
void PrintBombCount();
void PrintFlagCount();
void PrintOpenBlankCount();
void PrintRemainBlankCount();


