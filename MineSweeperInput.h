/***********************************************************************
 * File: MineSweeperInput.h
 * Author: ���ʦw
 * Create Date: 2023/04/16
 * Editor: ���ʦw
 * Update Date: 2023/04/26
 * Description: MineSweeperInput struct
***********************************************************************/
#pragma once
#ifndef MineSweeperInput_H
#define MineSweeperInput_H
#include "qwidget.h"
#include "BaseMineSweeperInput.h"

struct MineSweeperInput: public BaseMineSweeperInput
{
	QWidget* parent = Q_NULLPTR;
};
#endif
