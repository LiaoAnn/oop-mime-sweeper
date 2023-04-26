/***********************************************************************
 * File: CommandLine.h
 * Author: ÃÓªÃ®a
 * Create Date: 2023/04/16
 * Editor: ÃÓªÃ®a¡B¹ù§Ê¦w
 * Update Date: 2023/04/26
 * Description: Command Line reader header
***********************************************************************/
#pragma once
#ifndef CommandLine_H
#define CommandLine_H

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
#endif 
