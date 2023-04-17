#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication.h"

class QtWidgetsApplication : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication(QWidget *parent = nullptr);
    ~QtWidgetsApplication();

    void buttonClicked();

private:
    Ui::QtWidgetsApplicationClass ui;
};