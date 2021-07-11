#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QString>
#include <QWidget>

#include "classificationpluginmanager.h"




class ModelManager
{
public:
    ModelManager();


    void createNewModel(QString modelName, QString pluginName, QString baseModel);
    void removeModel(QString modelName, QString pluginName);
    void loadModel(QString modelName, QString pluginName);

    QString getCurrentPlugin();
    QWidget * getInputWidget();
    QString getCurrentModel();



private:
    ClassificationPluginManager * mClassificationPluginManager;

    QString mCurrentModel;
    QString mCurrentPlugin;


};

#endif // MODELMANAGER_H
