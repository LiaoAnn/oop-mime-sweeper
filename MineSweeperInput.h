#pragma once

#include "qwidget.h"
#include "Positioin.h"

struct MineSweeperInput
{
	Position* position;
	QWidget* parent = Q_NULLPTR;
	int value;
	bool isMine;
};