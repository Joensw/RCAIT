#include "modelmanager.h"

#include <utility>


ModelManager::ModelManager(){
    mCurrentModel = "";
    mCurrentPlugin = "";
    mClassificationPluginManager = &ClassificationPluginManager::getInstance();
}

void ModelManager::createNewModel(QString modelName, QString pluginName, QString baseModel){
    mClassificationPluginManager->createNewModel(std::move(modelName), std::move(pluginName), std::move(baseModel));
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
