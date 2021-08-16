#ifndef CLASSIFICATIONPLUGIN_H
#define CLASSIFICATIONPLUGIN_H

#include <QObject>
#include <QTextStream>
#include <results/trainingresult.h>
#include <results/classificationresult.h>
#include <pluginusage/progressableplugin.h>
#include "plugin.h"


class ClassificationPlugin : public Plugin
{
public:
    virtual ~ClassificationPlugin() = default;
    virtual QStringList getAssociatedModels() = 0;
    virtual bool createNewModel(QString modelName, QString baseModel) = 0;
    virtual bool getAugmentationPreview(QString modelName, QString inputPath, QString targetPath, int amount) = 0;
    virtual QWidget* getDataAugmentationInputWidget() = 0;
    virtual bool removeModel(QString modelName)= 0;
    virtual TrainingResult* train(QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin *receiver)= 0;
    virtual ClassificationResult* classify(QString inputImageDirPath, QString trainDatasetPath, QString workingDirPath, QString modelName, ProgressablePlugin *receiver)= 0;
    virtual void init() = 0;
};

QT_BEGIN_NAMESPACE

#define ClassificationPlugin_iid "de.Fraunhofer.IOSB.RCAIT.ClassificationPlugin"

Q_DECLARE_INTERFACE(ClassificationPlugin, ClassificationPlugin_iid)
QT_END_NAMESPACE

#endif
