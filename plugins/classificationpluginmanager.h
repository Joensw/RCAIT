#ifndef CLASSIFICATIONPLUGINMANAGER_H
#define CLASSIFICATIONPLUGINMANAGER_H

#include <QString>
#include <QWidget>
#include <QMap>
#include <pluginusage/progressableplugin.h>
#include "trainingresult.h"
#include "classificationresult.h"
#include "pluginmanager.h"


class ClassificationPluginManager  : public PluginManager
{
private:
    ClassificationPluginManager();
    static volatile ClassificationPluginManager* instance;

public:
    void loadPlugins(QString pluginDir);
    ClassificationPluginManager* getInstance();
    QWidget* getConfigurationWidget(QString pluginName);
    void saveConfiguration(QString pluginName);
    QWidget* getInputWidget(QString pluginName);
    QMap<QString, QString>  getModelNames(QString projectPath);
    bool createNewModel(QString modelName, QString baseModel);
    bool getAugmentationPreview(QString inputPath);
    bool removeModel(QString modelName);
    TrainingResult* train(QString modelName,QString dataSetPath, ProgressablePlugin* receiver);
    ClassificationResult* classify(QString inputImagePath, QString modelName,ProgressablePlugin* receiver);



};

#endif // CLASSIFICATIONPLUGINMANAGER_H
