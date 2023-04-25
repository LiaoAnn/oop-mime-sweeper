#include "CommandMap.h"
#include "BaseMineSweeperElement.h"
#include <iostream>
#include "RunMode.h"

const char MINE = 'X';
const char EMPTY = 'O';
int** layout;
BaseMineSweeperElement*** objectList;
int openedBlanks = 0;
int mapBlanks = 0;
int boomBlanks = 0;
int mapRow = 0,
mapCol = 0;

void LoadBoardFile(QString fileName)
{
	QStringList lines = LoadFile(fileName);
	QStringList mapSize = lines[0].split(" ");

	int row = mapSize[0].toInt();
	int col = mapSize[1].toInt();
	layout = new int* [row];
	mapBlanks = 0;
	openedBlanks = 0;
	mapRow = row;
	mapCol = col;

	lines = lines.mid(1);

	for (int i = 0; i < row; i++)
	{
		layout[i] = new int[col];
		for (int j = 0; j < col; j++)
		{
			if (lines[i][j] == MINE)
			{
				// Set mine
				layout[i][j] = -1;
			}
			else if (lines[i][j] == EMPTY)
			{
				// Set empty
				layout[i][j] = 0;
				++mapBlanks;
			}
		}
	}

	// Fill in the numbers
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
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
			if (i > 0 && j < col - 1 && layout[i - 1][j + 1] == -1)
			{
				++count;
			}
			if (j > 0 && layout[i][j - 1] == -1)
			{
				++count;
			}
			if (j < col - 1 && layout[i][j + 1] == -1)
			{
				++count;
			}
			if (i < row - 1 && j > 0 && layout[i + 1][j - 1] == -1)
			{
				++count;
			}
			if (i < row - 1 && layout[i + 1][j] == -1)
			{
				++count;
			}
			if (i < row - 1 && j < col - 1 && layout[i + 1][j + 1] == -1)
			{
				++count;
			}
			layout[i][j] = count;
		}
	}

	// Init MineSweeperElement
	objectList = new BaseMineSweeperElement * *[row];
	for (int i = 0; i < row; i++)
	{
		objectList[i] = new BaseMineSweeperElement * [col];
		for (int j = 0; j < col; j++)
		{
			BaseMineSweeperInput* input = new BaseMineSweeperInput();
			Position pos = { j, i };
			input->position = &pos;
			input->value = layout[i][j];
			objectList[i][j] = new BaseMineSweeperElement(input);
		}
	}
}

void GenerateMapCountMine(int row, int col, int mineCount)
{
	mapBlanks = row * col - mineCount;
	openedBlanks = 0;
	layout = new int* [row];
	mapRow = row;
	mapCol = col;
	for (int i = 0; i < row; i++)
	{
		layout[i] = new int[col];
		for (int j = 0; j < col; j++)
		{
			layout[i][j] = 0;
		}
	}

	// Randomly generate mines
	std::srand(std::time(nullptr));
	for (int i = 0; i < mineCount;)
	{
		int x = std::rand() % col;
		int y = std::rand() % row;
		if (layout[y][x] != -1)
		{
			layout[y][x] = -1;
			++i;
		}
		else
			continue;
	}

	// Fill in the numbers
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
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
			if (i > 0 && j < col - 1 && layout[i - 1][j + 1] == -1)
			{
				++count;
			}
			if (j > 0 && layout[i][j - 1] == -1)
			{
				++count;
			}
			if (j < col - 1 && layout[i][j + 1] == -1)
			{
				++count;
			}
			if (i < row - 1 && j > 0 && layout[i + 1][j - 1] == -1)
			{
				++count;
			}
			if (i < row - 1 && layout[i + 1][j] == -1)
			{
				++count;
			}
			if (i < row - 1 && j < col - 1 && layout[i + 1][j + 1] == -1)
			{
				++count;
			}
			layout[i][j] = count;
		}
	}

	// Init MineSweeperElement
	objectList = new BaseMineSweeperElement * *[row];
	for (int i = 0; i < row; i++)
	{
		objectList[i] = new BaseMineSweeperElement * [col];
		for (int j = 0; j < col; j++)
		{
			BaseMineSweeperInput* input = new BaseMineSweeperInput();
			Position pos = { j, i };
			input->position = &pos;
			input->value = layout[i][j];
			objectList[i][j] = new BaseMineSweeperElement(input);
		}
	}
}

void GenerateMapRateMine(int row, int col, double mineRate)
{
	const int mineCount = row * col * mineRate;
	GenerateMapCountMine(row, col, mineCount);
}

