#include "mmclassificationplugin.h"

void MMClassificationPlugin::initBaseModels() {
    auto *resnet50 = new BaseModel("ResNet-50", "resnet50.py", "resnet50_batch256_imagenet_20200708-cfb998bf.pth");
    m_baseModels.append(*resnet50);
    auto *resnet101 = new BaseModel("ResNet-101", "resnet101.py",
                                    "resnet101_batch256_imagenet_20200708-753f3608.pth");
    m_baseModels.append(*resnet101);
    auto *resNeXt32x8d101 = new BaseModel("ResNeXt-32x8d-101", "resnext101_32x8d.py",
                                          "resnext101_32x8d_b32x8_imagenet_20210506-23a247d5.pth");
    m_baseModels.append(*resNeXt32x8d101);
    auto *sEResNet50 = new BaseModel("SE-ResNet-50", "seresnet50.py",
                                     "se-resnet50_batch256_imagenet_20200804-ae206104.pth");
    m_baseModels.append(*sEResNet50);
    auto *mobileNetV3Large = new BaseModel("MobileNetV3 Large", "mobilenet_v3_large_imagenet.py",
                                           "mobilenet_v3_large-3ea3c186.pth");
    m_baseModels.append(*mobileNetV3Large);
}

void MMClassificationPlugin::saveModel(Model model) {
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

Model MMClassificationPlugin::loadModel(const QString &name) {
    if (m_models.childGroups().contains(name)) {
        m_models.beginGroup(name);
        QString modelName = m_models.value(m_modelNameKey).toString();
        QString baseModelName = m_models.value(m_baseModelNameKey).toString();
        QString mainConfigPath = m_models.value(m_mainConfigPathKey).toString();
        QString modelConfigPath = m_models.value(m_modelConfigPathKey).toString();
        QString datasetConfigPath = m_models.value(m_datasetConfigPathKey).toString();
        QString scheduleConfigPath = m_models.value(m_scheduleConfigPathKey).toString();
        QString runtimeConfigPath = m_models.value(m_runtimeConfigPathKey).toString();
        m_models.endGroup();
        return Model(modelName, baseModelName, mainConfigPath, modelConfigPath, datasetConfigPath,
                     scheduleConfigPath, runtimeConfigPath);
    }
    return Model(QString(), QString(), QString(), QString(), QString(), QString(), QString());
}

QStringList MMClassificationPlugin::getLabels(const QString &datasetPath) {
    QStringList labels;
    QDir rootDir(datasetPath);
    rootDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const auto &item: rootDir.entryInfoList()) {
        labels << item.baseName();
    }
    return labels;
}

bool MMClassificationPlugin::checkDataAugmentationPreviewInput(const QString &modelName, const QString &inputPath,
                                                               const QString &targetPath,
                                                               int amount) {
    QDir inputDir(inputPath);
    QDir targetDir(targetPath);
    QString datasetConfigPath = loadModel(modelName).getDatasetConfigPath();
    QFileInfo datasetConfigInfo(datasetConfigPath);
    return inputDir.exists() && targetDir.exists() && amount && datasetConfigInfo.exists();
}

bool MMClassificationPlugin::checkTrainMethodInput(const QStringList &labels, const QString &mainConfigPath,
                                                   const QString &trainDatasetPath,
                                                   const QString &validationDatasetPath,
                                                   const QString &workingDirectoryPath) {
    QFileInfo mainConfigInfo(mainConfigPath);
    QFileInfo trainDatasetInfo(trainDatasetPath);
    QFileInfo validationDatasetInfo(validationDatasetPath);
    QFileInfo workingDirectoryInfo(workingDirectoryPath);
    return !labels.isEmpty() && mainConfigInfo.exists() && trainDatasetInfo.exists() &&
           validationDatasetInfo.exists() && workingDirectoryInfo.exists();
}

void MMClassificationPlugin::adjustCheckpointCreation(const QString &runtimeConfigPath, int max_iters) {
    const int defaultCheckpointCreationStep = 1000;
    if (max_iters % defaultCheckpointCreationStep != 0) {
        m_mmClassificationConfigFileBuilder.changeCheckpointCreationStep(runtimeConfigPath, max_iters);
    } else {
        m_mmClassificationConfigFileBuilder.changeCheckpointCreationStep(runtimeConfigPath,
                                                                         defaultCheckpointCreationStep);
    }
}

QString MMClassificationPlugin::getName() {
    return m_name;
}

