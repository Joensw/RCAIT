#include "modelmanager.h"


ModelManager::ModelManager(){
    mClassificationPluginManager = ClassificationPluginManager::getInstance();
}

void ModelManager::createNewModel(QString modelName, QString pluginName, QString baseModel){
    mClassificationPluginManager->createNewModel(modelName, pluginName, baseModel);
}
void ModelManager::removeModel(QString modelName, QString pluginName){
    mClassificationPluginManager->removeModel(modelName, pluginName);
}

void ModelManager::loadModel(QString modelName, QString pluginName){
    mCurrentModel = modelName;
    mCurrentPlugin = pluginName;
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
