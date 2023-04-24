#include "RunMode.h"
#include "CommandMode.h"

GameState GameGlobal::gameState = LOADING;

// GUI Mode
int RunGUI(int argc, char* argv[])
{
	QApplication a(argc, argv);
	StartWindow startWindow;
	startWindow.show();
	return a.exec();
}

// Console Command Mode
int RunCommandFile(char* inputFileName, char* outputFileName)
{
	bool isSuccess = false;
	QString printString = "", result = "", output = "";

	// Read file
	QStringList lines = LoadFile(inputFileName);

	QFile file(outputFileName);
	file.open(QIODevice::WriteOnly);
	QTextStream out(&file);

	for (int i = 0; i < lines.size(); i++)
	{
		QStringList commandList = lines[i].split(" ");

		if (commandList.size() == 0)
			continue;

		if (commandList[0] == QUIT_COMMAND)
		{
			// Execute command
			isSuccess = (GameGlobal::gameState == GameState::END) ? true : false;
			result = isSuccess ? "Success" : "Fail";

			output = QString("<%1> : %2\r\n").arg(lines[i]).arg(result);
			out << output;

			if (isSuccess)
			{
				out.flush();
				exit(1);
			}
		}
		else if (commandList[0] == PRINT_COMMAND)
		{
			printString = ExecutePrintCommand(commandList);

			output = QString("<%1>%2\r\n").arg(lines[i], printString);
			out << output;
		}
		else {
			// Execute command
			isSuccess = ExecuteCommand(commandList);

			result = isSuccess ? "Success" : "Fail";
			output = QString("<%1> : %2\r\n").arg(lines[i]).arg(result);
			out << output;
		}
	}

	file.close();
	return 0;
}

// Console Input Mode
int RunCommandInput()
{
	QTextStream stream(stdin);
	QString line = "", printString = "", result = "", output = "";
	bool isSuccess = false;

	while ((line = stream.readLine()) != QString("Quit"))
	{
		QStringList commandList = line.split(" ");
		ExecuteCommand(commandList);

		if (commandList[0] == PRINT_COMMAND)
		{
			printString = ExecutePrintCommand(commandList);

			output = QString("<%1>%2\r\n").arg(line, printString);
			std::cout << output.toStdString();
		}
		else
		{
			// Execute command
			isSuccess = ExecuteCommand(commandList);

			result = isSuccess ? "Success" : "Fail";
			output = QString("<%1> : %2\r\n").arg(line).arg(result);
			std::cout << output.toStdString();
		}
	}

	return 0;
}

