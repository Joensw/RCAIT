#include "resultsimporter.h"

ResultsImporter::ResultsImporter()
        : m_projectManager(&ProjectManager::getInstance()) {

}

void ResultsImporter::updateResultFolderPaths() {
    m_trainingResultsDir = m_projectManager->getTrainingResultsDir();
    m_classificationResultsDir = m_projectManager->getClassificationResultsDir();
    m_workingDir = m_projectManager->getProjectImageTempDir();
}

QString ResultsImporter::getResultDataPath(const QString &resultNameTemplate, const QString &baseDir,
                                           const QString &identifier) {

    auto folderIdentifier = Result::savableRepresentation(identifier);
    auto fullName = resultNameTemplate.arg(folderIdentifier);
    auto dir = QDir(baseDir);

    if (!dir.cd(folderIdentifier))
        qWarning() << "Error finding result dir " << folderIdentifier;
    if (!dir.exists(fullName))
        qWarning() << "Error finding target file " << fullName;

    return dir.absoluteFilePath(fullName);
}

/**
 * Top Accuracies slots
 */
void ResultsImporter::slot_comparison_loadAccuracyData(TopAccuraciesView *view,
                                                       const QPointer<TopAccuraciesGraphics> &graphics,
                                                       const QString &runNameToCompare) const {
    Q_ASSERT(graphics);
    Q_ASSERT(view);

    auto filepath = getResultDataPath(TRAINING_JSON, m_trainingResultsDir, runNameToCompare);
    auto jsonObject = JSON_Toolbox::readJSONFromFile(filepath);

    auto top1 = jsonObject["top1"].toDouble();
    auto top5 = jsonObject["top5"].toDouble();

    graphics->addDataRow(runNameToCompare, {top1, top5});
    view->addTopAccuraciesEntry(runNameToCompare, top1, top5);
}

void ResultsImporter::slot_comparison_unloadAccuracyData(TopAccuraciesView *view,
                                                         const QPointer<TopAccuraciesGraphics> &graphics,
                                                         const QString &runNameToCompare) {
    Q_ASSERT(graphics);
    Q_ASSERT(view);

    graphics->removeDataRow(runNameToCompare);
    view->removeTopAccuraciesEntry(runNameToCompare);
}

/**
 * Classification result slots
 */
void ResultsImporter::slot_comparison_loadClassificationResultData(ClassificationResultView *view,
                                                                   const QString &runNameToCompare) const {
    Q_ASSERT(view);
    view->setSaved(true);

    auto filepath = getResultDataPath(CLASSIFICATION_JSON, m_classificationResultsDir, runNameToCompare);
    auto jsonObject = JSON_Toolbox::readJSONFromFile(filepath);

    auto json_classification_data = jsonObject["classification_data"].toArray();
    auto json_labels = jsonObject["labels"].toArray();
    auto json_additionalResults = jsonObject["additionalResults"].toArray();

    QMap<QString, QList<double>> classification_data;
    for (const auto &value: json_classification_data) {
        auto obj = value.toObject();
        auto imagePath = obj["image_path"].toString();
        auto json_list = obj["confidence"].toArray();

        auto list = QJsonArray_toList<double>(json_list);
        classification_data[imagePath] = list;
    }

    auto labels = QJsonArray_toList<QString>(json_labels);
    auto additionalResults = QJsonArray_toList<QString>(json_additionalResults);

    auto result = new ClassificationResult(m_workingDir, classification_data, labels, additionalResults);
    emit sig_normal_loadClassificationResultData(view, result);
}

void ResultsImporter::slot_comparison_loadClassificationResultGraphics(GenericGraphicsView *receiver,
                                                                       const QString &runNameToCompare) const {
    loadGraphicsInView(receiver, m_classificationResultsDir, runNameToCompare);
}

/**
 * Training result slots
 */
