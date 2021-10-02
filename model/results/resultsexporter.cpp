#include <fstream>
#include "resultsexporter.h"

ResultsExporter::ResultsExporter()
        : m_projectManager(&ProjectManager::getInstance()) {

}

void ResultsExporter::updateResultFolderPaths() {
    m_resultsDir = m_projectManager->getResultsDir();
    m_trainingResultsDir = m_projectManager->getTrainingResultsDir();
    m_classificationResultsDir = m_projectManager->getClassificationResultsDir();
}

void
ResultsExporter::slot_save_TopAccuracies(const QSharedPointer<TopAccuraciesGraphics> &graphics, bool &success) const {
    const auto &baseName = graphics->getBaseName();
    const auto &extension = graphics->getExtension();
    const auto &timestamp = Result::generateExtendedTimestamp();

    const auto targetName = QString("%1_%2.%3").arg(baseName, timestamp, extension);

    //Move graphics to result folder, set success state accordingly
    saveGraphics();
}

void ResultsExporter::slot_save_TrainingResult(const QSharedPointer<TrainingResult> &result, bool &success) const {
    success = true;

    const auto &identifier = result->getSavableIdentifier();
    const auto resultFolder = createResultDir(m_trainingResultsDir, identifier);
    const auto savePath = resultFolder.absoluteFilePath(TRAINING_JSON.arg(identifier));
    const auto JSON = trainingResult2JSON(result);

    success &= JSON_Toolbox::writeJSONToFile(JSON, savePath);

    //Move to result folder
    saveGraphics();

}

void ResultsExporter::slot_save_ClassificationResult(const QSharedPointer<ClassificationResult> &result,
                                                     bool &success) const {
    success = true;

    const auto &identifier = result->getSavableIdentifier();
    const auto resultFolder = createResultDir(m_classificationResultsDir, identifier);
    const auto savePath = resultFolder.absoluteFilePath(CLASSIFICATION_JSON.arg(identifier));

    auto JSON = classificationResult2JSON(result);
    success &= JSON_Toolbox::writeJSONToFile(JSON, savePath);

    //Move to result folder
    saveGraphics();
}

QJsonObject ResultsExporter::trainingResult2JSON(const QSharedPointer<TrainingResult> &result) {
    QJsonObject JSON;

    //Extract relevant data from result
    const auto &accuracy_data = result->getAccuracyCurveData();
    const auto &class_labels = result->getClassLabels();
    const auto &confusionmatrix = result->getConfusionMatrixValues();
    const auto most_misclassified_images = result->getMostMisclassifiedImages();
    const auto top1 = result->getTop1Accuracy();
    const auto top5 = result->getTop5Accuracy();
    const auto additionalResults = result->getAdditionalResults();

    //Create JSON Objects
    QJsonArray json_accuracy_data;
    for (const auto &[iteration, pair]: MapAdapt(accuracy_data)) {
        auto &[train, validation] = pair;

        QJsonObject sub;
        sub["iteration"] = iteration;
        sub["train"] = train;
        sub["validation"] = validation;

        json_accuracy_data << sub;
    }
    JSON["accuracy_data"] = json_accuracy_data;
    JSON["class_labels"] = QJsonArray::fromStringList(class_labels);
    JSON["confusionmatrix"] = QJsonArray_fromAnyList(confusionmatrix);
    JSON["most_misclassified_images"] = QJsonArray::fromStringList(most_misclassified_images);

    JSON["top1"] = top1;
    JSON["top5"] = top5;

    JSON["additionalResults"] = QJsonArray::fromStringList(additionalResults);

    //JSON object is prepared now, so return it.
    return JSON;
}

QJsonObject ResultsExporter::classificationResult2JSON(const QSharedPointer<ClassificationResult> &result) {
    QJsonObject JSON;
    //Extract relevant data from result
    const auto &classification_data = result->getClassificationData();
    const auto &labels = result->getLabels();
    auto additionalResults = result->getAdditionalResults();

    //Create JSON Objects
    QJsonArray json_classification_data;
    for (const auto &[image_path, confidences]: MapAdapt(classification_data)) {

        QJsonObject json_sub;
        QJsonArray json_confidenceArray = QJsonArray_fromAnyList(confidences);

        json_sub["image_path"] = image_path;
        json_sub["confidence"] = json_confidenceArray;

        json_classification_data << json_sub;
    }
    JSON["classification_data"] = json_classification_data;

    JSON["labels"] = QJsonArray::fromStringList(labels);
    JSON["additionalResults"] = QJsonArray::fromStringList(additionalResults);

    //JSON object is prepared now, so return it
    return JSON;
}

QDir ResultsExporter::createResultDir(const QString &baseDir, const QString &identifier) {
    auto resultFolder = QDir(baseDir);

    if (!resultFolder.mkdir(identifier)) {
        qWarning() << "Error creating results dir " << identifier;
        return {};
    }
    resultFolder.cd(identifier);
    return resultFolder;
}

void ResultsExporter::saveGraphics() const {
    QDir resultsDir(m_resultsDir);

    for (const auto &file: resultsDir.entryInfoList(QDir::Files)) {
        for (int type = 0; type < $GRAPHICSTYPES_COUNT; type++) {
            auto regex = GRAPHICSTYPE2REGEX[type];
            auto filePath = file.absoluteFilePath();
            auto match = regex.match(file.fileName());
            if (!match.hasMatch()) continue;

            auto identifier = match.captured(1);

            graphicsTypeMultiplexer(type, filePath, identifier);

        }
    }
}

void ResultsExporter::graphicsTypeMultiplexer(int type, const QString &filePath, const QString &identifier) const {
    QDir trainingResultsDir(m_trainingResultsDir);
    QDir classificationResultsDir(m_classificationResultsDir);
    switch (QString newPath; type) {
        case CLASSIFICATION:
            newPath = m_classificationResultsDir + "/" + identifier;
            qDebug() << "Target folder to save to: " << newPath;
            if (classificationResultsDir.exists(identifier)) {
                QFile::rename(filePath, newPath);
            }
            break;
        case ACCURACYCURVE:
        case CONFUSIONMATRIX:
            newPath = m_trainingResultsDir + "/" + identifier;
            qDebug() << "Target folder to save to: " << newPath;
            if (trainingResultsDir.exists(identifier)) {
                QFile::rename(filePath, newPath);
            }
            break;
        case TOPACCURACIES:
            // Top-Accuracies graphics have no folder so pass and do nothing
            break;
        default:
            qDebug() << "Unknown graphics file encountered. Leaving it in default location";
            break;
    }
}
