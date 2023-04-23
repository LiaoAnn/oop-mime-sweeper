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
	QString printString = "";

	// Read file
	QStringList lines = LoadFile(inputFileName);

	QFile file(outputFileName);
	file.open(QIODevice::WriteOnly);
	QTextStream out(&file);

	for (int i = 0; i < lines.size(); i++)
	{
		QStringList commandList = lines[i].split(" ");

		if (commandList[0] != PRINT_COMMAND)
		{
			// Execute command
			isSuccess = ExecuteCommand(commandList);

			QString result = isSuccess ? "Success" : "Fail";
			QString output = QString("<%1> : %2\r\n").arg(lines[i]).arg(result);
			out << output;
		}
		else
		{
			printString = ExecutePrintCommand(commandList);

			QString output = QString("<%1>\r\n%2").arg(lines[i], printString);
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
	QString line = "";

	while ((line = stream.readLine()) != QString("Quit"))
	{
		QStringList commandList = line.split(" ");
		ExecuteCommand(commandList);
	}

	return 0;
}

