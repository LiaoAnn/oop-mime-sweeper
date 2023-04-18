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

bool ExecuteCommand(QString command, QString outputFileName)
{
	// Split command to list
	QStringList list = command.split(" ");
	QString commandName = list[0];
	bool isSuccess = false;

	if (commandName == LOAD_COMMAND)
	{
		if (GameGlobal::gameState == LOADING)
		{
			LoadCommand(list);
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
	else if (commandName == PRINT_COMMAND)
	{
		// Not implement
		PrintMap();
		isSuccess = true;
	}
	else if (commandName == LEFT_CLICK_COMMAND)
	{
		if (GameGlobal::gameState == PLAYING)
		{
			// Not implement
			LeftClick(list[1].toInt(), list[2].toInt());
			isSuccess = true;
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
			RightClick(list[1].toInt(), list[2].toInt());
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
			ResetMap();
		}
		else
		{
			isSuccess = false;
		}
	}
	else if (commandName == QUIT_COMMAND)
	{
		if (GameGlobal::gameState == END)
		{
			exit(1);
		}
		else
		{
			isSuccess = false;
		}
	}
	else
	{
		// Error
	}

	return isSuccess;
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