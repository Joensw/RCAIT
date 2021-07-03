#include "modelmanager.h"


ModelManager::ModelManager(){
    mCurrentModel = "";
    mCurrentPlugin = "";
    //mClassificationPluginManager = classificationPluginManager;
}

void ModelManager::createNewModel(QString modelName, QString pluginName, QString baseModel){
    //classificationPluginManager->createNewModel(modelName, pluginName, baseModel);
}
void ModelManager::removeModel(QString modelName, QString pluginName){
    //classificationPluginManager->removeModelModel(modelName, pluginName);
}

//es können ja eigentlich nur "legitime" Modelle geladen werden, die aus der GUI stammen.
//eine art "überprüfung" wäre trotzdem nicht schlecht
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
    //return mlassificationPluginManager->getInputWidget(currentModel);
    return nullptr;
}
