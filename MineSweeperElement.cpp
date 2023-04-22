#include "./MineSweeperElement.h"
#include "./MineSweeperInput.h"
#include "./Positioin.h"
#include "GameWindow.h"
#include <iostream>
#include <vector>
#include <Qmessagebox>
// Constructor
MineSweeperElement::MineSweeperElement(MineSweeperInput* input)
{
	// Initialize variable
	this->value = input->value;
	if (this->value == -1)
		mineBlocks++;
	else
		safeBlocks++;
	this->position = *input->position;
	this->setParent(input->parent);
	// Create button and adding it to the layout
	this->setGeometry(10 + (input->position->x * 30), 30 + (input->position->y * 30), 30, 30);
	delete input; // Delete input
	this->show();
	this->serialNumber = m_objects.size();
	// Add to object list
	m_objects.push_back(this);
}

// Destructor
MineSweeperElement::~MineSweeperElement()
{
	mineBlocks = 0;
	safeBlocks = 0;
}

void MineSweeperElement::flag()
{
	this->setStyleSheet("border: 1px solid gray; border-radius: 5px; background-color: #5555ff;");
	this->setText("🚩");
	this->setFlagged(true);
}
void MineSweeperElement::unflag()
{
	this->setStyleSheet("");
	this->setText(" ");
	this->setFlagged(false);
}
void MineSweeperElement::confuse()
{
	this->setStyleSheet("border: 1px solid gray; border-radius: 5px; background-color: #fff555;");
	this->setText("?");
	this->setConfused(true);
}
void MineSweeperElement::unconfuse()
{
	this->setStyleSheet("");
	this->setText(" ");
	this->setConfused(false);
}

void MineSweeperElement::disply()
{
	// value = -2 means boom
	// value = -1 means mine
	// value = 0 means empty
	// value = 1 means 1 mine around
	// value = 2 means 2 mine around
	// ...
	if (this->value > 0)
		this->setText(QString::number(this->value));
	if (this->value == -2)
	{
		this->setIcon("boom.gif");
		setBackGroundColor("#ff4444");
	}
	if (this->value == -1)
	{
		if (!flagged)
			this->setIcon("boom.gif");
	}
	if (this->value == 0)
	{
		setBackGroundColor("#bbbbbb");
	}
	if (this->value == 1)
	{
		setTextColor("#006aff");
		setBackGroundColor("#adcfff");
	}
	if (this->value == 2)
	{
		setTextColor("#80ff00");
		setBackGroundColor("#e1ffc2");
	}
	if (this->value == 3)
	{
		setTextColor("#cf0a28");
		setBackGroundColor("#ffc7cf");
	}
	if (this->value == 4)
	{
		setTextColor("#000787");
		setBackGroundColor("#c9ccff");
	}
	if (this->value == 5)
	{
		setTextColor("#000000");
		setBackGroundColor("#fac707");
	}
	if (this->value == 6)
	{
		setTextColor("#00ffff");
		setBackGroundColor("#c7ffff");
	}
	if (this->value == 7)
	{
		setTextColor("#ffffff");
		setBackGroundColor("#c7c7c7");
	}
	if (this->value == 8)
	{
		setTextColor("#808080");
		setBackGroundColor("#e1e1e1");
	}
}
void MineSweeperElement::setBackGroundColor(QString color)
{
	this->backGroundColor = color;
	this->setStyleSheet("border: 1px solid gray; border-radius: 5px; background-color: " + backGroundColor + "; color: " + textColor);
}

void MineSweeperElement::setTextColor(QString color)
{
	this->textColor = color;
	this->setStyleSheet("border: 1px solid gray; border-radius: 5px; background-color: " + backGroundColor + "; color: " + textColor);
}
void MineSweeperElement::boom()
{
	this->value = -2;
}
// Get Position 
Position MineSweeperElement::getPosition()
{
	return this->position;
}

// Get Value
int MineSweeperElement::getValue()
{
	return this->value;
}

// Is Clicked
bool MineSweeperElement::isSwept()
{
	return this->swept;
}

// Is Flagged
bool MineSweeperElement::isFlagged()
{
	return this->flagged;
}

// Is Confused
bool MineSweeperElement::isConfused()
{
	return this->confused;
}

// Get Serial Number
int MineSweeperElement::getSerialNumber()
{
	return this->serialNumber;
}

// Set Clicked
void MineSweeperElement::setClicked(bool isClicked)
{
	this->swept = isClicked;
}

// Set Flagged
void MineSweeperElement::setFlagged(bool isFlagged)
{
	this->flagged = isFlagged;
}
// Set Confused
void MineSweeperElement::setConfused(bool isConfused)
{
	this->confused = isConfused;
}

// Set Text
void MineSweeperElement::setText(QString text)
{
	this->QPushButton::setText(text);
}

// Set Icon
void MineSweeperElement::setIcon(QString icon)
{
	this->QPushButton::setIcon(QIcon(icon));
}

std::vector<MineSweeperElement*> MineSweeperElement::m_objects;
int MineSweeperElement::safeBlocks = 0;
int MineSweeperElement::mineBlocks = 0;
