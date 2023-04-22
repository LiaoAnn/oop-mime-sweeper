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

// Click
void MineSweeperElement::onButtonLeftClicked()
{
	if (!this->swept && !this->flagged && !this->confused)
		this->sweep();
}
int MineSweeperElement::onButtonRightClicked()
{
	if (!swept)
	{
		if (flagged)
		{			
			unflag();
			confuse();
			return 0;
		}
		else if (confused)
		{
			unconfuse();
			return -1;
		}
		else
		{
			flag();
			return 1;
		}
	}
}
int MineSweeperElement::sweep()
{
	int sweptCount = 0;
	if (this->swept == false && this->confused == false && this->flagged == false)
	{
		if (this->value == -1)
		{			
			this->boom();
			return -1;
		}
		else
		{
			this->swept = true;
			this->disply();
			sweptCount++;
			sweptCount += this->diffusion();
		}
	}
	return sweptCount;
}
int MineSweeperElement::diffusion()
{
	int sweptCount = 0;
	int width = m_objects[m_objects.size() - 1]->position.x + 1;
	int height = m_objects[m_objects.size() - 1]->position.y + 1;
	if (this->value == 0)
	{
		if (position.x != 0)
		{
			sweptCount += m_objects[serialNumber - 1]->sweep();
			if (position.y != 0)
				sweptCount+=m_objects[serialNumber - width - 1]->sweep();
			if (position.y % height != height - 1)
				sweptCount += m_objects[serialNumber + width - 1]->sweep();
		}
		if (position.x % width != width - 1)
		{
			sweptCount += m_objects[serialNumber + 1]->sweep();
			if (position.y != 0)
				sweptCount += m_objects[serialNumber - width + 1]->sweep();
			if (position.y % height != height - 1)
				sweptCount += m_objects[serialNumber + width + 1]->sweep();
		}
		if (position.y != 0)
			sweptCount += m_objects[serialNumber - width]->sweep();
		if (position.y % height != height - 1)
			sweptCount += m_objects[serialNumber + width]->sweep();
	}
	return sweptCount;
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
	if (this->value != 0 && this->value != -1)
		this->setText(QString::number(this->value));
	if (this->value == 0)
	{
		setBackGroundColor("#bbbbbb");
	}
	if (this->value == -1)
	{
		this->setIcon("boom.gif");
		this->setText("");
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
	for (int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i]->value == -1)
			m_objects[i]->disply();
		m_objects[i]->setDisabled(true);
	}
}

void MineSweeperElement::win()
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->setDisabled(true);
	}
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