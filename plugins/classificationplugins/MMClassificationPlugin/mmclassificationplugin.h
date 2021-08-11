#ifndef MMCLASSIFICATIONPLUGIN_H
#define MMCLASSIFICATIONPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QGraphicsSvgItem>
#include "trainingresult.h"
#include "classificationresult.h"
#include "progressableplugin.h"
#include "classificationplugin.h"
#include "mmclassificationsettings.h"
#include "mmclassificiationdataaugmentationinput.h"
#include "mmclassificationinputoptions.h"
#include "basemodel.h"
#include "model.h"
#include "mmclassificationconfigfilebuilder.h"

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

    QList<BaseModel>* m_baseModels;
    QSettings m_models = {"MMClassificationModels", QSettings::IniFormat};


    MMClassificationSettings m_mmClassificationSettings;
    MMClassificationConfigFileBuilder m_mmClassificationConfigFileBuilder;
    MMClassificiationDataAugmentationInput *m_mmclassificiationdataaugmentationinput;
    MMClassificationInputOptions *m_mmClassificationInput;

    QWidget *pluginSettings;
    QWidget *dataAugmentationInput;
    QWidget *inputOptions;

    void initBaseModels();
    void deleteBaseModels();
    void saveModel(Model model);
    Model loadModel(QString name);
public:
    MMClassificationPlugin();
    ~MMClassificationPlugin();

    QString getName();
    QWidget* getConfigurationWidget();
    void saveConfiguration();
    QWidget* getInputWidget();

    QStringList getAssociatedModels();
    bool createNewModel(QString modelName, QString baseModel);
    bool removeModel(QString modelName);
    bool getAugmentationPreview(QString modelName, QString inputPath, QString targetPath, int amount);
    TrainingResult* train(QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin *receiver);
    ClassificationResult* classify(QString inputImageDirPath,QString trainDatasetPath, QString workingDirPath, QString modelName, ProgressablePlugin *receiver);

    QWidget* getDataAugmentationInputWidget();

private slots:
    void slot_readOutPut();
    void slot_pluginFinished();
};
#endif // MMCLASSIFICATIONPLUGIN_H
