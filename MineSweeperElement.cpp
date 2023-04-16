#include "./MineSweeperElement.h"
#include "./MineSweeperInput.h"
#include <iostream>

// Constructor
MineSweeperElement::MineSweeperElement(MineSweeperInput* input)
{
	this->input = input;
	this->setParent(input->parent);
	// Create button and adding it to the layout
	this->setGeometry(10 + (input->position->x * 30), 10 + (input->position->y * 30), 30, 30);
	this->show();

	// Connect click event
	QObject::connect(this, &QPushButton::clicked, this, &MineSweeperElement::Click);
}

// Destructor
MineSweeperElement::~MineSweeperElement()
{
}

// Click
void MineSweeperElement::Click()
{
	std::cout << "Click" << std::endl;
	if (this->isClicked()) // Right Click
	{
		this->setFlagged(!this->isFlagged());
		return;
	}
	else // Left Click
	{
		this->setClicked(true);
		if (this->getMine())
		{
			this->setText("X");
		}
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