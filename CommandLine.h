#pragma once

#include <qobject.h>
#include <qthread.h>
#include <qdebug.h>
#include <qtextstream.h>
#include "qiodevice.h"



class CommandLine : public QObject
{
	Q_OBJECT
public:
	explicit CommandLine(QObject* parent = nullptr);

signals:
	void OnReadLine(QString line);

public slots:
	void ReadStdin();
	void HandleStdin(QString line);

private:
	QThread mThread;
};
