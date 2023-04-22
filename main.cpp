#include <iostream>
#include "RunMode.h"
#include "qstring.h"

const QString COMMAND_FILE_MODE = "CommandFile";
const QString COMMAND_INPUT_MODE = "CommandInput";
const QString GUI_MODE = "GUI";

int main(int argc, char* argv[])
{
	QString mode = "";
	if (argc > 1)
		mode = QString(argv[1]);

	if (mode == COMMAND_FILE_MODE && argc == 4)
	{
		return RunCommandFile(argv[2], argv[3]);
	}
	else if (mode == COMMAND_INPUT_MODE && argc == 3)
	{
		return RunCommandInput();
	}
	else
	{
		return RunGUI(argc, argv);
	}

	return 0;
}
