#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include <QString>
#include <newprojectdialog.h>
#include <removeprojectdialog.h>
#include <startwidget.h>
#include <datamanager.h>


class ProjectController : public QObject
{
    Q_OBJECT
public:
    explicit ProjectController(QObject *parent = nullptr, DataManager *dataManager = nullptr, StartWidget *startWidget = nullptr);

public slots:
    void slot_newProject();
    void slot_newProjectConfirm(QString projectName);

    void slot_removeProject(QString projectName);
    void slot_removeProjectConfirm();

    void slot_openProject(QString projectName);

private:
    DataManager *mDataManager;
    NewProjectDialog *mNewProjectDialog;
    RemoveProjectDialog *mRemoveProjectDialog;
    StartWidget * mStartWidget;

    QString verifyName(QString input);

};

#endif // PROJECTCONTROLLER_H
