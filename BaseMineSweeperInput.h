/***********************************************************************
 * File: BaseMineSweeperInput.h
 * Author: ¹ù§Ê¦w
 * Create Date: 2023/04/16
 * Editor: ¹ù§Ê¦w¡BÃÓªÃ®a
 * Update Date: 2023/04/26
 * Description: BaseMineSweeperInput struct
***********************************************************************/
#pragma once
#ifndef BaseMineSweeperInput_H
#define  BaseMineSweeperInput_H

#include "Positioin.h"

struct BaseMineSweeperInput
{
	Position* position;
	int value;
	bool isMine;
};
#endif
