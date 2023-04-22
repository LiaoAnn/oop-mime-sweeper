#pragma once

#include "qwidget.h"
#include "BaseMineSweeperInput.h"

struct MineSweeperInput: public BaseMineSweeperInput
{
	QWidget* parent = Q_NULLPTR;
};