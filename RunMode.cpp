/***********************************************************************
 * File: RunMode.cpp
 * Author: ÃÓªÃ®a
 * Create Date: 2023/04/16
 * Editor: ÃÓªÃ®a¡B¹ù§Ê¦w
 * Update Date: 2023/04/26
 * Description: Run mode selection
***********************************************************************/
#include "RunMode.h"
#include "CommandMode.h"

GameState GameGlobal::gameState = STANDBY;
bool GameGlobal::isGameEnd = false;
bool GameGlobal::isGameWin = false;
bool GameGlobal::loadedMap = false;

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
			result = isSuccess ? "Success" : "Failed";

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

			output = QString("<%1> : %2\r\n").arg(lines[i], printString);
			out << output;
		}
		else if (commandList[0] == LOAD_COMMAND) {
			// Execute command
			isSuccess = ExecuteCommand(commandList);

			result = isSuccess ? "Success" : "Failed";
			output = QString("<%1> : %2\r\n").arg(lines[i]).arg(result);
			out << output;
		} 
		else if (commandList[0] == START_GAME_COMMAND)
		{
			isSuccess = ExecuteCommand(commandList);

			result = isSuccess ? "Success" : "Failed";
			output = QString("<%1> : %2\r\n").arg(lines[i]).arg(result);
			out << output;
		}
		else if (commandList[0] == LEFT_CLICK_COMMAND)
		{
			isSuccess = ExecuteCommand(commandList);

			result = isSuccess ? "Success" : "Failed";
			output = QString("<%1> : %2\r\n").arg(lines[i]).arg(result);
			out << output;

			if (GameGlobal::isGameEnd)
			{
				if (GameGlobal::isGameWin)
					output = QString("You win the game\r\n");
				else
					output = QString("You lose the game\r\n");
				GameGlobal::isGameEnd = false;
				GameGlobal::loadedMap = false;
				out << output;
			}
		}
		else if (commandList[0] == RIGHT_CLICK_COMMAND)
		{
			isSuccess = ExecuteCommand(commandList);

			result = isSuccess ? "Success" : "Failed";
			output = QString("<%1> : %2\r\n").arg(lines[i]).arg(result);
			out << output;
		}
		else if (commandList[0] == REPLAY_COMMAND)
		{
			GameGlobal::loadedMap = false;
			isSuccess = ExecuteCommand(commandList);

			result = isSuccess ? "Success" : "Failed";
			output = QString("<%1> : %2\r\n").arg(lines[i]).arg(result);
			out << output;
		}
		else
		{
			isSuccess = false;
			result = "Failed";
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

			result = isSuccess ? "Success" : "Failed";
			output = QString("<%1> : %2\r\n").arg(line).arg(result);
			std::cout << output.toStdString();
		}
	}

	return 0;
}

