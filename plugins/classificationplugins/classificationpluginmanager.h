#ifndef CLASSIFICATIONPLUGINMANAGER_H
#define CLASSIFICATIONPLUGINMANAGER_H

#include <QString>
#include <QWidget>
#include <QMap>
#include "trainingresult.h"
#include "progressableplugin.h"
#include "classificationresult.h"
#include "classificationplugin.h"
#include "pluginmanager.h"
class ClassificationPluginManager : public PluginManager{
private: ClassificationPluginManager();
QMap<QString, ClassificationPlugin*> m_plugins;



public:
    ClassificationPluginManager(ClassificationPluginManager const &) = delete;
    void operator=(ClassificationPluginManager const &) = delete;

    static ClassificationPluginManager &getInstance() {
        static ClassificationPluginManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    void loadPlugins(QString pluginDir) override;

    QWidget * getConfigurationWidget(QString pluginName) override;
    void saveConfiguration(QString pluginName) override;
    QWidget * getInputWidget(QString pluginName) override;
    QStringList getNamesOfPlugins() override;
    QMap<QString, QString> getModelNames(QString projectPath);
    bool createNewModel(QString modelName, QString pluginName, QString baseModel);
    bool getAugmentationPreview(QString pluginName, QString inputPath);
    bool removeModel(QString modelName, QString pluginName);
    TrainingResult * train (QString pluginName, QString modelName, QString dataSetPath, ProgressablePlugin * receiver);
    ClassificationResult * classify(QString pluginName, QString inputImagePath, QString modelName, ProgressablePlugin * receiver);

    QStringList getClassificationPluginBases(QString plugin);
private:
    ClassificationPluginManager * instance;
};

#endif // CLASSIFICATIONPLUGINMANAGER_H
