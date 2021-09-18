#ifndef MMCLASSIFICATIONPLUGIN_H
#define MMCLASSIFICATIONPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QGraphicsSvgItem>

#include <QSettings>
#include <QLineEdit>
#include <QProcess>
#include <QProcessEnvironment>
#include <QFileSystemModel>
#include <QStringBuilder>

#include "trainingresult.h"
#include "classificationresult.h"
#include "progressableplugin.h"
#include "classificationplugin.h"
#include "mmclassificationsettings.h"
#include "mmclassificationdataaugmentationinput.h"
#include "mmclassificationinputoptions.h"
#include "basemodel.h"
#include "model.h"
#include "mmclassificationconfigfilebuilder.h"
#include "mmclassificationjsonresultreader.h"

/**
 * @brief The MMClassificationPlugin class contains the actual ClassificationPlugin functions to use MMClassification and
 *        uses the other MMClassification classes to do this.
 */
class MMClassificationPlugin : public QObject, ClassificationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.Fraunhofer.IOSB.RCAIT.MMClassificationPlugin" FILE "MMClassificationPlugin.json")
    Q_INTERFACES(ClassificationPlugin)
private:

    const QString m_name = "MMClassification";
    const QString m_modelNameKey = "name";
    const QString m_baseModelNameKey = "baseModel";
    const QString m_mainConfigPathKey = "configPath";
    const QString m_modelConfigPathKey = "modelConfig";
    const QString m_datasetConfigPathKey = "datasetPath";
    const QString m_scheduleConfigPathKey = "schedulePath";
    const QString m_runtimeConfigPathKey = "runtimePath";

    const QString m_subfolder_checkpoints = "checkpoints";
    const int m_numberOfMissClassifiedImages = 9;
    const QString m_annotationFileName = "val.txt";

    QList<BaseModel>* m_baseModels;
    QSettings m_models = {"MMClassificationModels", QSettings::IniFormat};

    MMClassificationSettings m_mmClassificationSettings;
    MMClassificationConfigFileBuilder m_mmClassificationConfigFileBuilder;
    MMClassificationDataAugmentationInput *m_mmclassificationdataaugmentationinput;
    MMClassificationInputOptions *m_mmClassificationInput;
    MMClassificationJsonResultReader m_jsonReader;

    QWidget *pluginSettings;
    QWidget *dataAugmentationInput;
    QWidget *inputOptions;

    QScopedPointer<QProcess> m_process;
    ProgressablePlugin* m_receiver;

    QFileSystemWatcher *m_watcher;
    QString m_workDir;
    int m_maxIters;

    void initBaseModels();
    void deleteBaseModels();
    void saveModel(Model model);
    Model loadModel(const QString& name);

    static QStringList getLabels(const QString& datasetPath);

    bool checkDataAugmentationPreviewInput(const QString& modelName, const QString& inputPath, const QString& targetPath, int amount);
    static bool checkTrainMethodInput(const QStringList& labels, const QString& mainConfigPath, const QString& trainDatasetPath, const QString& validationDatasetPath, const QString& workingDirectoryPath);

    void adjustCheckpointCreation(const QString& runtimeConfigPath, int max_iters);

    void connectIt();
    void connectFileWatcher(QString path);

public:

    /**
     * @brief destructor
     */

    ~MMClassificationPlugin();

    /**
     * @brief getName returns the name of this plugin
     * @return the name of this Classification Plugin
     */
    QString getName() override;

    /**
     * @brief getConfigurationWidget returns a widget to make configurations of this plugin accessible
     * @return a widget to make plugin specfific configurations
     */
    QWidget* getConfigurationWidget() override;

    /**
     * @brief saveConfiguration saves the changes made in the configuration widget
     */
    void saveConfiguration() override;

    /**
     * @brief getInputWidget returns a widget to specify additional, plugin specific input for the train method
     * @return a widget to specify plugin specific input, which is not data augmentation input
     */
    QWidget* getInputWidget() override;

    /**
     * @brief init initialize the needed classes and settings of this plugin, must be called once before using this plugin
     */
    void init() override;

    /**
     * @brief getAssociatedModels returns the names of the models associated with this plugin (base models)
     * @return the base model names
     */
    QStringList getAssociatedModels() override;

    /**
     * @brief createNewModel creates a new model with the given specification
     * @param modelName the name of the model to be created
     * @param baseModel the name of a base model of this plugin
     * @return false on error, true otherwise
     */
    bool createNewModel(QString modelName, QString baseModel) override;

    /**
     * @brief removeModel removes the given model with all its files
     * @param modelName the name of a model created with this plugin
     * @return false on error, true otherwise
     */
    bool removeModel(QString modelName) override;

    /**
     * @brief getAugmentationPreview carries out data augmentation with the parameters specified in the data augmentation input widget
     *        and given parameters
     * @param modelName the name of the model, which data augmentation options should be changed
     * @param inputPath a path with input pictures for the data augmentation, should have amount many pictures in it,
     *        otherwise less pictures as specified will be generated
     * @param targetPath a path to save the newly created pictures
     * @param amount the number of pictures to generate
     * @return false on error, true otherwise
     */
    bool getAugmentationPreview(QString modelName, QString inputPath, QString targetPath, int amount) override;

    /**
     * @brief train trains a model, reports the process while doing so and extracts the relevant results in a TrainingResult object
     * @param modelName the name of a model created with this plugin
     * @param trainDatasetPath a path to the dataset to use for this training
     * @param validationDatasetPath a path to the dataset to use for validation
     * @param workingDirectory a path the working directory to save the logs, checkpoints and result files
     * @param receiver a Progressable plugin to report the progress to the main application
     * @return a pointer to a TrainingResult object with the relevant data
     */
    TrainingResult* train(QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin *receiver) override;

    /**
     * @brief classify classifies the given images with the given model and extracts the relevant results in a ClassificationResult object
     * @param inputImageDirPath the input path with the images to classify
     * @param trainDatasetPath the path to the dataset used by train with the given model to get the labels
     * @param workingDirPath the path to the working directory, where the checkpoint file for the given model is located
     * @param modelName the name of the model, which should be used for this classification
     * @param receiver a Progressable plugin to report the progress to the main application
     * @return a pointer to a ClassificationResult object with the relevant data
     */
    ClassificationResult* classify(QString inputImageDirPath,QString trainDatasetPath, QString workingDirPath, QString modelName, ProgressablePlugin *receiver) override;

    /**
     * @brief getDataAugmentationInputWidget returns a widget to specify additional, plugin specific data augmentation input for the getAugmentationPreview and the train method
     * @return a widget to specify plugin specific data augmentation input
     */
    QWidget* getDataAugmentationInputWidget() override;

private slots:
    void slot_readClassifyOutput();

    void slot_checkForLogFile(QString path);
    void slot_readChangeInLogFile(QString path);
};
#endif // MMCLASSIFICATIONPLUGIN_H
