#include "modelmanager.h"

#include <utility>


ModelManager::ModelManager(){
    mClassificationPluginManager = &ClassificationPluginManager::getInstance();
}

void ModelManager::createNewModel(QString projectName, QString modelName, QString pluginName, QString baseModel){
    if(mClassificationPluginManager->createNewModel(modelName, pluginName, baseModel)) {
        // add the new model to the saved user models
        m_userModelNamesPerProject.beginGroup(projectName);
        m_userModelNamesPerProject.setValue(modelName, pluginName);
        m_userModelNamesPerProject.endGroup();
    } else {
        qWarning() << "The new model could not be created";
    }
}

void ModelManager::removeModel(QString projectName, QString modelName){
    m_userModelNamesPerProject.beginGroup(projectName);
    QString pluginName = m_userModelNamesPerProject.value(modelName).toString();
    m_userModelNamesPerProject.endGroup();
    if (!pluginName.isEmpty()) {
        if (mClassificationPluginManager->removeModel(modelName, pluginName)) {
            m_userModelNamesPerProject.beginGroup(projectName);
            m_userModelNamesPerProject.remove(modelName);
            m_userModelNamesPerProject.endGroup();
        }
    } else {
        qWarning() << "The model " + modelName + " could not be deleted";
    }
}

void ModelManager::loadModel(QString modelName, QString pluginName){
    mCurrentModel = std::move(modelName);
    mCurrentPlugin = std::move(pluginName);
}

QString ModelManager::getCurrentPlugin(){
    return mCurrentPlugin;
}
QString ModelManager::getCurrentModel(){
    return mCurrentModel;
}

QStringList ModelManager::getModelNamesOfProject(QString projectName)
{
    m_userModelNamesPerProject.beginGroup(projectName);
    QStringList modelNames = m_userModelNamesPerProject.childKeys();
    m_userModelNamesPerProject.endGroup();
    return modelNames;
}

void ModelManager::removeAllModelsOfProject(QString projectName)
{
    QStringList modelsToRemove = getModelNamesOfProject(projectName);
    foreach (QString modelName, modelsToRemove) {
        removeModel(projectName, modelName);
    }
}
QWidget * ModelManager::getInputWidget(){
    return mClassificationPluginManager->getInputWidget(mCurrentModel);
}
