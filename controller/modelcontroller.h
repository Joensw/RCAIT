#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QObject>
#include "datamanager.h"
#include "importfileswidget.h"
#include "newmodeldialog.h"
#include "removemodeldialog.h"

/**
 * @brief The ModelController class mediates between the model UI's and the model logic
 */
class ModelController : public QObject
{
    Q_OBJECT
public:
    explicit ModelController(QObject *parent = nullptr, DataManager *dataManager = nullptr, ImportFilesWidget *importFilesWidget = nullptr);
public slots:

    /**
     * @brief slot_newModel open the UI to create a new model
     */
    void slot_newModel();

    /**
     * @brief slot_newModelConfirm creates a new model
     * @param modelName name of the model
     * @param pluginName name of the underlying plugin
     * @param baseModel name of the base model to be used
     */
    void slot_newModelConfirm(const QString &modelName, const QString &pluginName, const QString &baseModel);

    /**
     * @brief slot_removeModel opens the confirmation UI to delete a model
     * @param modelName name of the model
     */
    void slot_removeModel(const QString &modelName);

    /**
     * @brief slot_removeModelConfirm deletes the previously specified model
     */
    void slot_removeModelConfirm();

    /**
     * @brief slot_loadModel loads a model that is to be used for further operations
     * @param modelName name of the model
     */
    void slot_loadModel(const QString &modelName);

    /**
     * @brief slot_pluginSelected updates the new Model UI, when a plugin is selected, to show the bases of this slected plugin accordingly
     * @param pluginName
     */
    void slot_pluginSelected(const QString &pluginName);

    void slot_projectPathUpdated();

signals:

    void sig_modelLoaded();

private:
    DataManager *mDataManager;
    NewModelDialog *mNewModelDialog{};
    RemoveModelDialog *mRemoveModelDialog{};
    ImportFilesWidget *mImportFilesWidget;
};

#endif // MODELCONTROLLER_H
