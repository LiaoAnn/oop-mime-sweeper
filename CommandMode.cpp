#include "CommandMode.h"
#include "CommandMap.h"
#include "RunMode.h"


QStringList LoadFile(QString fileName)
{
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	QTextStream in(&file);
	QStringList lines;
	while (!in.atEnd())
	{
		QString line = in.readLine();
		lines.append(line);
	}
	file.close();
	return lines;
}

bool ExecuteCommand(QStringList commandList)
{
	// Split command to list
	QString commandName = commandList[0];
	bool isSuccess = false;

	if (commandName == LOAD_COMMAND)
	{
		if (GameGlobal::gameState == LOADING)
		{
			LoadCommand(commandList);
			isSuccess = true;
		}
		else
		{
			isSuccess = false;
		}
	}
	else if (commandName == START_GAME_COMMAND)
	{
		if (GameGlobal::gameState == LOADING)
		{
			GameGlobal::gameState = PLAYING;
			isSuccess = true;
		}
		else
		{
			isSuccess = false;
		}

	}
	else if (commandName == LEFT_CLICK_COMMAND)
	{
		if (GameGlobal::gameState == PLAYING)
		{
			// Not implement
			isSuccess = LeftClick(commandList[1].toInt(), commandList[2].toInt());
		}
		else
		{
			isSuccess = false;
		}
	}
	else if (commandName == RIGHT_CLICK_COMMAND)
	{
		if (GameGlobal::gameState == PLAYING)
		{
			// Not implement
			RightClick(commandList[1].toInt(), commandList[2].toInt());
			isSuccess = true;
		}
		else
		{
			isSuccess = false;
		}
	}
	else if (commandName == REPLAY_COMMAND)
	{
		if (GameGlobal::gameState == END)
		{
			GameGlobal::gameState = LOADING;
			// Not implement
			isSuccess = ResetMap();
		}
		else
		{
			isSuccess = false;
		}
	}

	return isSuccess;
}

QString ExecutePrintCommand(QStringList commandList)
{
	// Split command to list	
	QString commandName = commandList[0];
	QString printResult = "";

	// Not implement
	if (commandList[1] == "GameBoard")
		printResult = PrintMap();
	else if (commandList[1] == "GameAnswer")
		printResult = PrintAnswer();
	else if (commandList[1] == "GameState")
		printResult = PrintGameState();
	else if (commandList[1] == "BombCount")
		printResult = PrintBombCount();
	else if (commandList[1] == "FlagCount")
		printResult = PrintFlagCount();
	else if (commandList[1] == "OpenBlankCount")
		printResult = PrintOpenBlankCount();
	else if (commandList[1] == "RemainBlankCount")
		printResult = PrintRemainBlankCount();

	return printResult;
}

void LoadCommand(QStringList originCommand)
{
	QString loadType = originCommand[1];

	if (loadType == "BoardFile")
	{
		QString boardFile = originCommand[2];

		// Not implement
		LoadBoardFile(boardFile);
	}
	else if (loadType == "RandomCount")
	{
		int row = originCommand[2].toInt();
		int col = originCommand[3].toInt();
		int mineCount = originCommand[4].toInt();

		// Not implement
		GenerateMapCountMine(row, col, mineCount);
	}
	else if (loadType == "RandomRate")
	{
		int row = originCommand[2].toInt();
		int col = originCommand[3].toInt();
		double mineRate = originCommand[4].toDouble();

		// Not implement
		GenerateMapRateMine(row, col, mineRate);
	}
}