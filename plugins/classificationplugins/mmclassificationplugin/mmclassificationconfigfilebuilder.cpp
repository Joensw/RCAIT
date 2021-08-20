#include "mmclassificationconfigfilebuilder.h"

MMClassificationConfigFileBuilder::MMClassificationConfigFileBuilder()
{

}

void MMClassificationConfigFileBuilder::setPathToMMClassification(QString pathToMMClassification)
{
    m_pathToMMClassification = pathToMMClassification;
}

QString MMClassificationConfigFileBuilder::createDatasetFileForDataAugmentationPreviewConfigFile()
{
    QFileInfo infoMMClassification(m_pathToMMClassification);
    QString osIndependendPathToMMClassification = infoMMClassification.absoluteFilePath();
    QDir mmclassificationDirectory(osIndependendPathToMMClassification);
    QString baseDatasetConfigPath = mmclassificationDirectory.cleanPath(mmclassificationDirectory.absoluteFilePath(m_defaultDatasetConfigPath));
    QFile baseDatasetConfigFile(baseDatasetConfigPath);
    if (!baseDatasetConfigFile.exists()) {
        return QString();
    }
    QString previewConfigPath = mmclassificationDirectory.cleanPath(mmclassificationDirectory.absoluteFilePath(m_previewConfigPath));
    QFile previewConfigFile(previewConfigPath);
    if (!previewConfigFile.exists()) {
        baseDatasetConfigFile.copy(previewConfigPath);
    }
    return previewConfigPath;
}

QString MMClassificationConfigFileBuilder::createMainConfigFile(QString name, QString modelConfigPath, QString datasetConfigPath, QString scheduleConfigPath, QString runtimeConfigPath, QString checkpointName)
{
    QFileInfo infoMMClassification(m_pathToMMClassification);
    QString osIndependendPathToMMClassification = infoMMClassification.absoluteFilePath();
    QDir mmclassificationDirectory(osIndependendPathToMMClassification);
    QString mainConfigPath = mmclassificationDirectory.cleanPath(mmclassificationDirectory.absoluteFilePath(m_subFolderConfigs));
    //QString checkpointPath = mmclassificationDirectory.cleanPath(mmclassificationDirectory.absoluteFilePath(m_subfolderCheckpoints));
    QString checkpointPath = mmclassificationDirectory.absolutePath();
    // Create the directory if needed
    if (!mmclassificationDirectory.exists(mainConfigPath)) {
        mmclassificationDirectory.mkpath(mainConfigPath);
    }
    mainConfigPath += QDir::fromNativeSeparators(QDir::separator()) + name + ".py";
    QFile mainConfigFile(mainConfigPath);
    QDir mainConfigDir(mainConfigPath);
    mainConfigDir.cdUp();
    mainConfigFile.open(QIODevice::WriteOnly);
    QTextStream out(&mainConfigFile);
        out << "_base_ = [" << "\n";
        out << "'" << mainConfigDir.relativeFilePath(modelConfigPath) << "'" << ',';
        out << "'" << mainConfigDir.relativeFilePath(datasetConfigPath) << "'" << ',';
        out << "'" << mainConfigDir.relativeFilePath(scheduleConfigPath) << "'" << ',';
        out << "'" << mainConfigDir.relativeFilePath(runtimeConfigPath) << "'" << "\n";
        out << "]" << "\n";
        //out << "load_from = " << "'" + mainConfigDir.relativeFilePath(checkpointPath + checkpointName) + "'";
        out << "load_from = " << "'" + checkpointName + "'";
    mainConfigFile.close();
    return mainConfigPath;
}

QString MMClassificationConfigFileBuilder::createModelConfigFile(QString name, QString baseModelPath)
{
    QString modelConfigPath = createConfigFile(name, m_defaultModelConfigPath);
    if (!modelConfigPath.isEmpty()) {
        QFile modelConfigFile(modelConfigPath);
        modelConfigFile.open(QIODevice::Text | QIODevice::ReadOnly);
        QStringList data;
        QTextStream in(&modelConfigFile);
        QString line = in.readLine();
        if (!line.isNull()) {
            line = "_base_ = ['./" + baseModelPath + "']";
            data.append(line);
        }
        while (!line.isNull()) {
            line = in.readLine();
            data.append(line);
        }
        modelConfigFile.close();
        if(modelConfigFile.open(QFile::WriteOnly | QFile::Truncate)) {
            QTextStream out(&modelConfigFile);
            for (int i = 0; i < data.size(); i++) {
                out << data.at(i) + "\n";
            }
        }
        modelConfigFile.close();
    }
    return modelConfigPath;
}

