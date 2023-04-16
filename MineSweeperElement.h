#pragma once

#include "MineSweeperInput.h"
#include "qpushbutton.h"
#include "qstring.h"
#include <string>

class MineSweeperElement : public QPushButton
{
	Q_OBJECT

private:
	MineSweeperInput* input;
	bool clicked = false;
	bool flagged = false;

public:
	MineSweeperElement(MineSweeperInput* input);
	~MineSweeperElement();
	void Click();

	Position* getPosition();
	bool getMine();
	bool isClicked();
	bool isFlagged();

	void setClicked(bool isClicked);
	void setFlagged(bool isFlagged);
	void setText(QString text);
	void setIcon(QString icon);
};