QSharedPointer<QWidget> MMClassificationPlugin::getConfigurationWidget() {
    return pluginSettings;
}

void MMClassificationPlugin::saveConfiguration() {
    pluginSettings->saveSettings();
}

QSharedPointer<QWidget> MMClassificationPlugin::getInputWidget() {
    return inputOptions;
}

void MMClassificationPlugin::init() {
    pluginSettings.reset(new MMClassificationSettings, &QObject::deleteLater);
    dataAugmentationInput.reset(new MMClassificationDataAugmentationInput, &QObject::deleteLater);
    inputOptions.reset(new MMClassificationInputOptions, &QObject::deleteLater);
    initBaseModels();
    m_mmClassificationConfigFileBuilder.setPathToMMClassification(pluginSettings->getMMClassificationPath());
    m_watcher.reset(new QFileSystemWatcher);
}

QStringList MMClassificationPlugin::getAssociatedModels() {
    QStringList modelNames;
    for (BaseModel model: m_baseModels) {
        modelNames << model.getName();
    }
    return modelNames;
}

bool MMClassificationPlugin::createNewModel(QString modelName, QString baseModelName) {
    m_mmClassificationConfigFileBuilder.setPathToMMClassification(
            pluginSettings->getMMClassificationPath()); //added must be done before every action???

    const QString modelConfigIdentifier = "_model";
    const QString datasetConfigIdentifier = "_dataset";
    const QString scheduleConfigIdentifier = "_schedule";
    const QString runtimeConfigIdentifier = "_runtime";
    const QString mainConfigIdentifier = "_main";
    bool validBaseModel = false;
    QString baseModelPath;
    QString checkpointFileName;
    for (BaseModel baseModel: m_baseModels) {
        int compareResult = QString::compare(baseModel.getName(), baseModelName);
        if (compareResult != 0) continue;

        validBaseModel = true;
        baseModelPath = baseModel.getRelConfigFilePath();
        checkpointFileName = baseModel.getCheckpointFileName();
        break;
    }
    if (!validBaseModel) return false;

    QString modelConfigPath = m_mmClassificationConfigFileBuilder.createModelConfigFile(
            modelName % modelConfigIdentifier, baseModelPath);
    QString datasetConfigPath = m_mmClassificationConfigFileBuilder.createDatasetConfigFile(
            modelName % datasetConfigIdentifier);
    QString scheduleConfigPath = m_mmClassificationConfigFileBuilder.createScheduleConfigFile(
            modelName % scheduleConfigIdentifier);
    QString defaultRuntimePath = m_mmClassificationConfigFileBuilder.createRuntimeConfigFile(
            modelName % runtimeConfigIdentifier);
    QString checkpointFilePath =
            pluginSettings->getMMClassificationPath() % "/"
            % m_subfolder_checkpoints % "/"
            % checkpointFileName;

    QString absoluteCheckpointFilePath = QFileInfo(checkpointFilePath).absoluteFilePath();

    QString mainConfigPath = m_mmClassificationConfigFileBuilder.createMainConfigFile(
            modelName % mainConfigIdentifier, modelConfigPath, datasetConfigPath,
            scheduleConfigPath, defaultRuntimePath, absoluteCheckpointFilePath);
    Model newModel(modelName, baseModelName, mainConfigPath, modelConfigPath,
                   datasetConfigPath, scheduleConfigPath, defaultRuntimePath);
    saveModel(newModel);

    return true;
}

