#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QString>
#include <QWidget>
#include <QSettings>

#include "classificationpluginmanager.h"



/**
 * @brief The ModelManager class contains logic for manipulating models of external classification plugins
 */
class ModelManager
{
public:
    ModelManager(); // might become a singleton TODO?

    /**
     * @brief createNewModel created a new model with the specified parameters
     * @param modelName name of the model
     * @param pluginName name of the plugin the model is from
     * @param baseModel name of the base model to be used
     */
    void createNewModel(QString projectName, QString modelName, QString pluginName, QString baseModel);

    /**
     * @brief removeModel removes a model according to the specified parameters
     * @param modelName name the model
     * @param pluginName name of the plugin the model is from
     */
    void removeModel(QString modelName, QString pluginName);

    /**
     * @brief loadModel loads a model into the application for further use
     * @param modelName name of the model
     * @param pluginName name of the plugin the model is from
     */
    void loadModel(QString modelName, QString pluginName);

    /**
     * @return the classification plugin the current model is from
     */
    QString getCurrentPlugin();

    /**
     * @return the input UI of the current classification plugin that is to be shown
     */
    QWidget * getInputWidget();

    /**
     * @return the currently loaded model
     */
    QString getCurrentModel();



private:
    ClassificationPluginManager * mClassificationPluginManager;

    QString mCurrentModel;
    QString mCurrentPlugin;

    QSettings m_userModelNamesPerProject = {"UserModelNamesPerProject", QSettings::IniFormat};

};

#endif // MODELMANAGER_H
