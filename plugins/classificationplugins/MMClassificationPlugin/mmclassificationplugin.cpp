#include "mmclassificationplugin.h"


MMClassificationPlugin::MMClassificationPlugin()
{
    pluginSettings = new MMClassificationSettings();
    dataAugmentationInput = new MMClassificiationDataAugmentationInput();
    inputOptions = new MMClassificationInputOptions();
    initBaseModels();
    m_mmclassificiationdataaugmentationinput = qobject_cast<MMClassificiationDataAugmentationInput *>(dataAugmentationInput);
    m_mmClassificationInput = qobject_cast<MMClassificationInputOptions *>(inputOptions);
}

MMClassificationPlugin::~MMClassificationPlugin()
{
    delete m_baseModels;
}

void MMClassificationPlugin::initBaseModels()
{
    m_baseModels = new QList<BaseModel>;
    BaseModel* resnet50 = new BaseModel("Resnet50", "/resnet50.py", "resnet50_batch256_imagenet_20200708-cfb998bf.pth");
    m_baseModels->append(*resnet50);
    BaseModel* resnet101 = new BaseModel("ResNet-101", "/resnet101.py", "resnet101_batch256_imagenet_20200708-753f3608.pth");
    m_baseModels->append(*resnet101);
    BaseModel* resNeXt32x8d101 = new BaseModel("ResNeXt-32x8d-101", "/resnext101_32x8d.py", "resnext101_32x8d_b32x8_imagenet_20210506-23a247d5.pth");
    m_baseModels->append(*resNeXt32x8d101);
    BaseModel* sEResNet50 = new BaseModel("SE-ResNet-50", "/seresnet50.py", "se-resnet50_batch256_imagenet_20200804-ae206104.pth");
    m_baseModels->append(*sEResNet50);
    BaseModel* mobileNetV3Large = new BaseModel("MobileNetV3 Large", "/mobilenet_v3_large_imagenet.py", "mobilenet_v3_large-3ea3c186.pth");
    m_baseModels->append(*mobileNetV3Large);
}

void MMClassificationPlugin::deleteBaseModels()
{
    delete m_baseModels;
}

void MMClassificationPlugin::saveModel(Model model)
{
    m_models.beginGroup(model.getName());
    m_models.setValue(m_modelNameKey, model.getName());
    m_models.setValue(m_baseModelNameKey, model.getBaseModelName());
    m_models.setValue(m_mainConfigPathKey, model.getMainConfigPath());
    m_models.setValue(m_modelConfigPathKey, model.getModelConfigPath());
    m_models.setValue(m_datasetConfigPathKey, model.getDatasetConfigPath());
    m_models.setValue(m_scheduleConfigPathKey, model.getScheduleConfigPath());
    m_models.setValue(m_runtimeConfigPathKey, model.getRuntimeConfigPath());
    m_models.endGroup();
}

Model MMClassificationPlugin::loadModel(QString name)
{
    if(m_models.childGroups().contains(name)) {
        m_models.beginGroup(name);
        QString modelName = m_models.value(m_modelNameKey).toString();
        QString baseModelName = m_models.value(m_baseModelNameKey).toString();
        QString mainConfigPath = m_models.value(m_mainConfigPathKey).toString();
        QString modelConfigPath = m_models.value(m_modelConfigPathKey).toString();
        QString datasetConfigPath = m_models.value(m_datasetConfigPathKey).toString();
        QString scheduleConfigPath = m_models.value(m_scheduleConfigPathKey).toString();
        QString runtimeConfigPath = m_models.value(m_runtimeConfigPathKey).toString();
        m_models.endGroup();
        Model* model = new Model(modelName, baseModelName, mainConfigPath, modelConfigPath, datasetConfigPath, scheduleConfigPath, runtimeConfigPath);
        return *model;
    }
    return Model(QString(), QString(), QString(), QString(), QString(), QString(), QString());
}

QString MMClassificationPlugin::getName()
{
    return m_name;
}

QWidget* MMClassificationPlugin::getConfigurationWidget()
{
    return pluginSettings;
}

void MMClassificationPlugin::saveConfiguration()
{
    qobject_cast<MMClassificationSettings *>(pluginSettings)->saveSettings();
}

QWidget* MMClassificationPlugin::getInputWidget()
{
    return inputOptions;
}

QStringList MMClassificationPlugin::getAssociatedModels()
{
    QStringList modelNames = {};
    foreach(BaseModel model, *m_baseModels) {
        modelNames.append(model.getName());
    }
    return modelNames;
}

bool MMClassificationPlugin::createNewModel(QString modelName, QString baseModel)
{

}

bool MMClassificationPlugin::removeModel(QString modelName)
{

}

bool MMClassificationPlugin::getAugmentationPreview(QString modelName, QString inputPath, QString targetPath, int amount)
{

}

TrainingResult* MMClassificationPlugin::train(QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin *receiver)
{

}

ClassificationResult* MMClassificationPlugin::classify(QString inputImageDirPath,QString trainDatasetPath, QString workingDirPath, QString modelName, ProgressablePlugin *receiver)
{

}

QWidget* MMClassificationPlugin::getDataAugmentationInputWidget()
{
    return dataAugmentationInput;
}

void MMClassificationPlugin::slot_readOutPut()
{

}

void MMClassificationPlugin::slot_pluginFinished()
{

}
