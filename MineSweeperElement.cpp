#include "./MineSweeperElement.h"
#include "./MineSweeperInput.h"
#include "./Positioin.h"
#include <iostream>
#include <vector>
#include <Qmessagebox>
// Constructor
MineSweeperElement::MineSweeperElement(MineSweeperInput* input)
{
	this->input = input;
	this->value = input->value; // Set value
	if (this->value == -1)
		mineBlocks++;
	else
		safeBlocks++;
	this->position = *input->position; // Set position
	this->setParent(input->parent);
	// Create button and adding it to the layout
	this->setGeometry(10 + (input->position->x * 30), 20 + (input->position->y * 30), 30, 30);
	this->show();
	this->serialNumber = m_objects.size();
	// Connect click event
	QObject::connect(this, &QPushButton::clicked, this, &MineSweeperElement::onButtonLeftClicked);
	this->setContextMenuPolicy(Qt::CustomContextMenu); // to link menu event to button
	connect(this, &QPushButton::customContextMenuRequested, this, &MineSweeperElement::onButtonRightClicked); // used menu event as a right click event
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
void MineSweeperElement::onButtonRightClicked()
{
	if (!swept)
	{
		if (flagged)
		{
			unflag();
			confuse();
		}
		else if (confused)
		{
			unconfuse();
		}
		else
		{
			flag();
		}
	}
}
void MineSweeperElement::sweep()
{
	if (this->swept == false && this->confused == false && this->flagged == false)
	{

		if (this->value == -1)
			this->boom();
		else
		{
			this->swept = true;
			this->disply();
			this->diffusion();
			safeBlocks--;
		}
	}
	if (safeBlocks == 0)
	{
		win();
	}
}
void MineSweeperElement::diffusion()
{
	int width = m_objects[m_objects.size() - 1]->position.x + 1;
	int height = m_objects[m_objects.size() - 1]->position.y + 1;
	if (this->value == 0)
	{
		if (position.x != 0)
		{
			m_objects[serialNumber - 1]->sweep();
			if (position.y != 0)
				m_objects[serialNumber - width - 1]->sweep();
			if (position.y % height != height - 1)
				m_objects[serialNumber + width - 1]->sweep();
		}
		if (position.x % width != width - 1)
		{
			m_objects[serialNumber + 1]->sweep();
			if (position.y != 0)
				m_objects[serialNumber - width + 1]->sweep();
			if (position.y % height != height - 1)
				m_objects[serialNumber + width + 1]->sweep();
		}
		if (position.y != 0)
			m_objects[serialNumber - width]->sweep();
		if (position.y % height != height - 1)
			m_objects[serialNumber + width]->sweep();
	}
}
void MineSweeperElement::flag()
{

	this->setStyleSheet("border: 1px solid gray; border-radius: 5px; background-color: #FF0000;");
	this->setText("F");
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
	this->setStyleSheet("border: 1px solid gray; border-radius: 5px; background-color: #FFF000;");
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
	this->setText(QString::number(this->value));
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
	// pop a message box
	QMessageBox::information(this, "Boom", "You lose!");

}

void MineSweeperElement::win()
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->setDisabled(true);
	}
	safeBlocks++;
	// pop a message box
	QMessageBox::information(input->parent, "You Win", "You Win");

}


// Get Position
Position MineSweeperElement::getPosition()
{
	return this->position;
}

// Get Mine
bool MineSweeperElement::getMine()
{
	return this->input->isMine;
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
