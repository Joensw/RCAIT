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
    QWidget * getDataAugmentationInputWidget(const QString& pluginName);
    QStringList getNamesOfPlugins() override;
    QStringList getModelNames(const QString& pluginName);
    bool createNewModel(QString modelName, const QString& pluginName, QString baseModel);
    bool getAugmentationPreview(const QString& pluginName, QString modelName, QString inputPath, QString targetPath, int amount);
    bool removeModel(QString modelName, const QString& pluginName);
    TrainingResult * train (const QString& pluginName, QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin * receiver);
    ClassificationResult * classify(const QString& pluginName, QString inputImageDirPath, QString trainDatasetPath, QString workingDirectory, QString modelName, ProgressablePlugin * receiver);
    QList<QWidget*> getConfigurationWidgets();

    QStringList getClassificationPluginBases(const QString& pluginName);
private:
    ClassificationPluginManager * instance;
    QList<QWidget*> m_pluginConfigurationWidgets;

};

#endif // CLASSIFICATIONPLUGINMANAGER_H
