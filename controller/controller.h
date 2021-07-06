#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "settingscontroller.h"
#include "datamanager.h"
#include <mainwindow.h>

#include <QObject>


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

signals:

private:
    MainWindow *mMainWindow;

    SettingsController *mSettingsController;

    DataManager* mDataManger;

};

#endif // CONTROLLER_H
