#include <QJsonDocument>
#include <QFile>
#include <projectmanager.h>
#include "resultsexporter.h"


void ResultsExporter::updateResultFolderPaths() {
    auto &pm = ProjectManager::getInstance();
    m_resultsDir = pm.getResultsDir();
    m_trainingResultsDir = pm.getTrainingResultsDir();
    m_classificationResultsDir = pm.getClassificationResultsDir();
}

void ResultsExporter::slot_save_TopAccuracies(TopAccuraciesGraphics *graphics) {
    const auto &fileName = graphics->getFullName();
    const auto &identifier = graphics->getIdentifier();
    const auto &extension = graphics->getExtension();
    const auto &timestamp = Result::generateExtendedTimestamp();

    auto targetName = QString("%1_%2.%3").arg(identifier, timestamp, extension);

    auto oldFilePath = QFileInfo(fileName).absoluteFilePath();
    auto newFilePath = QDir(m_trainingResultsDir).absoluteFilePath(targetName);

    QFile::copy(oldFilePath, newFilePath);
}

void ResultsExporter::slot_save_TrainingResult(TrainingResult *result) {

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
