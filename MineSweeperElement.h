#pragma once

#include "MineSweeperInput.h"
#include "qpushbutton.h"
#include "qstring.h"
#include <string>
#include <vector>

class MineSweeperElement : public QPushButton
{
	Q_OBJECT

private:
	MineSweeperInput* input;
	bool swept = false;
	bool flagged = false;
	int serialNumber = 0;
	int value = 0;
	QString textColor = "Black";
	QString backGroundColor = "White";
public:
	static std::vector<MineSweeperElement*> m_objects; // Store all objects
	MineSweeperElement(MineSweeperInput* input);
	~MineSweeperElement();

	void onButtonLeftClicked();
	void onButtonRightClicked();
	void diffusion();
	void flag();
	void sweep();
	void unflag();
	void disply();

	Position* getPosition();
	bool getMine();
	bool isSwept();
	bool isFlagged();
	int getSerialNumber();
	int getValue();

	void setClicked(bool isClicked);
	void setFlagged(bool isFlagged);
	void setText(QString text);
	void setIcon(QString icon);
	void setBackGroundColor(QString);
	void setTextColor(QString);
};