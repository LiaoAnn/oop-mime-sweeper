#include "CommandMap.h"


const char MINE = 'O';
const char EMPTY = 'X';

void LoadBoardFile(QString fileName)
{
	QStringList lines = LoadFile(fileName);
	QStringList mapSize = lines[0].split(" ");

	int row = mapSize[0].toInt();
	int col = mapSize[1].toInt();

	lines = lines.mid(1);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (lines[i][j] == MINE)
			{
				// Set mine
				/*
					Write code here
				*/
			}
			else if (lines[i][j] == EMPTY)
			{
				// Set empty
				/*
					Write code here
				*/
			}
		}
	}
}

void GenerateMapCountMine(int row, int col, int mineCount)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			/*
				Write code here
			*/
		}
	}
}

void GenerateMapRateMine(int row, int col, double mineRate)
{

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			/*
				Write code here
			*/
		}
	}
}

void PrintMap()
{
	/*
		Write code here
	*/
}

void LeftClick(int row, int col)
{
	/*
		Write code here
	*/
}

void RightClick(int row, int col)
{
	/*
		Write code here
	*/
}

void ResetMap()
{
	/*
		Write code here
	*/
}