bool MMClassificationPlugin::removeModel(QString modelName) {
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

bool
MMClassificationPlugin::getAugmentationPreview(const QString &modelName, const QString &inputPath,
                                               const QString &targetPath, int amount) {
    if (!checkDataAugmentationPreviewInput(modelName, inputPath, targetPath, amount)) {
        qWarning() << "Invalid Input";
        return false;
    }

    QDir targetDir(targetPath);
    QString targetAbsolutePath = targetDir.absolutePath();

    // delete old Preview Pictures in the directory
    targetDir.setNameFilters(QStringList() << "*.jpg" << "*.png");
    targetDir.setFilter(QDir::Files);
    for (const QString &dirFile: targetDir.entryList()) {
        targetDir.remove(dirFile);
    }

    // find all subdirectories to distribute evenly between the different classes
    const QString &rootDir = inputPath;
    QDirIterator iter(rootDir, QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList subdirectories;
    while (iter.hasNext()) {
        QString path = iter.next();
        subdirectories.append(path);
    }
    int totalPictures = 0;
    QMap<QString, int> numberPerSubdirectories = {};
    QVector<QString> validExtensions = {".jpg", ".JPG", ".png", ".PNG"};
    int count;
    for (const auto &subdirectory: subdirectories) {
        QDir dir(subdirectory);
        count = 0;
        for (const QFileInfo &file: dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
            if (file.isFile() && file.exists()) {
                for (const auto &validExtension: validExtensions) {
                    if (file.absoluteFilePath().endsWith(validExtension)) {
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
    QMap<QString, int> remainingAmountPerSubdirectory = {};
    if (amount >= totalPictures) {
        // If there are not enough picture, it will get all pictures
        // The same is the case if we only have so many pictures in total
        distribution = numberPerSubdirectories;
    } else {
        for (const auto &[key, _]: MapAdapt(numberPerSubdirectories)) {
            remainingAmountPerSubdirectory.insert(key, numberPerSubdirectories.value(key));
        }
        for (const auto &[key, _]: MapAdapt(numberPerSubdirectories)) {
            distribution.insert(key, 0);
        }
        while (remainingTotalAmount > 0) {
            for (const auto &[key, _]: MapAdapt(remainingAmountPerSubdirectory)) {
                amount = distribution.value(key);
                if (amount < numberPerSubdirectories.value(key)) {
                    amount++;
                    distribution.insert(key, amount);
                    remainingTotalAmount--;
                } else {
                    remainingAmountPerSubdirectory.remove(key);
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

    auto albuTransformType = dataAugmentationInput->getAlbuTransformType();
    auto randomResizedCropSize = dataAugmentationInput->getRandomResizedCropSize();
    auto randomFlipProb = dataAugmentationInput->getRandomFlipProb();
    auto randomFlipDirection = dataAugmentationInput->getRandomFlipDirection();
    auto randomErasing = dataAugmentationInput->getRandomErasing();
    auto resize = dataAugmentationInput->getResize();
    auto centerCropSize = dataAugmentationInput->getCenterCropSize();
    MMClassificationConfigFileBuilder::changeDataAugmentationOptions(datasetConfigPath, albuTransformType,
                                                                     randomResizedCropSize, randomFlipProb,
                                                                     randomFlipDirection, randomErasing, resize,
                                                                     centerCropSize);

    //QString command = m_mmClassificationSettings.getPythonPath();
    //TODO Use python from global settings
    QString command = "python";

    QFileInfo pythonfile = QFileInfo("mmclassification_preview_pipeline.py");
    QString scriptPath = pythonfile.absoluteFilePath();

    QStringList fullCommands = {};

    for (const auto &[sourceDirectoryPath, partAmount]: MapAdapt(distribution)) {
        fullCommands.append(command % " " % scriptPath % " " % datasetConfigPath % " " % sourceDirectoryPath % " " %
                            targetAbsolutePath % " " % QString::number(partAmount));
    }

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QString pathValue = env.value("PATH");

    if (!pluginSettings->getMMClsPath().isEmpty()) {
        pathValue.prepend(pluginSettings->getMMClsPath() % ":");
    }
    if (!pluginSettings->getPythonPath().isEmpty()) {
        pathValue.prepend(pluginSettings->getPythonPath() % ":");
    }

    QProcessEnvironment envUpdate;
    //TODO: EnvUpdate is probably useless, PATH should be included already
    envUpdate.insert("PATH", pathValue);

    for (const QString &fullCommand: fullCommands) {
        QProcess process;
        process.setProcessEnvironment(envUpdate);
        process.startCommand(fullCommand);
        process.waitForFinished();
        qDebug() << qPrintable(process.readAllStandardOutput().simplified());
        process.close();
    }
    return true;
}

TrainingResult *
MMClassificationPlugin::train(const QString &modelName, QString trainDatasetPath, QString validationDatasetPath,
                              QString workingDirectoryPath, ProgressablePlugin *receiver) {
    m_receiver = receiver;

    // get labels to calculate number of classes
    auto modelConfigPath = loadModel(modelName).getModelConfigPath();
    auto labels = getLabels(trainDatasetPath);
    auto mainConfigPath = loadModel(modelName).getMainConfigPath();

    if (!checkTrainMethodInput(labels, mainConfigPath, trainDatasetPath, validationDatasetPath, workingDirectoryPath)) {
        qWarning() << "Invalid input parameters, empty TrainingResult object will be returned";
        return new TrainingResult({}, {}, {}, {}, {}, {}, {});
    }

    m_mmClassificationConfigFileBuilder.changeModelNumberOfClasses(modelConfigPath, labels.size());

    // get the config from the model
    QString datasetConfigPath = loadModel(modelName).getDatasetConfigPath();

    // Change config file according to input
    QString albuTransformType = dataAugmentationInput->getAlbuTransformType();
    int randomResizedCropSize = dataAugmentationInput->getRandomResizedCropSize();
    double randomFlipProb = dataAugmentationInput->getRandomFlipProb();
    QString randomFlipDirection = dataAugmentationInput->getRandomFlipDirection();
    bool randomErasing = dataAugmentationInput->getRandomErasing();
    int resize = dataAugmentationInput->getResize();
    int centerCropSize = dataAugmentationInput->getCenterCropSize();

    MMClassificationConfigFileBuilder::changeDataAugmentationOptions(datasetConfigPath, albuTransformType,
                                                                     randomResizedCropSize, randomFlipProb,
                                                                     randomFlipDirection, randomErasing, resize,
                                                                     centerCropSize);
    m_mmClassificationConfigFileBuilder.changeDatasetPaths(datasetConfigPath, trainDatasetPath, validationDatasetPath,
                                                           validationDatasetPath);

    QString scheduleConfigPath = loadModel(modelName).getScheduleConfigPath();
    m_maxIters = inputOptions->getMaxIters();
    m_mmClassificationConfigFileBuilder.changeScheduleOptions(scheduleConfigPath, m_maxIters);

    // copy and change runtime config if checkpoint creation and max_iters does not fit
    QString runtimeConfigPath = loadModel(modelName).getRuntimeConfigPath();
    adjustCheckpointCreation(runtimeConfigPath, m_maxIters);

    int cudaDeviceNumber = inputOptions->getCudaDevice();

    //TODO: Use python executable from global settings
    QString command = "python";
    auto pythonTrainFile = QFileInfo("mmclassification_train.py");
    auto trainScriptPath = pythonTrainFile.absoluteFilePath();
    const auto workDirConsoleArgument = "--work-dir";

    QStringList fullTrainCommand = {command, trainScriptPath, mainConfigPath, workDirConsoleArgument,
                                    workingDirectoryPath};
    auto env = QProcessEnvironment::systemEnvironment();
    env.insert("CUDA_VISIBLE_DEVICES", QString::number(cudaDeviceNumber));

    m_workDir = workingDirectoryPath;
    m_watcher->addPath(m_workDir);
    connectIt();
    m_process.reset(new QProcess);
    m_process->setProcessEnvironment(env);
    m_process->setReadChannel(QProcess::StandardOutput);
    m_process->startCommand(fullTrainCommand.join(" "));
    m_process->waitForStarted();
    m_process->waitForFinished(-1);

    qDebug() << qPrintable(m_process->readAllStandardOutput().simplified());
    qDebug() << qPrintable(m_process->readAllStandardError().simplified());
    qDebug() << qPrintable(m_process->readAll().simplified());
    m_process->close();

    // Get Results
    const QString checkpointName = "latest.pth";
    const QString metricConsoleArgumentName = "--metrics";
    const QString outputConsoleArgumentName = "--out";

    const QString metricAccuracy = "accuracy";
    const QString metricSupport = "support";

    const QString metricAccuracyOutputName = "resultAccuracy.json";
    const QString metricSupportOutputName = "resultSupport.json";

    const QString withoutMetricSpecifiedOutputName = "resultWithout.json";

    QDir workingDir(workingDirectoryPath);

    const QString pathToAccuracyResultFile = workingDir.absoluteFilePath(metricAccuracyOutputName);
    const QString pathToSupportResultFile = workingDir.absoluteFilePath(metricSupportOutputName);
    const QString pathToWithoutMetricResultFile = workingDir.absoluteFilePath(withoutMetricSpecifiedOutputName);

    qDebug() << "Start Generating Results: ";

    QStringList fullCommands = {};

    QFileInfo testScriptFile = QFileInfo("mmclassification_test.py");
    QString testScriptPath = testScriptFile.absoluteFilePath();
    QString checkpointPath = workingDir.absoluteFilePath(checkpointName);

    QString baseCommand = command % " " % testScriptPath % " " % mainConfigPath % " " % checkpointPath % " ";
    fullCommands.append(baseCommand
                        % metricConsoleArgumentName % "=" % metricAccuracy % " "
                        % outputConsoleArgumentName % "=" % pathToAccuracyResultFile);
    fullCommands.append(baseCommand
                        % metricConsoleArgumentName % "=" % metricSupport % " "
                        % outputConsoleArgumentName % "=" % pathToSupportResultFile);
    fullCommands.append(baseCommand
                        % outputConsoleArgumentName % "=" % pathToWithoutMetricResultFile);

    // execute test process to generate result files
    for (const QString &fullCommand: fullCommands) {
        QProcess process;
        process.startCommand(fullCommand);
        process.waitForStarted();
        process.waitForFinished();
        process.close();
        qDebug() << qPrintable(process.readAllStandardOutput().simplified());
        qDebug() << qPrintable(process.readAllStandardError().simplified());
    }

    const auto &[top1, top5] = m_jsonReader.readTopValuesFromJson(pathToAccuracyResultFile);
    const auto confusionMatrixFileName = "data_confusion_matrix.json";
    // QString pathToConfusionMatrix = m_mmClassificationSettings.getMMClassificationPath()
    // % "/" % confusionMatrixFileName;
    QDir mmPath(pluginSettings->getMMClassificationPath());
    auto pathToConfusionMatrix = mmPath.absoluteFilePath(confusionMatrixFileName);
    auto confusionMatrixData = m_jsonReader.readConfusionMatrixFromJsonFile(pathToConfusionMatrix);

    // Search for log file
    workingDir.setNameFilters(QStringList() << "*.log.json");
    workingDir.setFilter(QDir::Files);
    QString logFileName;
    for (const QString &dirFile: workingDir.entryList()) {
        //TODO replace these loops with something better
        logFileName = dirFile;
    }
    QString absoluteLogFilePath = workingDir.absoluteFilePath(logFileName);

    auto accuracyCurveData = m_jsonReader.getAccuracyCurve(absoluteLogFilePath);

    QDir datasetDirectory(trainDatasetPath);
    datasetDirectory.cdUp();
    auto validationAnnotationFilePath = datasetDirectory.absoluteFilePath(m_annotationFileName);

    auto mostMisclassifiedImages =
            m_jsonReader.generateMostMissclassifiedImages(m_numberOfMissClassifiedImages,
                                                          validationAnnotationFilePath,
                                                          pathToWithoutMetricResultFile);

    return new TrainingResult(workingDirectoryPath, accuracyCurveData, labels, confusionMatrixData,
                              mostMisclassifiedImages, top1, top5);
}

ClassificationResult *
MMClassificationPlugin::classify(const QString &inputImageDirPath, const QString &trainDatasetPath,
                                 const QString &workingDirPath,
                                 const QString &modelName, ProgressablePlugin *receiver) {
    m_receiver = receiver;
    QDir workingDir(workingDirPath);

    const QString checkpointName = "latest.pth";
    const QString outputConfidenceScoreConsoleArgumentName = "--confidenceScoresOut";
    const QString outputConfidenceScoreResultName = "resultConfidenceScore.json";

    const QString pathToConfidenceScoreResultFile = workingDir.absoluteFilePath(outputConfidenceScoreResultName);
    const QString checkpointPath = workingDir.absoluteFilePath(checkpointName);

    QString mainConfigPath = loadModel(modelName).getMainConfigPath();
    // get train dataset path from dataset config file to extract the labels
    QString datasetConfigPath = loadModel(modelName).getDatasetConfigPath();

    m_mmClassificationConfigFileBuilder.changeTestPath(datasetConfigPath, inputImageDirPath);
    QFileInfo checkpointInfo(checkpointPath);

    if (mainConfigPath.isEmpty() || !checkpointInfo.exists()) {
        qWarning() << "mainConfigFile or checkpointFile does not exist";
        return new ClassificationResult({}, {}, {});
    }

    //TODO Use python from global settings
    QString command = "python";
    auto pythonfile = QFileInfo("mmclassification_test.py");
    auto scriptPath = pythonfile.absoluteFilePath();

    QString fullCommand = command % " " % scriptPath % " "
                       % mainConfigPath % " " % checkpointPath % " "
                       % outputConfidenceScoreConsoleArgumentName % "=" % pathToConfidenceScoreResultFile;

    m_process.reset(new QProcess);
    m_process->setReadChannel(QProcess::StandardOutput);
    connect(&*m_process, &QProcess::readyReadStandardOutput, this, &MMClassificationPlugin::slot_readClassifyOutput);
    m_process->startCommand(fullCommand);
    m_process->waitForStarted();
    m_process->waitForFinished();

    // Get the output
    qDebug() << qPrintable(m_process->readAllStandardOutput().simplified());
    qDebug() << qPrintable(m_process->readAllStandardError().simplified());
    m_process->close();

    QStringList inputImageFilePaths = {};

    // read subdirectories and take image paths
    QDir imageRootDir(inputImageDirPath);
    imageRootDir.setFilter(QDir::Dirs);
    for (const auto &item: imageRootDir.entryInfoList()) {
        QDir inputImageSubDirectory(item.absoluteFilePath());
        inputImageSubDirectory.setNameFilters(QStringList() << "*.jpg" << "*.png");
        inputImageSubDirectory.setFilter(QDir::Files);
        for (const QString &imageFile: inputImageSubDirectory.entryList()) {
            inputImageFilePaths.append(inputImageDirPath + "/" + item.baseName() + "/" + imageFile);
        }
    }

    QMap<QString, QList<double>> data;
    QList<QString> labels = getLabels(trainDatasetPath);
    QStringList additionalMetrics;

    if (!inputImageFilePaths.empty()) {
        data = m_jsonReader.readConfidenceScores(pathToConfidenceScoreResultFile, inputImageFilePaths);
        qDebug() << "content: " << data;
    }
    return new ClassificationResult(workingDirPath, data, labels, additionalMetrics);
}

QSharedPointer<QWidget> MMClassificationPlugin::getDataAugmentationInputWidget() {
    return dataAugmentationInput;
}

void MMClassificationPlugin::slot_readClassifyOutput() {
    const QString proportionRegularExpressionText = "[0-9]+\\/[0-9]+";
    QString line = QString::fromLocal8Bit(m_process->readLine());
    if (!line.isEmpty()) {
        QRegularExpression regularExpression(proportionRegularExpressionText);
        QRegularExpressionMatch match;
        match = regularExpression.match(line);
        if (match.hasMatch()) {
            QString lastCapturedProportion = match.captured(match.lastCapturedIndex());
            QStringList pieces = lastCapturedProportion.split("/");
            int progress = qCeil((pieces.at(0).toInt() * 100) / pieces.at(1).toInt());
            m_receiver->slot_makeProgress(progress);
        }
    }
}

void MMClassificationPlugin::slot_checkForLogFile(const QString & /*path*/) {
    QDir directory(m_workDir);
    QStringList logFiles = directory.entryList(QStringList() << "*.log.json", QDir::Files);
    if (!logFiles.isEmpty()) {
        for (const QString &filename: logFiles) {
            // disconnect due to found log file and monitor file directly
            QObject::disconnect(&*m_watcher, &QFileSystemWatcher::directoryChanged, this,
                                &MMClassificationPlugin::slot_checkForLogFile);
            const QString logFilePath = m_workDir + "/" + filename;
            connectFileWatcher(logFilePath);
        }
    }
}

void MMClassificationPlugin::slot_readChangeInLogFile(const QString &path) {
    const QString modeForProgress = "train";
    QFileInfo jsonLogFile = QFileInfo(path);
    QFile inFile(jsonLogFile.absoluteFilePath());
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList data = {};
    QTextStream in(&inFile);
    QString line = in.readLine();
    while (!line.isNull() && !line.isEmpty()) {
        line = in.readLine();
        data.append(line);
    }
    inFile.close();
    if (data.size() > 1) {
        int offset = 1;
        QJsonParseError errorPtr;
        while (data[data.size() - offset].isEmpty()) {
            offset++;
        }
        QJsonDocument doc = QJsonDocument::fromJson(data[data.size() - offset].toUtf8(), &errorPtr);
        if (doc.isNull()) {
            qWarning() << "Parse failed";
        }
        QJsonObject rootObj = doc.object();
        if (rootObj.contains("iter") && rootObj.contains("mode")) {
            QString mode = rootObj.value("mode").toString();
            if (!mode.compare(modeForProgress)) {
                int iter = rootObj.value("iter").toInt();
                int progress = qCeil((iter * 100) / m_maxIters);
                m_receiver->slot_makeProgress(progress);
            }
        }
    }
}

void MMClassificationPlugin::connectIt() {
    connect(&*m_watcher, &QFileSystemWatcher::directoryChanged, this, &MMClassificationPlugin::slot_checkForLogFile);
}

void MMClassificationPlugin::connectFileWatcher(const QString &path) {
    QFileInfo info(path);
    m_watcher->removePath(m_workDir);
    m_watcher->addPath(path);
    QObject::connect(&*m_watcher, &QFileSystemWatcher::fileChanged, this,
                     &MMClassificationPlugin::slot_readChangeInLogFile);
}
