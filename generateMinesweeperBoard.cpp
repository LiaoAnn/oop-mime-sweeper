/***********************************************************************
 * File: generateMinesweeperBoard.cpp
 * Author: 劉耀恩
 * Create Date: 2023/04/16
 * Editor: 劉耀恩
 * Update Date: 2023/04/26
 * Description: board generator
***********************************************************************/
#include <iostream>
#include "generateMinesweeperBoard.h"
using namespace std; 

// Intent: generate a minesweeper board
// Pre:  width, height, minesCount are all positive integers
// Post: return a 2D array of integers with already sign the mines and numbers
int** generateMinesweeperBoard(int width, int height, int minesCount) {
	// Create the board
	int** layout = new  int* [height];
	for (int i = 0; i < height; ++i)
	{
		layout[i] = new  int[width];
		for (int j = 0; j < width; ++j) 
		{
			layout[i][j] = 0;
		}
	}
	// Randomly generate mines
	std::srand(std::time(nullptr));
	for (int i = 0; i < minesCount;) 
	{
		int x = std::rand() % width;
		int y = std::rand() % height;
		if (layout[y][x] != -1) 
		{
			layout[y][x] = -1;
			++i;
		}
		else
			continue;
	}

	// Fill in the numbers
	for (int i = 0; i < height; ++i) 
	{
		for (int j = 0; j < width; ++j) 
		{
			if (layout[i][j] == -1)
			{
				continue;
			}
			int count = 0;
			if (i > 0 && j > 0 && layout[i - 1][j - 1] == -1) 
			{
				++count;
			}
			if (i > 0 && layout[i - 1][j] == -1) 
			{
				++count;
			}
			if (i > 0 && j < width - 1 && layout[i - 1][j + 1] == -1)
			{
				++count;
			}
			if (j > 0 && layout[i][j - 1] == -1) 
			{
				++count;
			}
			if (j < width - 1 && layout[i][j + 1] == -1) 
			{
				++count;
			}
			if (i < height - 1 && j > 0 && layout[i + 1][j - 1] == -1)
			{
				++count;
			}
			if (i < height - 1 && layout[i + 1][j] == -1)
			{
				++count;
			}
			if (i < height - 1 && j < width - 1 && layout[i + 1][j + 1] == -1) 
			{
				++count;
			}
			layout[i][j] = count;
		}
	}
	return layout;
} 
// Intent: transform a char board to a int board
// Pre: width, height are all positive integers
// Post: return a 2D array of integers with already sign the mines and numbers
int** transformationMinesweeperBoard(char** board, int width, int height)
{
	int** layout = new int* [height];
	for (int i = 0; i < height; ++i)
	{
		layout[i] = new int[width];
		for (int j = 0; j < width; ++j)
		{
			layout[i][j] = 0;
		}
	}
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (board[i][j] == 'X')
			{
				layout[i][j] = -1;
			}
		}
	}
	// Fill in the numbers
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (layout[i][j] == -1)
			{
				layout[i][j] = -1;
				continue;
			}
			int count = 0;
			if (i > 0 && j > 0 && layout[i - 1][j - 1] == -1)
			{
				++count;
			}
			if (i > 0 && layout[i - 1][j] == -1)
			{
				++count;
			}
			if (i > 0 && j < width - 1 && layout[i - 1][j + 1] == -1)
			{
				++count;
			}
			if (j > 0 && layout[i][j - 1] == -1)
			{
				++count;
			}
			if (j < width - 1 && layout[i][j + 1] == -1)
			{
				++count;
			}
			if (i < height - 1 && j > 0 && layout[i + 1][j - 1] == -1)
			{
				++count;
			}
			if (i < height - 1 && layout[i + 1][j] == -1)
			{
				++count;
			}
			if (i < height - 1 && j < width - 1 && layout[i + 1][j + 1] == -1)
			{
				++count;
			}
			layout[i][j] = count;
		}
	}
	return layout;
}