#pragma once

#include "MineSweeperElement.h"
#include "CommandMode.h"
#include "MineSweeperElement.h"
#include "qstring.h"

void LoadBoardFile(QString fileName);
void GenerateMapCountMine(int row, int col, int mineCount);
void GenerateMapRateMine(int row, int col, double mineRate);
void PrintMap();
void LeftClick(int row, int col);
void RightClick(int row, int col);
void ResetMap();


