#pragma once

#include "MineSweeperInput.h"
#include "qpushbutton.h"
#include "qstring.h"
#include "./Positioin.h"
#include <string>
#include <vector>

class MineSweeperElement : public QPushButton
{
	Q_OBJECT

private:
	MineSweeperInput* input;
	bool swept = false;
	bool flagged = false;
	bool confused = false;
	int serialNumber = 0;
	int value = 0;
	static int safeBlocks;
	static int mineBlocks;
	QString textColor = "Black";
	QString backGroundColor = "White";
	Position position;
public:
	static std::vector<MineSweeperElement*> m_objects; // Store all objects
	MineSweeperElement(MineSweeperInput* input);
	~MineSweeperElement();

	void onButtonLeftClicked();
	void onButtonRightClicked();
	void diffusion();
	void sweep();
	void flag();
	void unflag();
	void confuse();
	void unconfuse();
	void disply();
	void boom();
	void win();

	Position getPosition();
	bool getMine();
	bool isSwept();
	bool isFlagged();
	bool isConfused();
	int getSerialNumber();
	int getValue();

	void setClicked(bool isClicked);
	void setFlagged(bool isFlagged);
	void setConfused(bool isConfused);
	void setText(QString text);
	void setIcon(QString icon);
	void setBackGroundColor(QString);
	void setTextColor(QString);
};