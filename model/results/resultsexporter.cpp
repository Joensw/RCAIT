#include "resultsexporter.h"

ResultsExporter::ResultsExporter()
        : m_projectManager(&ProjectManager::getInstance()) {

}

void ResultsExporter::updateResultFolderPaths() {
    m_trainingResultsDir = m_projectManager->getTrainingResultsDir();
    m_classificationResultsDir = m_projectManager->getClassificationResultsDir();
}

void ResultsExporter::slot_save_TopAccuracies(const QSharedPointer<TopAccuraciesGraphics> &graphics, bool &success) {
    const auto &fileName = graphics->getFullName();
    const auto &baseName = graphics->getBaseName();
    const auto &extension = graphics->getExtension();
    const auto &timestamp = Result::generateExtendedTimestamp();

    const auto targetName = QString("%1_%2.%3").arg(baseName, timestamp, extension);

    const auto &oldFilePath = graphics->getFullPath();
    const auto newFilePath = QDir(m_trainingResultsDir).absoluteFilePath(targetName);

    //Move graphics to result folder, set success state accordingly
    success = saveFile(oldFilePath, newFilePath);
}

void ResultsExporter::slot_save_TrainingResult(const QSharedPointer<TrainingResult>& result, bool &success) {
    success = true;

    const auto &identifier = result->getSavableIdentifier();
    const auto resultFolder = createResultDir(m_trainingResultsDir, identifier);
    const auto savePath = resultFolder.absoluteFilePath(TRAINING_JSON.arg(identifier));
    const auto JSON = trainingResult2JSON(result);

    success &= JSON_Toolbox::writeJSONToFile(JSON, savePath);

    //Save images
    auto accCurveFilename = result->getAccuracyCurve()->getFullName();
    auto matrixFileName = result->getConfusionMatrix()->getFullName();
    auto old_accCurvePath = result->getAccuracyCurve()->getFullPath();
    auto old_matrixPath = result->getConfusionMatrix()->getFullPath();

    //Move to result folder
    success &= saveFile(old_accCurvePath, resultFolder.absoluteFilePath(accCurveFilename));
    success &= saveFile(old_matrixPath, resultFolder.absoluteFilePath(matrixFileName));

}

void ResultsExporter::slot_save_ClassificationResult(const QSharedPointer<ClassificationResult> &result, bool &success) {
    success = true;

    const auto &identifier = result->getSavableIdentifier();
    const auto resultFolder = createResultDir(m_classificationResultsDir, identifier);
    const auto savePath = resultFolder.absoluteFilePath(CLASSIFICATION_JSON.arg(identifier));

    auto JSON = classificationResult2JSON(result);
    success &= JSON_Toolbox::writeJSONToFile(JSON, savePath);

    //Save images
    auto graphicsFilename = result->getClassificationGraphics()->getFullName();
    auto old_graphicsPath = result->getClassificationGraphics()->getFullPath();

    //Move to result folder
    success &= saveFile(old_graphicsPath, resultFolder.absoluteFilePath(graphicsFilename));
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

bool ResultsExporter::saveFile(const QString &oldFilePath, const QString &newFilePath) {
    QFile::rename(oldFilePath, newFilePath);
    auto saveWorked = QFile::exists(newFilePath);
    if (!saveWorked) {
        qWarning() << "Saving file " << oldFilePath << " -> " << newFilePath << " failed";
    }
    return saveWorked;
}
