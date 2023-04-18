#include "QtWidgetsApplication.h"
#include <iostream>
#include "MineSweeperElement.h"
#include "generateMinesweeperBoard.h"
#include "StartWindow.h"

QtWidgetsApplication::QtWidgetsApplication(QWidget* parent, StartWindow* from, int width, int height, int mines)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	int** layout = generateMinesweeperBoard(width, height, mines);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			const int index = i * height + j;
			MineSweeperInput* input = new MineSweeperInput();
			Position position = { j, i };
			input->position = &position;
			input->parent = this;
			input->value = layout[i][j];
			this->from = from;
			MineSweeperElement* element = new MineSweeperElement(input);
		}
	}
	for (int i = 0; i < height; i++)
		free(layout[i]);
	free(layout);
}

QtWidgetsApplication::~QtWidgetsApplication()
{}

void QtWidgetsApplication::closeEvent(QCloseEvent* event)
{
	while (MineSweeperElement::m_objects.size() > 0)
	{
		MineSweeperElement* element = MineSweeperElement::m_objects[0];
		element->~MineSweeperElement();
		MineSweeperElement::m_objects.erase(MineSweeperElement::m_objects.begin());
	}

	this->~QtWidgetsApplication();
	from->show();
}