QString MMClassificationConfigFileBuilder::createDatasetConfigFile(QString name)
{
    return createConfigFile(name, m_defaultDatasetConfigPath);
}

QString MMClassificationConfigFileBuilder::createScheduleConfigFile(QString name)
{
    return createConfigFile(name, m_defaultScheduleConfigPath);
}

QString MMClassificationConfigFileBuilder::createRuntimeConfigFile(QString name)
{
    return createConfigFile(name, m_defaultRuntimeConfigPath);
}

QString MMClassificationConfigFileBuilder::getDefaultRuntimeConfigFilePath()
{
    QFileInfo infoMMClassification(m_pathToMMClassification);
    QString osIndependendPathToMMClassification = infoMMClassification.absoluteFilePath();
    QDir mmclassificationDirectory(osIndependendPathToMMClassification);
    return mmclassificationDirectory.cleanPath(mmclassificationDirectory.absoluteFilePath(m_defaultRuntimeConfigPath));
}

QString MMClassificationConfigFileBuilder::createConfigFile(QString name, QString defaultFilePath)
{
    QFileInfo infoMMClassification(m_pathToMMClassification);
    QString osIndependendPathToMMClassification = infoMMClassification.absoluteFilePath();
    QDir mmclassificationDirectory(osIndependendPathToMMClassification);
    QString defaultConfigPath = mmclassificationDirectory.cleanPath(mmclassificationDirectory.absoluteFilePath(defaultFilePath));
    QFile defaultConfigFile(defaultConfigPath);
    if (!defaultConfigFile.exists()) {
        return QString();
    }
    QFileInfo info (defaultConfigPath);
    QString newConfigPath = info.absolutePath() + QDir::fromNativeSeparators(QDir::separator()) + name + ".py";;
    defaultConfigFile.copy(newConfigPath);
    return newConfigPath;
}

void MMClassificationConfigFileBuilder::changeRuntimeConfigPathInMainConfig(QString mainConfigPath, QString newRuntimeConfigPath)
{
    const int captureGroupIndex = 1;
    QFile file(mainConfigPath);
    file.open(QIODevice::Text | QIODevice::ReadOnly);
    QString mainConfigContent = file.readAll();

    QDir mainConfigDir(mainConfigPath);
    mainConfigDir.cdUp();
    QString relativeRuntimeConfigPath = mainConfigDir.relativeFilePath(newRuntimeConfigPath);

    mainConfigContent = replaceText(mainConfigContent, m_runtimeConfigPathRegExText, captureGroupIndex, relativeRuntimeConfigPath);
    QStringList list = mainConfigContent.split(QRegularExpression("[\r\n]"));
    writeBack(mainConfigPath, list);
}

void MMClassificationConfigFileBuilder::changeCheckpointFilePath(QString mainConfigPath, QString checkpointFilePath)
{
    const QString expression = "load_from = '(\\S+)'";

    QVector<QString> toReplace;
    toReplace.append(expression);

    QVector<QString> replaceWith;
    replaceWith.append(checkpointFilePath);

    readAndReplaceLinesInOrder(mainConfigPath, toReplace, replaceWith, 1);
}

void MMClassificationConfigFileBuilder::changeModelNumberOfClasses(QString modelConfigPath, int numberOfClasses)
{
    const QString expression = "num_classes = (\\d+)";

    QFile file(modelConfigPath);
    file.open(QIODevice::Text | QIODevice::ReadOnly);
    QString modelConfigPathContent = file.readAll();
    modelConfigPathContent = replaceText(modelConfigPathContent, expression, 1, QString::number(numberOfClasses));

    QStringList list = modelConfigPathContent.split(QRegularExpression(m_newLineRegExText));
    writeBack(modelConfigPath, list);
}

