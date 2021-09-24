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


/**
 * @brief The ClassificationPluginManager class is responsible for loading and managing classification plugins.
 */
class ClassificationPluginManager : public PluginManager {
private:
    ClassificationPluginManager();

    QMap<QString, QSharedPointer<ClassificationPlugin>> m_plugins;


public:

    /**
     * @brief ImageLoaderPluginManager singleton constructor
     */
    ClassificationPluginManager(ClassificationPluginManager const &) = delete;

    /**
     * @brief operator = delete
     */
    void operator=(ClassificationPluginManager const &) = delete;

    /**
     * @brief getInstance gets singleton instance of ClassificationPluginManager.
     *
     * @return ClassificationPluginManager instance
     */
    static ClassificationPluginManager &getInstance() {
        static ClassificationPluginManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    /**
     * @brief loadPlugins loads classification plugins from a directory.
     *
     * @param pluginDir dir to load
     */
    void loadPlugins(QString pluginDir) override;

    /**
     * @brief getConfigurationWidget gets config widget of spcified plugin.
     *
     * @param pluginName name of plugin
     * @return config widget
     */
    QSharedPointer<QWidget> getConfigurationWidget(QString pluginName) override;

    /**
     * @brief saveConfiguration saves changes in config widget of specified plugin.
     *
     * @param pluginName name of plugin
     */
    void saveConfiguration(QString pluginName) override;

    /**
     * @brief getInputWidget gets widget with inputoptions of a specified plugin.
     *
     * @param pluginName name of plugin
     * @return input widget of plugin
     */
    QSharedPointer<QWidget> getInputWidget(QString pluginName) override;

    /**
     * @brief getDataAugmentationInputWidget gets widget for augmentation config of a specified plugin.
     *
     * @param pluginName name of plugin
     * @return data augmentation input widget
     */
    QSharedPointer<QWidget> getDataAugmentationInputWidget(const QString &pluginName);

    /**
     * @brief getNamesOfPlugins gets names of all loaded plugins.
     *
     * @return list of plugin names
     */
    QStringList getNamesOfPlugins() override;

    /**
     * @brief getModelNames gets all model names of specified plugin.
     *
     * @param pluginName name of plugin
     * @return list of model names
     */
    QStringList getModelNames(const QString &pluginName);

    /**
     * @brief createNewModel creates a new model with a name from a base model and plugin.
     *
     * @param modelName name of new model
     * @param pluginName name of plugin
     * @param baseModel base model of new model
     * @return true if creation was successful
     */
    bool createNewModel(QString modelName, const QString &pluginName, QString baseModel);

    /**
     * @brief getAugmentationPreview loads a preview of augmented images into a folder.
     *
     * @param pluginName name of plugin
     * @param modelName name of model
     * @param inputPath location of original images
     * @param targetPath location for new images
     * @param amount number of augmented images
     * @return true if successful
     */
    bool getAugmentationPreview(const QString &pluginName, const QString &modelName, const QString &inputPath,
                                const QString &targetPath,
                                int amount);

    /**
     * @brief removeModel removes model with specified name and plugin.
     *
     * @param modelName name of model
     * @param pluginName name of plugin
     * @return true if removal was successful
     */
    bool removeModel(QString modelName, const QString &pluginName);

    /**
     * @brief train starts a training with a selected plugin.
     *
     * @param pluginName name of plugin
     * @param modelName name of model
     * @param trainDatasetPath location of training images
     * @param validationDatasetPath location of validation images
     * @param workingDirectory working directory
     * @param receiver receives progress of training
     * @return result data of training
     */
    TrainingResult *
    train(const QString &pluginName, const QString &modelName, QString trainDatasetPath, QString validationDatasetPath,
          QString workingDirectory, ProgressablePlugin *receiver);

    /**
     * @brief classify starts a classification with a selected plugin.
     *
     * @param pluginName name of plugin
     * @param inputImageDirPath location of input images
     * @param trainDatasetPath location of training images
     * @param workingDirectory working directory
     * @param modelName name of model
     * @param receiver receives classification progress
     * @return result data of classification
     */
    ClassificationResult *
    classify(const QString &pluginName, const QString &inputImageDirPath, const QString &trainDatasetPath,
             const QString &workingDirectory,
             const QString &modelName, ProgressablePlugin *receiver);

    /**
     * @brief getConfigurationWidgets gets config widgets of all classification plugins.
     *
     * @return list of config widgets
     */
    QList<QSharedPointer<QWidget>> getConfigurationWidgets();

    /**
     * @brief getClassificationPluginBases gets base models of plugin.
     *
     * @param pluginName name of plugin
     * @return list of plugin bases
     */
    QStringList getClassificationPluginBases(const QString &pluginName);

private:
    QList<QSharedPointer<QWidget>> m_pluginConfigurationWidgets;

};

#endif // CLASSIFICATIONPLUGINMANAGER_H
