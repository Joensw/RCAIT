#include <projectmanager.h>
#include "resultsprocessor.h"

ResultsProcessor::ResultsProcessor() {
    //TODO Create identifier utility class which creates date/time identifier statically
    m_topAccuraciesGraphics = new TopAccuraciesGraphics(Result::generateIdentifier());
}

void ResultsProcessor::slot_generateTopAccuraciesGraphics(AbstractGraphicsView *receiver) {
    m_topAccuraciesGraphics->generateGraphics(receiver);
}

void ResultsProcessor::slot_addedRow_topAccuraciesTable(const QString &identifier, double top1, double top5) {
    m_topAccuraciesGraphics->addDataRow(identifier, top1, top5);
}

void ResultsProcessor::slot_removedRow_topAccuraciesTable(const QString &identifier) {
    m_topAccuraciesGraphics->removeDataRow(identifier);
}

void ResultsProcessor::slot_loadTrainingImagesToCompare(const QString &runNameToCompare, TrainingResultView *view) {
    auto dirPath = ProjectManager::getInstance().getResultsDir();
    auto dir = QDir(dirPath + '/' + runNameToCompare);

    for (const auto &file : dir.entryInfoList(QDir::Files, QDir::Name)) {
        auto baseName = file.baseName();
        auto ext = file.completeSuffix();
        if (baseName == "confusionmatrix_" + runNameToCompare) {

            if (ext == "svg")
                view->setConfusionMatrix(new QGraphicsSvgItem(file.absoluteFilePath()));
            else
                view->setConfusionMatrix(new QGraphicsPixmapItem(file.absoluteFilePath()));
            continue;
        }
        if (baseName == "losscurve_" + runNameToCompare) {

            if (ext == "svg")
                view->setLossCurve(new QGraphicsSvgItem(file.absoluteFilePath()));
            else
                view->setLossCurve(new QGraphicsPixmapItem(file.absoluteFilePath()));
            continue;
        }
    }
    //TODO Load most misclassified images.
}

void ResultsProcessor::slot_loadAccuracyDataToCompare(const QString &runNameToCompare, TopAccuraciesView *view) {
    view->addTableRow(runNameToCompare, QRandomGenerator::global()->bounded(100), QRandomGenerator::global()->bounded(100));
    //TODO Load real accuracy data from JSON file
}