void MMClassificationConfigFileBuilder::changeDataAugmentationOptions(QString datasetConfigPath, QString albuTransform, int randomResizedCropSize, double randomFlipProb, QString randomFlipDirection, bool randomErasing, int resize, int centerCropSize)
{
    const QString albuTransformPlaceholder = "#no albu transform type specified";
    const QString randomResizedCropPlaceholder = "#no random resized crop specified";
    const QString randomFlipPlaceholder = "#no random flip specified";
    const QString randomErasingPlaceholder = "#no random erasing specified";
    const QString albuTransformPipelinePlaceholder = "#no albu transform pipeline options specified";
    const QString resizePlaceholder = "#no resize specified";
    const QString centerCropPlaceholder = "#no center crop specified";

    // to identify the appropriate type in the config
    const QString albuTransformIdentifier = "albu_transforms = [";
    const QString randomResizedIdentifier = "RandomResizedCrop";
    const QString randomFlipIdentifier = "RandomFlip";
    const QString randomErasingIdentifier = "RandomErasing";
    const QString resizeIdentifier = "Resize";
    const QString centerCropIdentifier = "CenterCrop";

    const QString albuTransformCompleteRegExText = "(albu_transforms = \\[.+\\])";
    const QString albuTransformGroupValueRegExText = "albu_transforms = \\[.+type='(.+)'";
    const QString albuTransformBeforeValue = "albu_transforms = [dict(type='";
    const QString albuTransformAfterValue = "')]";

    const QString randomResizedCropSizeCompleteRegExText = "(dict\\(type='RandomResizedCrop'.+\\),)";
    const QString randomResizedCropSizeGroupValueRegExText = "dict\\(type='RandomResizedCrop'.*size=([0-9][0-9]*)";
    const QString randomResizedCropSizeBeforeValue = "dict(type='RandomResizedCrop', scale=(0.8, 1.0), size=";
    const QString randomResizedCropSizeAfterValue = "),";

    const QString randomFlipCompleteRegExText = "(dict\\(type='RandomFlip'.+\\),)";
    const QString randomFlipProbGroupValueRegExText = "flip_prob=(\\d+.\\d+)";
    const QString randomFlipDirectionGroupValueRegExText = "direction='(\\w+)'";
    const QString randomFlipProbBeforeValue = "dict(type='RandomFlip', flip_prob=";
    const QString randomFlipDirectionBeforeValue = ", direction='";
    const QString randomFlipDirectionAfterValue = "'),";

    const QString randomErasingCompleteRegExText = "(dict\\(type='RandomErasing'.*\\),)";
    const QString randomErasingLine = "dict(type='RandomErasing'),";

    const QString albuTransformCompleteLineRegExText = "(dict\\(type='Albu', transforms=albu_transforms\\),)";
    const QString albuTransformCompleteLine = "dict(type='Albu', transforms=albu_transforms),";

    const QString resizeCompleteRegExText = "(dict\\(type='Resize'.*\\),)";
    const QString resizeGroupValueRegExText = "dict\\(type='Resize'.*size=\\(([0-9][0-9]*)";
    const QString resizeBeforeValue = "dict(type='Resize', size=(";
    const QString resizeAfterValue = ", -1)),";

    const QString centerCropSizeCompleteRegExText = "(dict\\(type='CenterCrop'.*\\),)";
    const QString centerCropSizeGroupValueRegExText = "dict\\(type='CenterCrop'.*crop_size=([0-9][0-9]*)";
    const QString centerCropSizeBeforeValue = "dict(type='CenterCrop', crop_size=";
    const QString centerCropSizeAfterValue = "),";

    const int groupIndex = 1;
    QVector<QString> toReplace;
    QVector<QString> replaceWith;
    QStringList datasetConfigContent = readFileLines(datasetConfigPath);

    // indicates whether the specified setting already exists in the configuration file or not
    bool containsAlbuTransformType = false;
    bool containsRandomResizedCrop = false;
    bool containsRandomFlip = false; // flip probability and flip direction belong together
    bool containsRandomErasing = false;
    bool containsResize = false;
    bool containsCenterCropSize = false;

    QString line;
    for (int i = 0; i < datasetConfigContent.size(); i++) {
        line = datasetConfigContent.at(i);
        if (line.contains(albuTransformIdentifier)) {
            containsAlbuTransformType = true;
        } else if (line.contains(randomResizedIdentifier)) {
            containsRandomResizedCrop = true;
        } else if (line.contains(randomFlipIdentifier)) {
            containsRandomFlip = true;
        } else if (line.contains(randomErasingIdentifier)) {
            containsRandomErasing = true;
        } else if (line.contains(resizeIdentifier)) {
            containsResize = true;
        } else if (line.contains(centerCropIdentifier)) {
            containsCenterCropSize = true;
        }
    }

    if (albuTransform.isEmpty() && containsAlbuTransformType) {
        toReplace.append(albuTransformCompleteRegExText);
        replaceWith.append(albuTransformPlaceholder);
    } else if (!albuTransform.isEmpty()) {
        if (containsAlbuTransformType) {
            toReplace.append(albuTransformGroupValueRegExText);
            replaceWith.append(albuTransform);
        } else {
            toReplace.append("(" + albuTransformPlaceholder + ")");
            replaceWith.append(albuTransformBeforeValue + albuTransform + albuTransformAfterValue);
        }
    }

    if (randomResizedCropSize == 0 && containsRandomResizedCrop) {
        toReplace.append(randomResizedCropSizeCompleteRegExText);
        replaceWith.append(randomResizedCropPlaceholder);
    } else if (randomResizedCropSize != 0){
        if (containsRandomResizedCrop) {
            toReplace.append(randomResizedCropSizeGroupValueRegExText);
            replaceWith.append(QString::number(randomResizedCropSize));
        } else {
            toReplace.append("(" + randomResizedCropPlaceholder + ")");
            replaceWith.append(randomResizedCropSizeBeforeValue + QString::number(randomResizedCropSize) + randomResizedCropSizeAfterValue);
        }
    }

    if ((randomFlipProb == 0 || randomFlipDirection.isEmpty()) && containsRandomFlip) {
        toReplace.append(randomFlipCompleteRegExText);
        replaceWith.append(randomFlipPlaceholder);
    } else if (randomFlipProb != 0 && !randomFlipDirection.isEmpty()){
        if (containsRandomFlip) {
            toReplace.append(randomFlipProbGroupValueRegExText);
            toReplace.append(randomFlipDirectionGroupValueRegExText);
            replaceWith.append(QString::number(randomFlipProb));
            replaceWith.append(randomFlipDirection);
        } else {
            toReplace.append("(" + randomFlipPlaceholder + ")");
            replaceWith.append(randomFlipProbBeforeValue + QString::number(randomFlipProb) + randomFlipDirectionBeforeValue + randomFlipDirection + randomFlipDirectionAfterValue);
        }
    }

    if (!randomErasing && containsRandomErasing) {
        toReplace.append(randomErasingCompleteRegExText);
        replaceWith.append(randomErasingPlaceholder);
    } else if (randomErasing && !containsRandomErasing){
        toReplace.append("(" + randomErasingPlaceholder + ")");
        replaceWith.append(randomErasingLine);
    }

    if (albuTransform.isEmpty() && containsAlbuTransformType) {
        toReplace.append(albuTransformCompleteLineRegExText);
        replaceWith.append(albuTransformPipelinePlaceholder);
    } else if (!albuTransform.isEmpty() && !containsAlbuTransformType) {
        toReplace.append("(" + albuTransformPipelinePlaceholder + ")");
        replaceWith.append(albuTransformCompleteLine);
    }

    if (resize == 0 && containsResize) {
        toReplace.append(resizeCompleteRegExText);
        replaceWith.append(resizePlaceholder);
    } else if (resize != 0){
        if (containsResize) {
            toReplace.append(resizeGroupValueRegExText);
            replaceWith.append(QString::number(resize));
        } else {
            toReplace.append("(" + resizePlaceholder + ")");
            replaceWith.append(resizeBeforeValue + QString::number(resize) + resizeAfterValue);
        }
    }

    if (centerCropSize == 0 && containsCenterCropSize) {
        toReplace.append(centerCropSizeCompleteRegExText);
        replaceWith.append(centerCropPlaceholder);
    } else if (!albuTransform.isEmpty()){
        if (containsCenterCropSize) {
            toReplace.append(centerCropSizeGroupValueRegExText);
            replaceWith.append(QString::number(centerCropSize));
        } else {
            toReplace.append("(" + centerCropPlaceholder + ")");
            replaceWith.append(centerCropSizeBeforeValue + QString::number(centerCropSize) + centerCropSizeAfterValue);
        }
    }
    readAndReplaceLinesInOrder(datasetConfigPath, toReplace, replaceWith, groupIndex);
}

