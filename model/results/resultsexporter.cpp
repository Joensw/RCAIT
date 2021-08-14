#include <QJsonDocument>
#include <QFile>
#include <projectmanager.h>
#include <mapadapt.h>
#include <QJsonArray>
#include "resultsexporter.h"


void ResultsExporter::updateResultFolderPaths() {
    auto &pm = ProjectManager::getInstance();
    m_resultsDir = pm.getResultsDir();
    m_trainingResultsDir = pm.getTrainingResultsDir();
    m_classificationResultsDir = pm.getClassificationResultsDir();
}

void ResultsExporter::slot_save_TopAccuracies(TopAccuraciesGraphics *graphics) {
    const auto &fileName = graphics->getFullName();
    const auto &baseName = graphics->getBaseName();
    const auto &extension = graphics->getExtension();
    const auto &timestamp = Result::generateExtendedTimestamp();

    auto targetName = QString("%1_%2.%3").arg(baseName, timestamp, extension);

    auto oldFilePath = QFileInfo(fileName).absoluteFilePath();
    auto newFilePath = QDir(m_trainingResultsDir).absoluteFilePath(targetName);

    QFile::copy(oldFilePath, newFilePath);
}

void ResultsExporter::slot_save_TrainingResult(TrainingResult *result) {
    auto resultsFolder = QDir(m_trainingResultsDir);
    const QString &identifier = result->getIdentifier();
    auto success = resultsFolder.mkdir(identifier);

    if (!success) {
        qWarning() << "Error creating results dir " << identifier;
        return;
    }
    resultsFolder.cd(identifier);

    //Extract relevant data from result
    const auto &accuracy_data = result->getAccuracyCurveData();
    const auto &class_labels = result->getClassLabels();
    const auto &confusionmatrix = result->getConfusionMatrixValues();
    auto most_misclassified_images = result->getMostMisclassifiedImages();
    auto top1 = result->getTop1Accuracy();
    auto top5 = result->getTop5Accuracy();
    auto additionalResults = result->getAdditionalResults();

    //Create JSON Objects
    QJsonObject JSON;
    QJsonArray json_accuracy_data;
    for (const auto &[iteration, pair] : MapAdapt(accuracy_data)) {
        auto &[train, validation] = pair;

        QJsonObject sub;
        sub["iteration"] = iteration;
        sub["train"] = train;
        sub["validation"] = validation;

        json_accuracy_data << sub;
    }
    JSON["accuracy_data"] = json_accuracy_data;

    JSON["class_labels"] = QJsonArray::fromStringList(class_labels);

    QJsonArray json_confusionmatrix;
    for (const auto &value : confusionmatrix) {
        json_confusionmatrix << value;
    }
    JSON["confusionmatrix"] = json_confusionmatrix;

    JSON["most_misclassified_images"] = QJsonArray::fromStringList(most_misclassified_images);

    JSON["top1"] = top1;
    JSON["top5"] = top5;

    JSON["additionalResults"] = QJsonArray::fromStringList(additionalResults);

    //JSON object is prepared now, so save it
    auto fileName = QString("training_%1.json").arg(identifier);
    auto savePath = resultsFolder.absoluteFilePath(fileName);
    writeJSON(JSON, savePath);

    //Save images
    //TODO prepare for saving images in temp dir
    auto accCurveFilename = result->getAccuracyCurve()->getFullName();
    auto matrixFileName = result->getConfusionMatrix()->getFullName();
    auto old_accCurvePath = result->getAccuracyCurve()->getFullName();
    auto old_matrixPath = result->getConfusionMatrix()->getFullName();

    //Copy to result folder
    QFile::copy(old_accCurvePath, resultsFolder.absoluteFilePath(accCurveFilename));
    QFile::copy(old_matrixPath, resultsFolder.absoluteFilePath(matrixFileName));

}

void ResultsExporter::slot_save_ClassificationResult(ClassificationResult *result) {

}

void ResultsExporter::writeJSON(const QJsonObject &jsonObject, const QString &filepath) {
    QJsonDocument json_doc(jsonObject);
    auto rawData = json_doc.toJson();

    QFile save_file(filepath);
    if (!save_file.open(QIODevice::WriteOnly)) {
        qWarning() << "failed to open save file";
        return;
    }
    save_file.write(rawData);
    save_file.close();
}
