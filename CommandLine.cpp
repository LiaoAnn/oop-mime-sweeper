#include "CommandLine.h"

CommandLine::CommandLine(QObject* parent)
	: QObject(parent)
{
	this->moveToThread(&mThread);

	connect(&mThread, SIGNAL(started()), this, SLOT(ReadStdin()));
	connect(this, SIGNAL(OnReadLine(QString)), this, SLOT(HandleStdin()));

	mThread.start();
}

void CommandLine::ReadStdin()
{
	QTextStream stream(stdin);
	QString line = stream.readLine();
	emit OnReadLine(line);
	ReadStdin();
}

void CommandLine::HandleStdin(QString line)
{
	qDebug() << "HandleStdin";
}
