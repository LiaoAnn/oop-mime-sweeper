/***********************************************************************
 * File: CommandMap.h
 * Author: �Ӫîa
 * Create Date: 2023/04/16
 * Editor: �Ӫîa�B���ʦw
 * Update Date: 2023/04/26
 * Description: Command Map header
***********************************************************************/
#pragma once
#ifndef CommandMap_H
#define CommandMap_H
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
#endif


