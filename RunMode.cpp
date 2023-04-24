#include "RunMode.h"

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
	// Read file
	QStringList lines = LoadFile(inputFileName);
	bool isSuccess = false;

	QFile file(outputFileName);
	file.open(QIODevice::WriteOnly);
	QTextStream out(&file);

	for (int i = 0; i < lines.size(); i++)
	{
		// Execute command
		isSuccess = ExecuteCommand(lines[i], outputFileName);

		QString result = isSuccess ? "Success" : "Fail";
		QString output = QString("<%1> : %2\r\n").arg(lines[i]).arg(result);
		out << output;
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
		ExecuteCommand(line, "");
	}

	return 0;
}

