#ifndef CLASSIFICATIONPLUGINMANAGER_H
#define CLASSIFICATIONPLUGINMANAGER_H

#include <QString>
#include <QWidget>

#include "trainingresult.h"
#include "progressableplugin.h"
#include "classificationresult.h"
class ClassificationPluginManager
{
public:
    ClassificationPluginManager();

    void loadPlugins(QString pluginDir);
    static ClassificationPluginManager * getInstance();
    QWidget * getConfigurationWidget(QString pluginName);
    void saveConfiguration(QString pluginName);
    QWidget * getInputWidget(QString pluginName);
    QMap<QString, QString> getModelNames(QString projectPath);
    bool createNewModel(QString ModelName, QString pluingName, QString baseModel);
    bool getAugmentationPreview(QString pluginName, QString inputPath);
    bool removeModel(QString modelName, QString pluginName);
    TrainingResult * train (QString pluginName, QString modelName, QString dataSetPath, ProgressablePlugin * receiver);
    ClassificationResult * classify(QString pluginName, QString inputImagePath, QString modelName, ProgressablePlugin * receiver);

    QStringList getClassificationPluginBases(QString plugin);
private:
    ClassificationPluginManager * instance;
};

#endif // CLASSIFICATIONPLUGINMANAGER_H
