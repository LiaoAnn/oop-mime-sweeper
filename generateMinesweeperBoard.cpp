#include <iostream>
#include "generateMinesweeperBoard.h"
using namespace std;
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