#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include <QString>
#include <newprojectdialog.h>
#include <startwidget.h>
#include <datamanager.h>


class ProjectController : public QObject
{
    Q_OBJECT
public:
    explicit ProjectController(QObject *parent = nullptr, DataManager *dataManager = nullptr);


public slots:
    void slot_newProject();
    void slot_newProjectConfirm(QString projectName);

private:
    DataManager *mDataManager;
    NewProjectDialog *mNewProjectDialog;
    StartWidget * mStartWidget;

    QString verifyName(QString input);

};

#endif // PROJECTCONTROLLER_H