bool LeftClick(int row, int col)
{
	if (row < 0 || col < 0)
		return false;
	if (row >= mapRow || col >= mapCol)
		return false;

	BaseMineSweeperElement* curr = objectList[row][col];
	if (curr->isFlagged() || curr->isConfused())
		return false;
	if (curr->isSwept())
		return false;

	int returnSignal = curr->sweep();
	openedBlanks += returnSignal;
	if (returnSignal == -1)
	{
		std::cout << "You lose!" << std::endl;
		GameGlobal::gameState = GameState::END;
		GameGlobal::isGameEnd = true;
		GameGlobal::isGameWin = false;
	}
	if (openedBlanks == mapBlanks)
	{
		std::cout << "You win!" << std::endl;
		GameGlobal::gameState = GameState::END;
		GameGlobal::isGameEnd = true;
		GameGlobal::isGameWin = true;
	}

	return true;
}

bool RightClick(int row, int col)
{
	if (row < 0 || col < 0)
		return false;
	if (row >= mapRow || col >= mapCol)
		return false;

	BaseMineSweeperElement* curr = objectList[row][col];
	if (curr->isSwept())
		return false;
	if (curr->isFlagged())
	{
		curr->unflag();
		curr->setConfused(true);
	}
	else if (curr->isConfused())
		curr->unconfuse();
	else
		curr->setFlagged(true);
	return true;
}

/**
 * Intent: Reset the map
 * Pre:
 * Post:
 */
bool ResetMap()
{
	// Delete objectList
	int row = sizeof(objectList) / sizeof(objectList[0]);
	int col = sizeof(objectList[0]) / sizeof(objectList[0][0]);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			delete objectList[i][j];
		}
		delete[] objectList[i];
	}
	delete[] objectList;

	// Delete layout
	for (int i = 0; i < row; i++)
	{
		delete[] layout[i];
	}
	delete[] layout;

	// Reset status
	openedBlanks = 0;
	mapBlanks = 0;

	return true;
}

/**
 * Intent: Print the map
 * Pre:
 * Post:
 */
QString PrintMap()
{
	int row = mapRow;
	int col = mapCol;
	QString resultString = "", temp = "";

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			BaseMineSweeperElement* curr = objectList[i][j];
			if (curr->isFlagged())
				temp = "f";
			else if (curr->isConfused())
				temp = "?";
			else if (curr->isSwept())
				temp = QString::number(curr->getValue());
			else
				temp = "#";
			temp += " ";

			resultString += temp;
			std::cout << temp.toStdString();
		}

		// If not last row, add new line
		if (i < row - 1)
			resultString += "\r\n";
		std::cout << std::endl;
	}

	resultString = "\r\n" + resultString;
	return resultString;
}

/**
 * Intent: Print the answer
 * Pre:
 * Post:
 */
QString PrintAnswer()
{
	int row = mapRow;
	int col = mapCol;
	QString resultString = "";

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			const int value = layout[i][j];
			const char output = value == -1
				? 'X'
				: value + 48;

			resultString += output;
			resultString += " ";
			std::cout << output << " ";
		}

		// If not last row, add new line
		if (i < row - 1)
			resultString += "\r\n";
		std::cout << std::endl;
	}

	resultString = "\r\n" + resultString;
	return resultString;
}

/**
 * Intent: Print the game state
 * Pre:
 * Post:
 */
QString PrintGameState()
{
	if (GameGlobal::gameState == GameState::STANDBY)
		return "Standby";
	else if (GameGlobal::gameState == GameState::END)
		return "GameOver";
	else if (GameGlobal::gameState == GameState::PLAYING)
		return "Playing";

	return "";
}

/**
 * Intent: Print the bomb count
 * Pre:
 * Post:
 */
QString PrintBombCount()
{
	int bombCount = 0;
	int row = mapRow;
	int col = mapCol;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			BaseMineSweeperElement* curr = objectList[i][j];
			if (curr->getValue() == -1)
				bombCount++;
		}
	}

	return QString::number(bombCount);
}

/**
 * Intent: Print the flag count
 * Pre:
 * Post:
 */
QString PrintFlagCount()
{
	int flagCount = 0;
	int row = mapRow;
	int col = mapCol;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			BaseMineSweeperElement* curr = objectList[i][j];
			if (curr->isFlagged())
				flagCount++;
		}
	}
	return QString::number(flagCount);
}

/**
 * Intent: Print the confused count
 * Pre:
 * Post:
 */
QString PrintOpenBlankCount()
{
	int openBlanks = openedBlanks;
	return QString::number(openBlanks);
}

/**
 * Intent: Print the remain blank count
 * Pre:
 * Post:
 */
QString PrintRemainBlankCount()
{
	int remainBlanks = mapBlanks - openedBlanks;
	return QString::number(remainBlanks);;
}