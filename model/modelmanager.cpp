#include "modelmanager.h"

#include <utility>


ModelManager::ModelManager(){
    mClassificationPluginManager = &ClassificationPluginManager::getInstance();
}

void ModelManager::createNewModel(QString projectName, QString modelName, QString pluginName, QString baseModel){
    if(mClassificationPluginManager->createNewModel(modelName, pluginName, baseModel)) {
        // add the new model to the saved user models
        m_userModelNamesPerProject.beginGroup(projectName);
        m_userModelNamesPerProject.setValue(modelName, modelName);
        m_userModelNamesPerProject.endGroup();
    } else {
        qWarning() << "The new model could not be created";
    }
}
void ModelManager::removeModel(QString modelName, QString pluginName){
    mClassificationPluginManager->removeModel(std::move(modelName), std::move(pluginName));
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
QWidget * ModelManager::getInputWidget(){
    return mClassificationPluginManager->getInputWidget(mCurrentModel);
}
