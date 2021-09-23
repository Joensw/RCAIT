#include "classificationpluginmock.h"





QWidget *ClassificationPluginMock::getConfigurationWidget()
{
    return new QWidget;
}

void ClassificationPluginMock::saveConfiguration()
{

}

void ClassificationPluginMock::init()
{

}

QString ClassificationPluginMock::getName()
{
    return PLUGIN_NAME;
}

QWidget *ClassificationPluginMock::getInputWidget()
{
    return new QWidget;
}

QStringList ClassificationPluginMock::getAssociatedModels()
{
    return QStringList();
}

bool ClassificationPluginMock::createNewModel(QString modelName, QString baseModel)
{
    return true;
}

bool ClassificationPluginMock::getAugmentationPreview(const QString &modelName, const QString &inputPath, const QString &targetPath, int amount)
{
    return true;
}

QWidget *ClassificationPluginMock::getDataAugmentationInputWidget()
{
    return new QWidget;
}

bool ClassificationPluginMock::removeModel(QString modelName)
{
    return true;
}

TrainingResult *ClassificationPluginMock::train(const QString &modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin *receiver)
{
    if (modelName == "true"){
        // valid result, to make handling valid results testable
        return new TrainingResult("testDir",{{1,{1,1}}}, {"labels"}, {1}, {"image"}, 1,1);
    }
    return new TrainingResult({},{},{},{},{},{},{});
}

ClassificationResult *ClassificationPluginMock::classify(const QString &inputImageDirPath, const QString &trainDatasetPath, const QString &workingDirPath, const QString &modelName, ProgressablePlugin *receiver)
{
    if (inputImageDirPath == "true"){
        // valid result, to make handling valid results testable
        return new ClassificationResult("testDir",{{"string",{1,1}}}, {"labels"});
    }
    return new ClassificationResult({},{},{});
}

