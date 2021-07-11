#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QObject>
#include "datamanager.h"
#include "importfileswidget.h"
#include "newmodeldialog.h"
#include "removemodeldialog.h"

class ModelController : public QObject
{
public:
    explicit ModelController(QObject *parent = nullptr, DataManager *dataManager = nullptr, ImportFilesWidget *importFilesWidget = nullptr);
public slots:
    void slot_newModel();
    void slot_newModelConfirm(QString modelName, QString pluginName, QString baseModel);

    void slot_removeModel(QString modelName);
    void slot_removeModelConfirm();

    void slot_loadModel(QString modelName);

    void slot_pluginSelected(QString pluginName);
private:
    DataManager *mDataManager;
    NewModelDialog *mNewModelDialog;
    RemoveModelDialog *mRemoveModelDialog;
    ImportFilesWidget * mImportFilesWidget;
};

#endif // MODELCONTROLLER_H