void
ResultsImporter::slot_comparison_loadTrainingResultData(TrainingResultView *view,
                                                        const QString &runNameToCompare) const {
    Q_ASSERT(view);
    view->setSaved(true);

    auto filepath = getResultDataPath(TRAINING_JSON, m_trainingResultsDir, runNameToCompare);
    auto jsonObject = JSON_Toolbox::readJSONFromFile(filepath);

    auto json_accuracy_data = jsonObject["accuracy_data"].toArray();
    auto json_class_labels = jsonObject["class_labels"].toArray();
    auto json_confusionmatrix = jsonObject["confusionmatrix"].toArray();
    auto json_mostMisclassifiedImages = jsonObject["most_misclassified_images"].toArray();
    auto top1 = jsonObject["top1"].toDouble();
    auto top5 = jsonObject["top5"].toDouble();
    auto json_additionalResults = jsonObject["additionalResults"].toArray();

    QMap<int, QPair<double, double>> accuracy_data;
    for (const auto &value: json_accuracy_data) {
        auto obj = value.toObject();
        int iteration = obj["iteration"].toInt();
        int train = obj["train"].toInt();
        int validation = obj["validation"].toInt();

        accuracy_data[iteration] = {train, validation};
    }

    auto class_labels = QJsonArray_toList<QString>(json_class_labels);
    auto confusionmatrix = QJsonArray_toList<int>(json_confusionmatrix);
    auto most_misclassified_images = QJsonArray_toList<QString>(json_mostMisclassifiedImages);
    auto additionalResults = QJsonArray_toList<QString>(json_additionalResults);

    auto result = new TrainingResult(m_workingDir, accuracy_data, class_labels, confusionmatrix,
                                     most_misclassified_images, top1, top5, additionalResults);
    emit sig_normal_loadTrainingResultData(view, result);
}

void ResultsImporter::slot_comparison_loadTrainingResultGraphics(GenericGraphicsView *receiver,
                                                                 const QString &runNameToCompare) const {
    loadGraphicsInView(receiver, m_trainingResultsDir, runNameToCompare);
}

void ResultsImporter::loadGraphicsInView(GenericGraphicsView *receiver, const QString &baseDir,
                                         const QString &resultsFolder) {
    Q_ASSERT(receiver);

    auto dir = QDir(baseDir);
    auto folderIdentifier = Result::savableRepresentation(resultsFolder);
    dir.cd(folderIdentifier);

    for (const auto &file: dir.entryInfoList(QDir::Files, QDir::Time)) {
        for (int type = 0; type < $GRAPHICSTYPES_COUNT; type++) {
            auto regex = GRAPHICSTYPE2REGEX[type];

            auto match = regex.match(file.fileName());
            if (!match.hasMatch()) continue;

            auto fileIdentifier = match.captured(1);

            if (folderIdentifier == fileIdentifier)
                passResultGraphicsMultiplexer(receiver, file, type);
        }
    }
}

void ResultsImporter::passResultGraphicsMultiplexer(GenericGraphicsView *receiver, const QFileInfo &file, int type) {
    Q_ASSERT(receiver);
    QGraphicsItem *graphics;

    //Create graphics item for vector/pixmap items accordingly
    if (file.suffix() == "svg")
        graphics = new QGraphicsSvgItem(file.absoluteFilePath());
    else
        graphics = new QGraphicsPixmapItem(file.absoluteFilePath());

    auto graphics_ptr = QSharedPointer<QGraphicsItem>(graphics);

    switch (type) {
        case CLASSIFICATION:
            receiver->setClassificationGraphics(graphics_ptr);
            break;
        case ACCURACYCURVE:
            receiver->setAccuracyCurve(graphics_ptr);
            break;
        case CONFUSIONMATRIX:
            receiver->setConfusionMatrix(graphics_ptr);
            break;
        case TOPACCURACIES:
            //Top Accuracies Graphics are not imported for comparison. Skip them.
            break;
        default:
            qDebug() << "Attempted to set unknown result graphics type";
            break;
    }
}