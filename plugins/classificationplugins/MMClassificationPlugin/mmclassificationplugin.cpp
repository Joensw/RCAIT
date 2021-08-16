#include "mmclassificationplugin.h"


MMClassificationPlugin::MMClassificationPlugin()
{
    pluginSettings = new MMClassificationSettings();
    dataAugmentationInput = new MMClassificiationDataAugmentationInput();
    inputOptions = new MMClassificationInputOptions();
    initBaseModels();
    m_mmClassificationConfigFileBuilder.setPathToMMClassification(m_mmClassificationSettings.getMMClassificationPath());
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

QStringList MMClassificationPlugin::getLabels(QString datasetPath)
{
    QString rootDir = datasetPath;
    QDirIterator iter( rootDir, QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList labels;
    while(iter.hasNext() )
    {
        QString path = iter.next();
        QDir dir(path);
        labels.append(dir.dirName());
    }
    return labels;
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

void MMClassificationPlugin::init()
{
    pluginSettings = new MMClassificationSettings();
    dataAugmentationInput = new MMClassificiationDataAugmentationInput();
    inputOptions = new MMClassificationInputOptions();
    initBaseModels();
    m_mmClassificationConfigFileBuilder.setPathToMMClassification(m_mmClassificationSettings.getMMClassificationPath());
    m_mmclassificiationdataaugmentationinput = qobject_cast<MMClassificiationDataAugmentationInput *>(dataAugmentationInput);
    m_mmClassificationInput = qobject_cast<MMClassificationInputOptions *>(inputOptions);
}

QStringList MMClassificationPlugin::getAssociatedModels()
{
    QStringList modelNames = {};
    foreach(BaseModel model, *m_baseModels) {
        modelNames.append(model.getName());
    }
    return modelNames;
}

bool MMClassificationPlugin::createNewModel(QString modelName, QString baseModelName)
{
    m_mmClassificationConfigFileBuilder.setPathToMMClassification(m_mmClassificationSettings.getMMClassificationPath()); //added must be done before every action???

    const QString modelConfigIdentifier = "_model";
    const QString datasetConfigIdentifier = "_dataset";
    const QString scheduleConfigIdentifier = "_schedule";
    const QString mainConfigIdentifier = "_main";
    bool validBaseModel = false;
    QString baseModelPath;
    QString checkpointFileName;
    QList<BaseModel> baseModels = *m_baseModels;
    foreach (BaseModel baseModel, baseModels) {
        int compareResult = QString::compare(baseModel.getName(), baseModelName);
        if (compareResult == 0) {
            validBaseModel = true;
            baseModelPath = baseModel.getRelConfigFilePath();
            checkpointFileName = baseModel.getCheckpointFileName();
            break;
        }
    }
    if (validBaseModel) {
        QString modelConfigPath = m_mmClassificationConfigFileBuilder.createModelConfigFile(modelName + modelConfigIdentifier, baseModelPath);
        QString datasetConfigPath = m_mmClassificationConfigFileBuilder.createDatasetConfigFile(modelName + datasetConfigIdentifier);
        QString scheduleConfigPath = m_mmClassificationConfigFileBuilder.createScheduleConfigFile(modelName + scheduleConfigIdentifier);
        // default runtime is sufficient in most cases
        QString defaultRuntimePath = m_mmClassificationConfigFileBuilder.getDefaultRuntimeConfigFilePath();
        QString checkpointFilePath = m_mmClassificationSettings.getMMClassificationPath() + QDir::fromNativeSeparators(QDir::separator())
                + m_subfolder_checkpoints + QDir::fromNativeSeparators(QDir::separator()) + checkpointFileName;


        QString absoluteCheckpointFilePath =  QFileInfo(checkpointFilePath).absoluteFilePath();

        QString mainConfigPath = m_mmClassificationConfigFileBuilder.createMainConfigFile(modelName + mainConfigIdentifier, modelConfigPath, datasetConfigPath,
                                                                                          scheduleConfigPath, defaultRuntimePath, absoluteCheckpointFilePath);
        Model newModel(modelName, baseModelName, mainConfigPath, modelConfigPath, datasetConfigPath, scheduleConfigPath, defaultRuntimePath);
        saveModel(newModel);
        return true;
    }
    return false;
}

bool MMClassificationPlugin::removeModel(QString modelName)
{
    Model existingModel = loadModel(modelName);
    if (existingModel.isValid()) {
        QString mainConfigPath = existingModel.getMainConfigPath();
        QFile::remove(mainConfigPath);
        QString modelConfigPath = existingModel.getModelConfigPath();
        QFile::remove(modelConfigPath);
        QString datasetConfigPath = existingModel.getDatasetConfigPath();
        QFile::remove(datasetConfigPath);
        QString scheduleConfigPath = existingModel.getScheduleConfigPath();
        QFile::remove(scheduleConfigPath);
        QString runtimeConfigPath = existingModel.getRuntimeConfigPath();
        if (!runtimeConfigPath.endsWith(m_mmClassificationConfigFileBuilder.getDefaultRuntimeConfigFilePath())) {
            QFile::remove(runtimeConfigPath);
        }
        m_models.beginGroup(modelName);
        m_models.remove(""); //removes the group and all it keys
        m_models.endGroup();
        return true;
    } else {
        return false;
    }
}

bool MMClassificationPlugin::getAugmentationPreview(QString modelName, QString inputPath, QString targetPath, int amount)
{
    QDir targetDir(targetPath);
    if (!targetDir.exists() || amount == 0 || inputPath.isEmpty() || targetPath.isEmpty()) {
        return false;
    }
    QString targetAbsolutePath = targetDir.absolutePath();

    // delete old Preview Pictures in the directory
    targetDir.setNameFilters(QStringList() << "*.jpg" << "*.png");
    targetDir.setFilter(QDir::Files);
    foreach(QString dirFile, targetDir.entryList())
    {
        targetDir.remove(dirFile);
    }

    // find all subdirectories to distribute evenly between the different classes
    QString rootDir = inputPath;
    QDirIterator iter( rootDir, QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList subdirectories;
    while(iter.hasNext() )
    {
        QString path = iter.next();
        subdirectories.append(path);
    }
    int totalPictures = 0;
    QMap<QString, int> numberPerSubdirectories = {};
    QVector<QString> validExtensions = {".jpg", ".JPG", ".png", ".PNG"};
    int count = 0;
    for (int i = 0; i < subdirectories.size(); i++) {
        QDir dir = subdirectories.at(i);
        QFileInfoList list = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
        count = 0;
        foreach(QFileInfo file, list) {
            if(file.isFile() && file.exists()) {
                for (int j = 0; j < validExtensions.size(); j++) {
                    if (file.absoluteFilePath().endsWith(validExtensions.at(j))) {
                        count++;
                    }
                }
            }
        }
        numberPerSubdirectories.insert(dir.path(), count);
        totalPictures += count;
    }
    int remainingTotalAmount = amount;
    QMap<QString, int> distribution = {};
    QMap<QString, int> remainingAmountPerSubdirectiorie = {};
    if (amount >= totalPictures) {
        // If there are not enough picture, it will get all pictures
        // The same is the case if we only have so many pictures in total
        distribution = numberPerSubdirectories;
    } else {
        foreach (QString key, numberPerSubdirectories.keys()) {
            remainingAmountPerSubdirectiorie.insert(key, numberPerSubdirectories.value(key));
        }
        foreach (QString key, numberPerSubdirectories.keys()) {
            distribution.insert(key, 0);
        }
        while (remainingTotalAmount > 0) {
            foreach(QString key, remainingAmountPerSubdirectiorie.keys()) {
                amount = distribution.value(key);
                if (amount < numberPerSubdirectories.value(key)) {
                    amount++;
                    distribution.insert(key, amount);
                    remainingTotalAmount--;
                } else {
                    remainingAmountPerSubdirectiorie.remove(key);
                }
                if (remainingTotalAmount == 0) {
                    break;
                }
            }
        }
    }
    // get the config from the model
    QString datasetConfigPath = loadModel(modelName).getDatasetConfigPath();

    // Change config file according to input

    m_mmclassificiationdataaugmentationinput->readDataAugmentationInput();

    QString albuTransformType = m_mmclassificiationdataaugmentationinput->getAlbuTransformType();
    int randomResizedCropSize = m_mmclassificiationdataaugmentationinput->getRandomResizedCropSize();
    double randomFlipProb = m_mmclassificiationdataaugmentationinput->getRandomFlipProb();
    QString randomFlipDirection = m_mmclassificiationdataaugmentationinput->getRandomFlipDirection();
    bool randomErasing = m_mmclassificiationdataaugmentationinput->getRandomErasing();
    int resize = m_mmclassificiationdataaugmentationinput->getResize();
    int centerCropSize = m_mmclassificiationdataaugmentationinput->getCenterCropSize();
    m_mmClassificationConfigFileBuilder.changeDataAugmentationOptions(datasetConfigPath, albuTransformType, randomResizedCropSize, randomFlipProb,
                                                                      randomFlipDirection, randomErasing, resize, centerCropSize);

    //QString command = m_mmClassificationSettings.getPythonPath();
    QString command = "python";

    QFileInfo pythonfile = QFileInfo("mmclassification_preview_pipeline.py");
    QString scriptPath = pythonfile.absoluteFilePath();

    QStringList fullCommands = {};
    QString sourceDirectoryPath;
    int partAmount;

    foreach (QString key, distribution.keys()) {
        sourceDirectoryPath = key;
        partAmount = distribution.value(key);

        fullCommands.append(command + " " + scriptPath + " " + datasetConfigPath + " " + sourceDirectoryPath + " " + targetAbsolutePath + " " + QString::number(partAmount));
    }

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QProcessEnvironment envUpdate;

    QString pathValue = env.value("PATH");

    if (!m_mmClassificationSettings.getMMClsPath().isEmpty()) {
        //  if (!pathValue.isEmpty()) {
        //    pathValue += ";";
        // }
        pathValue.prepend(m_mmClassificationSettings.getMMClsPath() + ":");
    }
    if (!m_mmClassificationSettings.getPythonPath().isEmpty()) {
        // if (!pathValue.isEmpty()) {
        //     pathValue += ";";
        //}
        pathValue.prepend(m_mmClassificationSettings.getPythonPath() + ":");
    }

    envUpdate.insert("PATH", pathValue);

    foreach (QString fullCommand, fullCommands) {
        QProcess* process;
        process = new QProcess();

        process->setProcessEnvironment(envUpdate);

        process->startCommand(fullCommand);

        process->waitForFinished();
        QString strTemp=QString::fromLocal8Bit(process->readAllStandardOutput());

    }
    return true;
}

TrainingResult* MMClassificationPlugin::train(QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectoryPath, ProgressablePlugin *receiver)
{
    const QString workDirConsoleArgument = "--work-dir";
    m_receiver = receiver;

    // get labels to calculate number of classes
    QString modelConfigPath = loadModel(modelName).getModelConfigPath();

    QStringList labels = getLabels(trainDatasetPath);

    if (labels.size() == 0) {
        qWarning() << "no labels found!!!";
        // Test data must be replaced
        QStringList labels = {"cats", "dogs"};
        QList<int> values = {29, 33, 22, 11};
        //ConfusionMatrix * confusionMatrix = new ConfusionMatrix("matrix1", labels, values);
        QMap<int, QPair<double, double>> *accuracyCurveData = new QMap<int, QPair<double, double>>();
        QStringList * mostMisclassifiedImages = new QStringList();
        QStringList *additionalResults = new QStringList();
        double top1Accuracy = 0.91;
        double top5Accuracy = 0.98;
        TrainingResult * trainingResult = new TrainingResult(*accuracyCurveData, labels, values, *mostMisclassifiedImages, top1Accuracy, top5Accuracy, *additionalResults);
        return trainingResult;
    }

    m_mmClassificationConfigFileBuilder.changeModelNumberOfClasses(modelConfigPath, labels.size());

    // get the config from the model
    QString datasetConfigPath = loadModel(modelName).getDatasetConfigPath();

   // not needed during an automation process, mode must set or signal/slot mechanics
    m_mmclassificiationdataaugmentationinput->readDataAugmentationInput();

    // Change config file according to input
    QString albuTransformType = m_mmclassificiationdataaugmentationinput->getAlbuTransformType();
    int randomResizedCropSize = m_mmclassificiationdataaugmentationinput->getRandomResizedCropSize();
    double randomFlipProb = m_mmclassificiationdataaugmentationinput->getRandomFlipProb();
    QString randomFlipDirection = m_mmclassificiationdataaugmentationinput->getRandomFlipDirection();
    bool randomErasing = m_mmclassificiationdataaugmentationinput->getRandomErasing();
    int resize = m_mmclassificiationdataaugmentationinput->getResize();
    int centerCropSize = m_mmclassificiationdataaugmentationinput->getCenterCropSize();
    m_mmClassificationConfigFileBuilder.changeDataAugmentationOptions(datasetConfigPath, albuTransformType, randomResizedCropSize, randomFlipProb,
                                                                      randomFlipDirection, randomErasing, resize, centerCropSize);
    m_mmClassificationConfigFileBuilder.changeDatasetPaths(datasetConfigPath, trainDatasetPath, validationDatasetPath, validationDatasetPath);

    QString scheduleConfigPath = loadModel(modelName).getScheduleConfigPath();

    m_mmClassificationInput->readInput();
    int max_iters = m_mmClassificationInput->getMaxIters();

    m_mmClassificationConfigFileBuilder.changeScheduleOptions(scheduleConfigPath, max_iters);

    // copy and change runtime config if checkpoint creation and max_iters does not fit
    // to do

    QString mainConfigPath = loadModel(modelName).getMainConfigPath();

    int cudaDeviceNumber = m_mmClassificationInput->getCudaDevice();

    QString command = "python";

    QFileInfo pythonTrainFile = QFileInfo("mmclassification_train.py");
    QString trainScriptPath = pythonTrainFile.absoluteFilePath();

    QString fullTrainCommand;

    fullTrainCommand = command + " " + trainScriptPath + " " + mainConfigPath + " " + workDirConsoleArgument + " " + workingDirectoryPath;

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    env.insert("CUDA_VISIBLE_DEVICES", QString::number(cudaDeviceNumber));

    // QProcess* process;
    m_process = new QProcess();

    m_process->setProcessEnvironment(env);

    m_process->setReadChannel(QProcess::StandardOutput);

    m_process->startCommand(fullTrainCommand);

    m_process->waitForStarted();
    m_process->waitForFinished(-1);

    QString strTemp=QString::fromLocal8Bit(m_process->readAllStandardOutput());  // Get the output
    qDebug() << qPrintable(strTemp);
    qDebug()<< QString::fromLocal8Bit(m_process->readAllStandardError());

    qDebug() << QString::fromLocal8Bit(m_process->readAll());

    // Get Results
    const QString checkpointName = "latest.pth";
    const QString metricConsoleArgumentName = "--metrics";
    const QString outputConsoleArgumentName = "--out";

    const QString metricAccuracy = "accuracy";
    const QString metricSupport = "support";

    const QString metricAccuracyOutputName = "resultAccuracy.json";
    const QString metricSupportOutputName = "resultSupport.json";

    const QString withoutMetricSpecifiedOutputName = "resultWithout.json";

    const QString pathToAccuracyResultFile = workingDirectoryPath + "/" + metricAccuracyOutputName;
    const QString pathToSupportResultFile = workingDirectoryPath + "/" + metricSupportOutputName;
    const QString pathToWithoutMetricResultFile = workingDirectoryPath + "/" + withoutMetricSpecifiedOutputName;

    qDebug() << "Start Generating Results:";

    QStringList fullCommands = {};

    QFileInfo testScriptFile = QFileInfo("mmclassification_test.py");
    QString testScriptPath = testScriptFile.absoluteFilePath();

    QString checkpointPath = workingDirectoryPath + "/" + checkpointName;

    fullCommands.append(command + " " + testScriptPath + " " + mainConfigPath + " " + checkpointPath + " " + metricConsoleArgumentName
    + "=" + metricAccuracy + " " + outputConsoleArgumentName + "=" + pathToAccuracyResultFile);
    fullCommands.append(command + " " + testScriptPath + " " + mainConfigPath + " " + checkpointPath + " " + metricConsoleArgumentName
    + "=" + metricSupport + " " + outputConsoleArgumentName + "=" + pathToSupportResultFile);
    fullCommands.append(command + " " + testScriptPath + " " + mainConfigPath + " " + checkpointPath + " " + outputConsoleArgumentName + "=" + pathToWithoutMetricResultFile);

    // execute test process to generate result files
    foreach(QString fullCommand, fullCommands) {
        QProcess* process;
        process = new QProcess();
        process->startCommand(fullCommand);
        process->waitForStarted();
        process->waitForFinished();
        QString strTemp2=QString::fromLocal8Bit(process->readAllStandardOutput());  // Get the output
        qDebug() << qPrintable(strTemp2);
        qDebug()<< QString::fromLocal8Bit(process->readAllStandardError());
    }
    QPair<double, double> accuracies = m_jsonReader.readTopValuesFromJson(pathToAccuracyResultFile);
    const QString confusionMatrixFileName = "data_confusion_matrix.json";
    // QString pathToConfusionMatrix = m_mmClassificationSettings.getMMClassificationPath() + "/" + confusionMatrixFileName;
    QString pathToConfusionMatrix = m_mmClassificationSettings.getMMClassificationPath() + "/" + confusionMatrixFileName;
    QVector<int> confusionMatrixData = m_jsonReader.readConfusionMatrixFromJsonFile(pathToConfusionMatrix);

    // Search for log file
    QString pathToLogFile = "";

    QDir workingDirectory(workingDirectoryPath);
    workingDirectory.setNameFilters(QStringList() << "*.log.json");
    workingDirectory.setFilter(QDir::Files);
    foreach(QString dirFile, workingDirectory.entryList())
    {
        pathToLogFile = dirFile;
    }

    QMap<int, QPair<double, double>> accuracyCurveData = m_jsonReader.getAccuracyCurve(pathToLogFile);

    QDir datasetDirectory(trainDatasetPath);
    datasetDirectory.cdUp();
    QString validationAnnotationFilePath = datasetDirectory.absoluteFilePath(m_annotationFileName);

    QStringList mostMisclassifiedImages = m_jsonReader.generateMostMissclassifiedImages(m_numberOfMissClassifiedImages, validationAnnotationFilePath, pathToWithoutMetricResultFile);

    const QStringList * additionalResults = new QStringList();

    TrainingResult * trainingResult = new TrainingResult(accuracyCurveData, labels, confusionMatrixData, mostMisclassifiedImages, accuracies.first, accuracies.second, *additionalResults);

    return trainingResult;
}

ClassificationResult* MMClassificationPlugin::classify(QString inputImageDirPath,QString trainDatasetPath, QString workingDirPath, QString modelName, ProgressablePlugin *receiver)
{
    const QString checkpointName = "latest.pth";
    const QString outputConfidenceScoreConsoleArgumentName = "--confidenceScoresOut";
    const QString outputConfidenceScoreResultName = "resultConfidenceScore.json";
    const QString pathToConfidenceScoreResultFile = workingDirPath + "/" + outputConfidenceScoreResultName;

    m_receiver = receiver;

    QMap<QString, QList<double>> data = {};
    QList<QString> labels = {};
    QStringList additionalMetrics = {};

    QString mainConfigPath = loadModel(modelName).getMainConfigPath();
    // get train dataset path from dataset config file to extract the labels
    QString datasetConfigPath = loadModel(modelName).getDatasetConfigPath();

    m_mmClassificationConfigFileBuilder.changeTestPath(datasetConfigPath, inputImageDirPath);
    labels = getLabels(trainDatasetPath);
    QString checkpointPath = workingDirPath + "/" + checkpointName;
    QFileInfo checkpointInfo(checkpointPath);

    if (mainConfigPath.isEmpty() || !checkpointInfo.exists()) {
        qWarning() << "mainConfigFile or checkpointFile does not exist";
        return new ClassificationResult(data, labels, additionalMetrics);
    }

    QString command = "python";
    QFileInfo pythonfile = QFileInfo("mmclassification_test.py");
    QString scriptPath = pythonfile.absoluteFilePath();

    QString fullCommand = command + " " + scriptPath + " " + mainConfigPath + " " + checkpointPath + " " + outputConfidenceScoreConsoleArgumentName + "=" + pathToConfidenceScoreResultFile;

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    m_process = new QProcess();
    m_process->startCommand(fullCommand);
    m_process->waitForStarted();
    m_process->waitForFinished();
    QString strTemp=QString::fromLocal8Bit(m_process->readAllStandardOutput());  // Get the output
    qDebug() << qPrintable(strTemp);
    qDebug()<< QString::fromLocal8Bit(m_process->readAllStandardError());

    // new json file with complete data
    QStringList inputImageFilePaths = {};
    QDir inputImageDirectory(inputImageDirPath);
    inputImageDirectory.setNameFilters(QStringList() << "*.jpg" << "*.png");
    inputImageDirectory.setFilter(QDir::Files);
    foreach(QString imageFile, inputImageDirectory.entryList())
    {
        inputImageFilePaths.append(imageFile);
    }
    if (inputImageFilePaths.size() > 0) {
        data = m_jsonReader.readConfidenceScores(pathToConfidenceScoreResultFile, inputImageFilePaths);
        qDebug() << "content: " << data;
    }
    return new ClassificationResult(data, labels, additionalMetrics);
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