void MMClassificationConfigFileBuilder::changeDatasetPaths(QString datasetConfigPath, QString trainingSetPath, QString validationSetPath, QString testSetPath)
{
    int groupIndex = 3;
    QFile file(datasetConfigPath);
    file.open(QIODevice::Text | QIODevice::ReadOnly);
    QString datasetConfigContent = file.readAll();
    datasetConfigContent = replaceText(datasetConfigContent, m_trainPathRegExText, groupIndex, trainingSetPath);
    datasetConfigContent = replaceText(datasetConfigContent, m_validationPathRegExText, groupIndex, validationSetPath);
    datasetConfigContent = replaceText(datasetConfigContent, m_testPathRegExText, groupIndex, testSetPath);
    QStringList list = datasetConfigContent.split(QRegularExpression(m_newLineRegExText)); // inverse transformation, so that it isn't in only one line
    writeBack(datasetConfigPath, list);
}

void MMClassificationConfigFileBuilder::changeTestPath(QString datasetConfigPath, QString testSetPath)
{
    const int testPathGroupIndex = 3;
    QFile file(datasetConfigPath);
    file.open(QIODevice::Text | QIODevice::ReadOnly);
    QString datasetConfigContent = file.readAll();
    datasetConfigContent = replaceText(datasetConfigContent, m_testPathRegExText, testPathGroupIndex, testSetPath);
    QStringList list = datasetConfigContent.split(QRegularExpression(m_newLineRegExText));
    writeBack(datasetConfigPath, list);
}

