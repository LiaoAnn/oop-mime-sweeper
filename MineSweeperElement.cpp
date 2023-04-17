#include "./MineSweeperElement.h"
#include "./MineSweeperInput.h"
#include <iostream>
#include <vector>
// Constructor
MineSweeperElement::MineSweeperElement(MineSweeperInput* input)
{
	this->input = input;
	this->setParent(input->parent);
	// Create button and adding it to the layout
	this->setGeometry(10 + (input->position->x * 72), 20 + (input->position->y * 72), 72, 72);
	this->show();
	this->serialNumber  = m_objects.size();
	// Connect click event
	QObject::connect(this, &QPushButton::clicked, this, &MineSweeperElement::Click);
	this->setContextMenuPolicy(Qt::CustomContextMenu); // to link menu event to button
	connect(this, &QPushButton::customContextMenuRequested, this, &MineSweeperElement::onButtonRightClicked); // used menu event as a right click event
	// Add to object list
	m_objects.push_back(this);
}

// Destructor
MineSweeperElement::~MineSweeperElement()
{
}

// Click
void MineSweeperElement::Click()
{
	std::cout << "Click" << std::endl;
	if (!this->isFlagged())
	{
		if (!this->isClicked()) // Right Click
		{
			int a = this->serialNumber;
			this->setText(QString::number(a));			
			this->setStyleSheet("background-color: #FFFFAA");
			this->setClicked(true);
			return;
		}
	}
}
void MineSweeperElement::POP()
{
	std::cout << "Click" << std::endl;
	if (!this->isFlagged())
	{
		if (!this->isClicked()) // Right Click
		{
			int a = this->serialNumber;
			this->setText(QString::number(a));
			this->setStyleSheet("background-color: #FFFFAA");
			this->setClicked(true);
			return;
		}
	}
}
void MineSweeperElement::onButtonRightClicked(const QPoint& pos)
{
	std::cout << "Right Click" << std::endl;
	if (!this->isClicked())
	{
		if (!this->isFlagged()) // Right Click
		{
			this->setText("F");
			this->setStyleSheet("background-color: #AAFFAA");
		}
		else
		{
			this->setText("");
			this->setStyleSheet("background-color: #FFFFFF");
		}
		this->setFlagged(!this->isFlagged());
		return;
	}
}
// Get Position
Position* MineSweeperElement::getPosition()
{
	return this->input->position;
}

// Get Mine
bool MineSweeperElement::getMine()
{
	return this->input->isMine;
}

// Get Mine Text
char MineSweeperElement::getMineText()
{
	return this->mineText;
}

// Is Clicked
bool MineSweeperElement::isClicked()
{
	return this->clicked;
}

// Is Flagged
bool MineSweeperElement::isFlagged()
{
	return this->flagged;
}

// Get Serial Number
int MineSweeperElement::getSerialNumber()
{
	return this->serialNumber;
}

// Set Clicked
void MineSweeperElement::setClicked(bool isClicked)
{
	this->clicked = isClicked;
}

// Set Flagged
void MineSweeperElement::setFlagged(bool isFlagged)
{
	this->flagged = isFlagged;
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
