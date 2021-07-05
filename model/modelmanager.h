#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QString>
#include <QWidget>


class ModelManager
{
public:
    //ModelManager::ModelManager(ClassificationPluginManager * classificationPluginManager)
    ModelManager();

    //TODO update this when it exists
    //ModelManager(ClassificationPluginManager* classificationPluginManager);

    void createNewModel(QString modelName, QString pluginName, QString baseModel);
    void removeModel(QString modelName, QString pluginName);
    void loadModel(QString modelName, QString pluginName);

    QString getCurrentPlugin();
    QWidget * getInputWidget();
    QString getCurrentModel();






private:
    //ClassificationPluginManager * mClassificationPluginManager;

    QString mCurrentModel;
    QString mCurrentPlugin;


};

#endif // MODELMANAGER_H