void MMClassificationConfigFileBuilder::changeScheduleOptions(QString scheduleConfigPath, int maxIterations)
{
    const int split = 2;
    const int maxItersGroupIndex = 0;
    const int stepGroupIndex = 1;
    const QString maxItersExpression = "max_iters=";
    int step = maxIterations / split; // the step depends on the maximum numbers of iterations

    QFile file(scheduleConfigPath);
    file.open(QIODevice::Text | QIODevice::ReadOnly);
    QString scheduleConfigContent = file.readAll();
    scheduleConfigContent = replaceText(scheduleConfigContent, m_step, stepGroupIndex, QString::number(step));
    scheduleConfigContent = replaceText(scheduleConfigContent, m_maxItersRegExText, maxItersGroupIndex, maxItersExpression + QString::number(maxIterations));

    qDebug() << "step: " << step;

    QStringList list = scheduleConfigContent.split(QRegularExpression(m_newLineRegExText));
    writeBack(scheduleConfigPath, list);
}

void MMClassificationConfigFileBuilder::changeCheckpointCreationStep(QString runtimeConfigPath, int step)
{
    const int groupIndex = 1;
    QFile file(runtimeConfigPath);
    file.open(QIODevice::Text | QIODevice::ReadOnly);
    QString runtimeConfigContent = file.readAll();
    runtimeConfigContent = replaceText(runtimeConfigContent, m_checkpointInterval, groupIndex, QString::number(step));
    QStringList list = runtimeConfigContent.split(QRegularExpression(m_newLineRegExText));
    writeBack(runtimeConfigPath, list);
}

QString MMClassificationConfigFileBuilder::replaceText(QString content, QString regularExpressionText, int captureGroupIndex, QString replacementText) {
    QString textToReplace;
    QRegularExpression regularExpresion(regularExpressionText);
    QRegularExpressionMatch match;
    match = regularExpresion.match(content);
    if (match.hasMatch()) {
        textToReplace = match.captured(captureGroupIndex);
        regularExpresion.setPattern(textToReplace);
        content.replace(regularExpresion, replacementText);
     }
    return content;
}

QStringList MMClassificationConfigFileBuilder::readFileLines(QString pathToFile) {
    QFile file(pathToFile);
    file.open(QIODevice::Text | QIODevice::ReadOnly);
    QStringList data;
    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
        line = in.readLine();
        data.append(line);
    }
    file.close();
    return data;
}

bool MMClassificationConfigFileBuilder::readAndReplaceLinesInOrder(QString pathToFile, QVector<QString> regularExpression, QVector<QString> replaceWith, int caputureGroupIndex) {
    QFile file(pathToFile);
    file.open(QIODevice::Text | QIODevice::ReadOnly);
    QStringList data;
    QTextStream in(&file);
    int countReplaces = 0;
    int regularExpressionSize = regularExpression.size();
    int replaceWithSize = replaceWith.size();
    if (regularExpressionSize == 0 or replaceWithSize == 0 or regularExpressionSize != replaceWithSize) {
        return false;
    }
    QRegularExpression re(regularExpression[countReplaces]);
    QString replacementText(replaceWith[countReplaces]);
    QString toReplace;
    bool allReplaced = false;
    QRegularExpressionMatch match;
    QString line = in.readLine();
    while (!line.isNull()) {
        match = re.match(line);
        if (!allReplaced && match.hasMatch()) {
            toReplace = match.captured(caputureGroupIndex);
            QRegularExpression valueToReplace(toReplace);
            if(!valueToReplace.isValid())
            line.replace(toReplace, replaceWith[countReplaces]);
            QRegularExpressionMatch match2 = valueToReplace.match(line);
            countReplaces++;
            if (countReplaces == regularExpressionSize) {
                allReplaced = true;
                data.append(line);
                line = in.readLine();
            } else {
                re.setPattern(regularExpression[countReplaces]);
            }
        } else {
            data.append(line);
            line = in.readLine();
        }
    }
    file.close();
    writeBack(pathToFile, data);
    return countReplaces == regularExpressionSize;
}

void MMClassificationConfigFileBuilder::writeBack(QString pathToFile, QStringList data) {
    QFile file(pathToFile);
    if(file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&file);
        for (int i = 0; i < data.size(); i++) {
            out << data.at(i) + "\n";
        }
    }
    file.close();
}
