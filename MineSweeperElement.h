#pragma once

#include "MineSweeperInput.h"
#include "qpushbutton.h"
#include "qstring.h"
#include "./Positioin.h"
#include <string>
#include <vector>
#include "BaseMineSweeperElement.h"

class MineSweeperElement : public QPushButton, protected BaseMineSweeperElement
{
	Q_OBJECT

private:
	QString textColor = "Black";
	QString backGroundColor = "White";
public:
	static std::vector<MineSweeperElement*> m_objects;
	// Constructor & Destructor
	MineSweeperElement(MineSweeperInput* input);
	~MineSweeperElement();
	// Events
	void onButtonLeftClicked();
	int onButtonRightClicked();
	int diffusion();
	int  sweep();
	void flag();
	void unflag();
	void confuse();
	void unconfuse();
	void disply();
	void boom();
	void win();
	// Getters 
	Position getPosition();
	bool isSwept();
	bool isFlagged();
	bool isConfused();
	int getSerialNumber();
	int getValue();
	// Setters
	void setClicked(bool isClicked);
	void setFlagged(bool isFlagged);
	void setConfused(bool isConfused);
	void setText(QString text);
	void setIcon(QString icon);
	void setBackGroundColor(QString);
	void setTextColor(QString);
};