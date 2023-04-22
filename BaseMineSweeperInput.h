#pragma once

#include "Positioin.h"

struct BaseMineSweeperInput
{
	Position* position;
	int value;
	bool isMine;
};