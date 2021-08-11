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
    QWidget *getConfigurationWidget();
    void saveConfiguration();
    QWidget *getInputWidget();
    QStringList getAssociatedModels(QString dataSet);
    bool createNewModel(QString modelName, QString baseModel);
    bool getAugmentationPreview(QString inputPath);
    bool removeModel(QString modelName);
    TrainingResult *train(QString modelName,QString dataSetPath, ProgressablePlugin* receiver);
    ClassificationResult *classify(QString inputImagePath, QString modelName,ProgressablePlugin* receiver);

private slots:
    void slot_readOutPut();
    void slot_pluginFinished();

};
#endif // MMCLASSIFICATIONPLUGIN_H
