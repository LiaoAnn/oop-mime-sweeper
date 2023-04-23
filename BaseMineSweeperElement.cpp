#include "BaseMineSweeperElement.h"
#include "BaseMineSweeperInput.h"

// Constructor
BaseMineSweeperElement::BaseMineSweeperElement() 
{
	this->value = 0;
	this->position = { 0,0 };
	this->serialNumber = m_objects.size();
	// Add to object list
	m_objects.push_back(this);
}
BaseMineSweeperElement::BaseMineSweeperElement(BaseMineSweeperInput* input)
{
	// Initialize variable
	this->value = input->value;
	if (this->value == -1)
		mineBlocks++;
	else
		safeBlocks++;
	this->position = *input->position;
	this->serialNumber = m_objects.size();
	// Add to object list
	m_objects.push_back(this);
}


// Destructor
BaseMineSweeperElement::~BaseMineSweeperElement()
{
	mineBlocks = 0;
	safeBlocks = 0;
}

int BaseMineSweeperElement::sweep()
{
	int sweptCount = 0;
	if (this->swept == false && this->confused == false && this->flagged == false)
	{
		if (this->value == -1)
		{
			//this->boom();
			return -1;
		}
		else
		{
			if (this->isFlagged())
				this->unflag();
			if (this->isConfused())
				this->unconfuse();
			this->swept = true;
			//this->disply();
			sweptCount++;
			sweptCount += this->diffusion();
		}
	}
	return sweptCount;
}

int BaseMineSweeperElement::diffusion()
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
				sweptCount += m_objects[serialNumber - width - 1]->sweep();
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

void BaseMineSweeperElement::flag()
{
	this->setFlagged(true);
}
void BaseMineSweeperElement::unflag()
{
	this->setFlagged(false);
}
void BaseMineSweeperElement::confuse()
{
	this->setConfused(true);
}
void BaseMineSweeperElement::unconfuse()
{
	this->setConfused(false);
}

// Get Position 
Position BaseMineSweeperElement::getPosition()
{
	return this->position;
}

// Get Value
int BaseMineSweeperElement::getValue()
{
	return this->value;
}

// Is Clicked
bool BaseMineSweeperElement::isSwept()
{
	return this->swept;
}

// Is Flagged
bool BaseMineSweeperElement::isFlagged()
{
	return this->flagged;
}

// Is Confused
bool BaseMineSweeperElement::isConfused()
{
	return this->confused;
}

// Get Serial Number
int BaseMineSweeperElement::getSerialNumber()
{
	return this->serialNumber;
}

// Set Clicked
void BaseMineSweeperElement::setClicked(bool isClicked)
{
	this->swept = isClicked;
}

// Set Flagged
void BaseMineSweeperElement::setFlagged(bool isFlagged)
{
	this->flagged = isFlagged;
}
// Set Confused
void BaseMineSweeperElement::setConfused(bool isConfused)
{
	this->confused = isConfused;
}

std::vector<BaseMineSweeperElement*> BaseMineSweeperElement::m_objects;
int BaseMineSweeperElement::safeBlocks = 0;
int BaseMineSweeperElement::mineBlocks = 0;