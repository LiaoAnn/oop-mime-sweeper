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
	bool clicked = false;
	bool flagged = false;	
	int serialNumber = 0;	
public:
	static std::vector<MineSweeperElement*> m_objects; // Store all objects
	MineSweeperElement(MineSweeperInput* input);
	~MineSweeperElement();
	
	void Click();
	void POP(); //Just for test
	void onButtonRightClicked(const QPoint& pos);
	char mineText;
	Position* getPosition();
	bool getMine();
	bool isClicked();
	bool isFlagged();
	int getSerialNumber();
	char getMineText();

	void setClicked(bool isClicked);
	void setFlagged(bool isFlagged);
	void setText(QString text);
	void setIcon(QString icon);
};