#ifndef CLASSIFICATIONPLUGIN_H
#define CLASSIFICATIONPLUGIN_H

#include <QTextStream>
#include "trainingresult.h"
#include "classificationresult.h"
#include "progressableplugin.h"
#include "plugin.h"

class ClassificationPlugin : public Plugin
{
public:
    virtual QStringList getAssociatedModels(QString dataSet);
    virtual bool createNewModel(QString modelName, QString baseModel);
    virtual bool getAugmentationPreview(QString inputPath);
    virtual bool removeModel(QString modelName);
    virtual TrainingResult* train(QString modelName,QString dataSetPath, ProgressablePlugin* receiver);
    virtual ClassificationResult* classify(QString inputImagePath, QString modelName,ProgressablePlugin* receiver);

};

#endif // CLASSIFICATIONPLUGIN_H
