#ifndef MMCLASSIFICATIONPLUGIN_H
#define MMCLASSIFICATIONPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QGraphicsSvgItem>
#include "trainingresult.h"
#include "classificationresult.h"
#include "progressableplugin.h"
#include "classificationplugin.h"

class MMClassificationPlugin : public QObject, ClassificationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.Fraunhofer.IOSB.RCAIT.MMClassificationPlugin" FILE "MMClassificationPlugin.json")
    Q_INTERFACES(ClassificationPlugin)

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
    bool getAugmentationPreview(QString modelName, QString inputPath, QString targetPath, int amount) = 0;
    TrainingResult* train(QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin *receiver);
    ClassificationResult* classify(QString inputImageDirPath,QString trainDatasetPath, QString workingDirPath, QString modelName, ProgressablePlugin *receiver);

    QWidget* getDataAugmentationInputWidget();

private slots:
    void slot_readOutPut();
    void slot_pluginFinished();
};
#endif // MMCLASSIFICATIONPLUGIN_H
