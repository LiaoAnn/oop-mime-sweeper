/***********************************************************************
 * File: BaseMineSweeperElement.h
 * Author: ¹ù§Ê¦w
 * Create Date: 2023/04/16
 * Editor: ¹ù§Ê¦w¡BÃÓªÃ®a
 * Update Date: 2023/04/26
 * Description: Command map
***********************************************************************/
#pragma once
#ifndef BaseMineSweeperElement_H
#define BaseMineSweeperElement_H

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
#endif
