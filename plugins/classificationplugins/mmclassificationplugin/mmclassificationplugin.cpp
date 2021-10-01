#include "mmclassificationplugin.h"

void MMClassificationPlugin::initBaseModels() {
    auto baseModels = {
            new BaseModel("ResNet-50", "resnet50.py",
                          "resnet50_batch256_imagenet_20200708-cfb998bf.pth"),
            new BaseModel("ResNet-101", "resnet101.py",
                          "resnet101_batch256_imagenet_20200708-753f3608.pth"),
            new BaseModel("ResNeXt-32x8d-101", "resnext101_32x8d.py",
                          "resnext101_32x8d_b32x8_imagenet_20210506-23a247d5.pth"),
            new BaseModel("SE-ResNet-50", "seresnet50.py",
                          "se-resnet50_batch256_imagenet_20200804-ae206104.pth"),
            new BaseModel("MobileNetV3 Large", "mobilenet_v3_large_imagenet.py",
                          "mobilenet_v3_large-3ea3c186.pth")
    };

    for (const auto &model: baseModels) {
        m_baseModelsMap[model->getName()].reset(model);
    }
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
    return Model({}, {}, {}, {}, {}, {}, {});
}

QStringList MMClassificationPlugin::getLabels(const QString &datasetPath) {
    QStringList labels;
    QDir rootDir(datasetPath);

    for (const auto &item: rootDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
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

bool MMClassificationPlugin::checkTrainMethodInput(const QStringList &labels, const QStringList &paths) {
    bool allPathsExist = std::all_of(paths.begin(), paths.end(),
                                     [](const QString &path) { return QFileInfo::exists(path); });
    return !labels.isEmpty() && allPathsExist;
}

void MMClassificationPlugin::adjustCheckpointCreation(const QString &runtimeConfigPath, int max_iters) {
    static const int defaultCPStep = 1000;
    auto step = (max_iters % defaultCPStep == 0) ? defaultCPStep : max_iters;
    m_configFileBuilder.changeCheckpointCreationStep(runtimeConfigPath, step);
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
    m_configFileBuilder.setPathToMMClassification(pluginSettings->getMMClassificationPath());
    m_watcher.reset(new QFileSystemWatcher);
    initBaseModels();
}

QStringList MMClassificationPlugin::getAssociatedModels() {
    return m_baseModelsMap.keys();
}

bool MMClassificationPlugin::createNewModel(QString modelName, QString baseModelName) {
    m_configFileBuilder.setPathToMMClassification(
            pluginSettings->getMMClassificationPath()); //added must be done before every action???

    static constexpr auto modelConfigIdentifier = "_model";
    static constexpr auto datasetConfigIdentifier = "_dataset";
    static constexpr auto scheduleConfigIdentifier = "_schedule";
    static constexpr auto runtimeConfigIdentifier = "_runtime";
    static constexpr auto mainConfigIdentifier = "_main";
    QString baseModelPath;
    QString checkpointFileName;
    if (!pluginSettings->getMMClassificationPath().trimmed().isEmpty()
            && m_baseModelsMap.contains(baseModelName)
            && !m_models.contains(modelName % "/" % m_modelNameKey)) {
        auto baseModel = m_baseModelsMap[baseModelName];
        baseModelPath = m_baseModelsMap[baseModelName]->getRelConfigFilePath();
        checkpointFileName = baseModel->getCheckpointFileName();
    } else return false;

    QString modelConfigPath = m_configFileBuilder.createModelConfigFile(
            modelName % modelConfigIdentifier, baseModelPath);
    QString datasetConfigPath = m_configFileBuilder.createDatasetConfigFile(
            modelName % datasetConfigIdentifier);
    QString scheduleConfigPath = m_configFileBuilder.createScheduleConfigFile(
            modelName % scheduleConfigIdentifier);
    QString defaultRuntimePath = m_configFileBuilder.createRuntimeConfigFile(
            modelName % runtimeConfigIdentifier);
    QString checkpointFilePath =
            pluginSettings->getMMClassificationPath()
            % "/" % m_subfolder_checkpoints
            % "/" % checkpointFileName;

    QString absoluteCheckpointFilePath = QFileInfo(checkpointFilePath).absoluteFilePath();

    QString mainConfigPath = m_configFileBuilder.createMainConfigFile(
            modelName % mainConfigIdentifier, modelConfigPath, datasetConfigPath,
            scheduleConfigPath, defaultRuntimePath, absoluteCheckpointFilePath);
    Model newModel(modelName, baseModelName, mainConfigPath, modelConfigPath,
                   datasetConfigPath, scheduleConfigPath, defaultRuntimePath);
    saveModel(newModel);

    return true;
}

bool MMClassificationPlugin::removeModel(QString modelName) {
    Model existingModel = loadModel(modelName);
    if (pluginSettings->getMMClassificationPath().trimmed().isEmpty() || !existingModel.isValid()) return false;
    QString mainConfigPath = existingModel.getMainConfigPath();
    QString modelConfigPath = existingModel.getModelConfigPath();
    QString datasetConfigPath = existingModel.getDatasetConfigPath();
    QString scheduleConfigPath = existingModel.getScheduleConfigPath();
    QFile::remove(mainConfigPath);
    QFile::remove(modelConfigPath);
    QFile::remove(datasetConfigPath);
    QFile::remove(scheduleConfigPath);

    QString runtimeConfigPath = existingModel.getRuntimeConfigPath();
    if (!runtimeConfigPath.endsWith(m_configFileBuilder.getDefaultRuntimeConfigFilePath())) {
        QFile::remove(runtimeConfigPath);
    }

    m_models.beginGroup(modelName);
    m_models.remove(""); //removes the group and all it keys
    m_models.endGroup();

    return true;

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
    for (const QString &dirFile: targetDir.entryList(QDir::Files)) {
        targetDir.remove(dirFile);
    }

    // find all subdirectories to distribute evenly between the different classes
    const QString &rootDir = inputPath;
    QStringList subdirectories = QDir(rootDir).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    int totalPictures = 0;
    QMap<QString, int> numberPerSubdirectory;
    QStringList validExtensions = {"jpg", "JPG", "png", "PNG"};
    int count;
    for (const auto &subdirectory: subdirectories) {
        QDir dir(subdirectory);
        count = 0;
        for (const QFileInfo &file: dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
            if (file.exists() && file.isFile() && validExtensions.contains(file.suffix()))
                count++;
        }
        numberPerSubdirectory[dir.path()] = count;
        totalPictures += count;
    }

    int remainingTotalAmount = amount;
    QMap<QString, int> distribution = {};
    QMap<QString, int> remainingAmountPerSubdirectory = {};
    if (amount >= totalPictures) {
        // If there are not enough picture, it will get all pictures
        // The same is the case if we only have so many pictures in total
        distribution = numberPerSubdirectory;
    } else {
        remainingAmountPerSubdirectory.insert(numberPerSubdirectory);

        while (remainingTotalAmount > 0) {
            for (const auto &[key, remaining]: MapAdapt(remainingAmountPerSubdirectory)) {
                amount = 0;
                if (amount < remaining) {
                    distribution[key] = ++amount;
                    remainingTotalAmount--;
                } else remainingAmountPerSubdirectory.remove(key);

                if (remainingTotalAmount == 0) break;
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
    auto command = pluginSettings->getPythonPath();
    MMClassificationConfigFileBuilder::changeDataAugmentationOptions(datasetConfigPath, albuTransformType,
                                                                     randomResizedCropSize, randomFlipProb,
                                                                     randomFlipDirection, randomErasing, resize,
                                                                     centerCropSize);

    QFileInfo pythonfile = QFileInfo("mmclassification_preview_pipeline.py");
    QString scriptPath = pythonfile.absoluteFilePath();

    QStringList fullCommands = {};

    for (const auto &[sourceDirectoryPath, partAmount]: MapAdapt(distribution)) {
        fullCommands.append(command % " " % scriptPath % " " % datasetConfigPath % " " % sourceDirectoryPath % " " %
                            targetAbsolutePath % " " % QString::number(partAmount));
    }

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QString pathValue = env.value("PATH");

    if (!pluginSettings->getMMClsPath().isEmpty())
        pathValue.prepend(pluginSettings->getMMClsPath() % ":");
    if (!pluginSettings->getPythonPath().isEmpty())
        pathValue.prepend(pluginSettings->getPythonPath() % ":");
    env.insert("PATH", pathValue);

    for (const QString &fullCommand: fullCommands) {
        QProcess process;
        process.setProcessEnvironment(env);
        process.startCommand(fullCommand);
        process.waitForFinished();
        qDebug() << qPrintable(process.readAllStandardOutput().simplified());
        process.close();
    }
    return true;
}

QSharedPointer<TrainingResult>
MMClassificationPlugin::train(const QString &modelName, QString trainDatasetPath, QString validationDatasetPath,
                              QString workingDirectoryPath, ProgressablePlugin *receiver) {
    m_receiver = receiver;

    // get labels to calculate number of classes
    auto modelConfigPath = loadModel(modelName).getModelConfigPath();
    auto labels = getLabels(trainDatasetPath);
    auto mainConfigPath = loadModel(modelName).getMainConfigPath();

    if (!checkTrainMethodInput(labels,
                               {mainConfigPath, trainDatasetPath, validationDatasetPath, workingDirectoryPath})) {
        qWarning() << "Invalid input parameters, empty TrainingResult object will be returned";
        return QSharedPointer<TrainingResult>(new TrainingResult({}, {}, {}, {}, {}, {}, {}));
    }

    m_configFileBuilder.changeModelNumberOfClasses(modelConfigPath, labels.size());

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
    m_configFileBuilder.changeDatasetPaths(datasetConfigPath, trainDatasetPath, validationDatasetPath,
                                           validationDatasetPath);

    QString scheduleConfigPath = loadModel(modelName).getScheduleConfigPath();
    m_maxIters = inputOptions->getMaxIters();
    m_configFileBuilder.changeScheduleOptions(scheduleConfigPath, m_maxIters);

    // copy and change runtime config if checkpoint creation and max_iters does not fit
    QString runtimeConfigPath = loadModel(modelName).getRuntimeConfigPath();
    adjustCheckpointCreation(runtimeConfigPath, m_maxIters);

    int cudaDeviceNumber = inputOptions->getCudaDevice();

    QString command = pluginSettings->getPythonPath();
    auto pythonTrainFile = QFileInfo("mmclassification_train.py");
    auto trainScriptPath = pythonTrainFile.absoluteFilePath();
    const auto workDirConsoleArgument = "--work-dir";

    QStringList fullTrainCommand = {command, trainScriptPath, mainConfigPath, workDirConsoleArgument,
                                    workingDirectoryPath};
    auto env = QProcessEnvironment::systemEnvironment();
    env.insert("CUDA_VISIBLE_DEVICES", QString::number(cudaDeviceNumber));

    m_workDir = workingDirectoryPath;
    m_watcher->addPath(m_workDir);
    connect(&*m_watcher, &QFileSystemWatcher::directoryChanged, this, &MMClassificationPlugin::slot_checkForLogFile);
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
    auto entries = workingDir.entryList(QDir::Files);
    QString logFileName = (entries.isEmpty()) ? "" : entries.last();
    QString absoluteLogFilePath = workingDir.absoluteFilePath(logFileName);

    auto accuracyCurveData = m_jsonReader.getAccuracyCurve(absoluteLogFilePath);

    QDir validationDatasetDirectory(validationDatasetPath);
    auto validationAnnotationFilePath = validationDatasetDirectory.absoluteFilePath(m_annotationFileName);

    auto mostMisclassifiedImages =
            m_jsonReader.generateMostMissclassifiedImages(m_numberOfMissClassifiedImages,
                                                          validationAnnotationFilePath,
                                                          pathToWithoutMetricResultFile);

    return QSharedPointer<TrainingResult>(new TrainingResult(workingDirectoryPath, accuracyCurveData, labels, confusionMatrixData,
                              mostMisclassifiedImages, top1, top5));
}

QSharedPointer<ClassificationResult>
MMClassificationPlugin::classify(const QString &inputImageDirPath, const QString &trainDatasetPath,
                                 const QString &workingDirPath,
                                 const QString &modelName, ProgressablePlugin *receiver) {
    m_receiver = receiver;
    QDir workingDir(workingDirPath);

    static constexpr auto checkpointName = "latest.pth";
    static constexpr auto outputConfidenceScoreConsoleArgumentName = "--confidenceScoresOut";
    static constexpr auto outputConfidenceScoreResultName = "resultConfidenceScore.json";

    const QString pathToConfidenceScoreResultFile = workingDir.absoluteFilePath(outputConfidenceScoreResultName);
    const QString checkpointPath = workingDir.absoluteFilePath(checkpointName);

    QString mainConfigPath = loadModel(modelName).getMainConfigPath();
    // get train dataset path from dataset config file to extract the labels
    QString datasetConfigPath = loadModel(modelName).getDatasetConfigPath();

    m_configFileBuilder.changeTestPath(datasetConfigPath, inputImageDirPath);
    QFileInfo checkpointInfo(checkpointPath);

    if (mainConfigPath.isEmpty() || !checkpointInfo.exists()) {
        qWarning() << "mainConfigFile or checkpointFile does not exist";
        return QSharedPointer<ClassificationResult>(new ClassificationResult({}, {}, {}));
    }

    auto command = pluginSettings->getPythonPath();
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

    QDir inputDirectory(inputImageDirPath);
    QString pathToValTxt = inputDirectory.absoluteFilePath(m_annotationFileName);
    QPair<QVector<QString>, QVector<int>> annotationFileData = m_jsonReader.readAnnotationFile(pathToValTxt);
    inputImageFilePaths = annotationFileData.first;

    QMap<QString, QList<double>> data;
    QList<QString> labels = getLabels(trainDatasetPath);
    QStringList additionalMetrics;

    if (!inputImageFilePaths.isEmpty()) {
        data = m_jsonReader.readConfidenceScores(pathToConfidenceScoreResultFile, inputImageFilePaths);
        qDebug() << "content: " << data;
    }
    return QSharedPointer<ClassificationResult>(new ClassificationResult(workingDirPath, data, labels, additionalMetrics));
}

QSharedPointer<QWidget> MMClassificationPlugin::getDataAugmentationInputWidget() {
    return dataAugmentationInput;
}

QSharedPointer<QIcon> MMClassificationPlugin::getPluginIcon() {
    return QSharedPointer<QIcon>(new QIcon(PLUGIN_ICON));
}

void MMClassificationPlugin::slot_readClassifyOutput() {
    // Regex for proportion
    static QRegularExpression regularExpression("[0-9]+/[0-9]+");
    QString line = QString::fromLocal8Bit(m_process->readLine());

    QRegularExpressionMatch match = regularExpression.match(line);
    if (match.hasMatch()) {
        QString lastCapturedProportion = match.captured(match.lastCapturedIndex());
        QStringList pieces = lastCapturedProportion.split("/");
        int progress = qCeil((pieces[0].toInt() * 100) / pieces[1].toInt());
        m_receiver->slot_makeProgress(progress);
    }
}

void MMClassificationPlugin::slot_checkForLogFile(const QString & /*path*/) {
    QDir directory(m_workDir);
    QStringList logFiles = directory.entryList(QStringList() << "*.log.json", QDir::Files);
    if (logFiles.isEmpty()) return;

    for (const QString &filename: logFiles) {
        // disconnect due to found log file and monitor file directly
        QObject::disconnect(&*m_watcher, &QFileSystemWatcher::directoryChanged, this,
                            &MMClassificationPlugin::slot_checkForLogFile);
        const QString logFilePath = m_workDir % "/" % filename;
        connectFileWatcher(logFilePath);
    }
}

void MMClassificationPlugin::slot_readChangeInLogFile(const QString &path) {
    static constexpr auto modeForProgress = "train";

    QFileInfo jsonLogFile = QFileInfo(path);
    QFile inFile(jsonLogFile.absoluteFilePath());
    QStringList data;

    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&inFile);

    for (QString line = in.readLine(); !line.isNull() && !line.isEmpty(); line = in.readLine()) {
        data.append(line);
    }
    inFile.close();

    if (data.size() <= 1) return;

    int offset = 1;
    QJsonParseError errorPtr;
    while (data[data.size() - offset].isEmpty()) offset++;

    auto doc = QJsonDocument::fromJson(data[data.size() - offset].toUtf8(), &errorPtr);
    if (doc.isNull()) qWarning() << "Parse failed";

    QJsonObject rootObj = doc.object();
    if (rootObj.contains("iter") && rootObj.contains("mode")) {
        QString mode = rootObj.value("mode").toString();
        if (mode.compare(modeForProgress) != 0) return;

        int iter = rootObj.value("iter").toInt();
        int progress = qCeil((iter * 100) / m_maxIters);
        m_receiver->slot_makeProgress(progress);
    }
}

void MMClassificationPlugin::connectFileWatcher(const QString &path) {
    m_watcher->removePath(m_workDir);
    m_watcher->addPath(path);
    QObject::connect(&*m_watcher, &QFileSystemWatcher::fileChanged, this,
                     &MMClassificationPlugin::slot_readChangeInLogFile);
}
