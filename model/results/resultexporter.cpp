#include <QJsonDocument>
#include <QFile>
#include <projectmanager.h>
#include "resultexporter.h"


void ResultExporter::updateResultFolderPaths() {
    auto &pm = ProjectManager::getInstance();
    m_resultsDir = pm.getResultsDir();
    m_trainingResultsDir = pm.getTrainingResultsDir();
    m_classificationResultsDir = pm.getClassificationResultsDir();
}

void ResultExporter::slot_save_TopAccuracies(TopAccuraciesGraphics *graphics) {

}

void ResultExporter::slot_save_TrainingResult(TrainingResult *result) {

}

void ResultExporter::slot_save_ClassificationResult(ClassificationResult *result) {

}

void ResultExporter::writeJSON(const QJsonObject &jsonObject, const QString &filepath) {
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
