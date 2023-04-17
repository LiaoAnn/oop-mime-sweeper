#include "QtWidgetsApplication.h"
#include "qstring.h"
#include <iostream>
#include "MineSweeperElement.h"
#include "generateMinesweeperBoard.h"
#include <algorithm>
#include <vector>
#include <time.h>
#include <random>
#include <chrono>


QtWidgetsApplication::QtWidgetsApplication(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	int ** layout = generateMinesweeperBoard(10, 10, 10);
	srand(time(NULL));
	// Create vector
	std::vector<int> mines = std::vector<int>();
	for (int i = 0; i < 100; i++)
		mines.push_back(i);
	std::shuffle(mines.begin(), mines.end(), std::default_random_engine(time(NULL)));
	// Create 10x10 matrix mine sweeper
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			const int index = i * 10 + j;
			MineSweeperInput* input = new MineSweeperInput();
			Position position = { i, j };
			input->position = &position;
			input->parent = this;
			input->isMine = mines[index] >= 90;	
			input->value = layout[i][j];
			MineSweeperElement* element = new MineSweeperElement(input);
		}
	}
}

QtWidgetsApplication::~QtWidgetsApplication()
{}

void QtWidgetsApplication::buttonClicked()
{
	std::cout << "Button clicked" << std::endl;
}
