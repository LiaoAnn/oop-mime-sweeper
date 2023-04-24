#pragma once

#include "BaseMineSweeperInput.h"
#include <string>
#include <vector>

class BaseMineSweeperElement
{
protected:
	bool swept = false;
	bool flagged = false;
	bool confused = false;
	int serialNumber = 0;
	int value = 0;
	static int safeBlocks;
	static int mineBlocks;
	Position position;

public:
	static std::vector<BaseMineSweeperElement*> m_objects;
	// Constructor & Destructor
	BaseMineSweeperElement();
	BaseMineSweeperElement(BaseMineSweeperInput* input);
	~BaseMineSweeperElement();
	// Events
	int diffusion();
	int  sweep();
	void flag();
	void unflag();
	void confuse();
	void unconfuse();
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
};