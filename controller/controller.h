#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "settingscontroller.h"
#include "projectcontroller.h"
#include "datamanager.h"
#include "aicontroller.h"
#include "modelcontroller.h"
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

    SettingsController * mSettingsController;

    ProjectController * mProjectController;

    AIController * mAiController;

    ModelController * mModelController;

    DataManager * mDataManger;

};

#endif // CONTROLLER_H
