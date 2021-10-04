/**
 * @file modelmanager.h
 *
 * @brief functions for managing models of image classification plugins
 *
 * @author Andreas Ott
 */
#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QString>
#include <QWidget>
#include <QSettings>
#include <utility>
#include <classificationpluginmanager.h>

/**
 * @brief The ModelManager class contains logic for manipulating models of external classification plugins
 */
class ModelManager final
{
public:

    /**
     * @brief ModelManager deleted copy constructor
     */

    ModelManager(const ModelManager &) = delete;

    /**
     * @brief operator = deleted assignment operator
     */

    ModelManager &operator=(const ModelManager &) = delete;

    /**
     * @brief getInstance returns the only instance of the ModelManager class
     * @return instance
     */
    static ModelManager &getInstance() {
        static ModelManager INSTANCE; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return INSTANCE;
    }

    /**
     * @brief createNewModel created a new model with the specified parameters
     * @param projectName the name of the project to which the model belongs
     * @param modelName name of the model
     * @param pluginName name of the plugin the model is from
     * @param baseModel name of the base model to be used
     */
    bool createNewModel(const QString &projectName, const QString &modelName, const QString &pluginName, const QString &baseModel);

    /**
     * @brief removeModel removes a model according to the specified parameters
     * @param projectName the name of the project to which the model belongs
     * @param modelName name the model
     */
    bool removeModel(const QString &projectName, const  QString &modelName);

    /**
     * @brief loadModel loads a model into the application for further use
     * @param modelName name of the model
     * @param pluginName name of the plugin the model is from
     */
    void loadModel(const QString &modelName, const QString &pluginName);

    /**
     * @return the classification plugin the current model is from
     */
    [[nodiscard]] QString getCurrentPlugin() const;

    /**
     * @return the input UI of the current classification plugin that is to be shown
     */
    QSharedPointer<QWidget> getInputWidget();

    /**
     * @return the input UI of the current classification plugins data augmentation settings that are to be shown
     */
    QSharedPointer<QWidget> getDataAugmentationInputWidget();

    /**
     * @return the currently loaded model
     */
    [[nodiscard]] QString getCurrentModel() const;

    /**
     * @brief getModelNamesOfProject returns all modelNames of the given project
     * @param projectName the name of the project with the required models
     * @return the names of the models from the given project, if the projects exists,
     *         otherwise an empty list will be returned
     */
    QStringList getModelNamesOfProject(const QString &projectName);

    /**
     * @brief removeAllModelsOfProject deletes every user created model from the given project
     * @param projectName the name of the project whose models are to be removed
     */
    void removeAllModelsOfProject(const QString &projectName);

    /**
     * @brief setLastWorkingDirectoryOfModel saves the given working directory to the model data
     * @param projectName the project name of the given model
     * @param modelName the name of the model to which the working directory belongs
     * @param workingDirectory the working directory to save
     */
    void saveLastWorkingDirectoryOfModel(const QString &projectName, const QString &modelName, const QString &workingDirectory);

    /**
     * @brief recallLastWorkingDirectoryOfModel returns the saved working directory of the given model
     * @param projectName the project name of the given model
     * @param modelName the name of model to which the working directory belongs
     * @return the saved working directory of the given model, if it exists, an empty QString otherwise
     */
    QString recallLastWorkingDirectoryOfModel(const QString &projectName, const QString &modelName);

    /**
     * @brief recallPluginNameOfModel find the plugin a certain model was derived from
     * @param projectName name of the project to search in
     * @param modelName name of the model to search by
     * @return name of the originating plugin
     */

    QString recallPluginNameOfModel(const QString &projectName, const QString &modelName);

private:
    const int pluginNamePosition = 0;
    const int lastWorkingDirectoryPosition = 1;
    const int numberOfEntries = 2;

    ClassificationPluginManager * mClassificationPluginManager;

    QString mCurrentModel;
    QString mCurrentPlugin;

    QSettings m_userModelNamesPerProject = {"UserModelNamesPerProject", QSettings::IniFormat};

    ModelManager();
};

#endif // MODELMANAGER_H
