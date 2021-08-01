#include <projectmanager.h>
#include <classificationresultview.h>
#include "resultsprocessor.h"

ResultsProcessor::ResultsProcessor() {
    //TODO Create identifier utility class which creates date/time identifier statically
    m_topAccuraciesGraphics = new TopAccuraciesGraphics();
}

void ResultsProcessor::slot_generateTopAccuraciesGraphics(AbstractGraphicsView *receiver) {
    m_topAccuraciesGraphics->updateIdentifier(Result::generateIdentifier());
    m_topAccuraciesGraphics->generateGraphics(receiver);
}

void ResultsProcessor::slot_generateClassificationResultGraphics(AbstractGraphicsView *receiver) {
    //TODO
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
        if (baseName == "accuracycurve_" + runNameToCompare) {

            if (ext == "svg")
                view->setAccuracyCurve(new QGraphicsSvgItem(file.absoluteFilePath()));
            else
                view->setAccuracyCurve(new QGraphicsPixmapItem(file.absoluteFilePath()));
            continue;
        }
    }
    //TODO Load most misclassified images.
}

void ResultsProcessor::slot_loadAccuracyDataToCompare(const QString &runNameToCompare, TopAccuraciesView *view) {
    double top1 = QRandomGenerator::global()->bounded(100);
    double top5 = QRandomGenerator::global()->bounded(100);
    m_topAccuraciesGraphics->addDataRow(runNameToCompare, {top1, top5});
    view->addTopAccuraciesEntry(runNameToCompare, top1, top5);
    //TODO Load real accuracy data from JSON file
}

void ResultsProcessor::slot_unloadAccuracyDataToCompare(const QString &runNameToCompare, TopAccuraciesView *view) {
    m_topAccuraciesGraphics->removeDataRow(runNameToCompare);
    view->removeTopAccuraciesEntry(runNameToCompare);
}

void ResultsProcessor::slot_loadClassificationDataToCompare(const QString &runNameToCompare,
                                                            ClassificationResultView *view) {
    //TODO Load data from JSON file
    QStringList labels = {"Car", "Truck", "Airplane", "Boat", "Bike"};
    QList<QPair<QString, QStringList>> data;
    for (int j = 0; j < 20; ++j) {
        long long randomLabel = QRandomGenerator::global()->bounded(labels.size());
        auto label = labels[randomLabel];
        int random = QRandomGenerator::global()->bounded(65, 100);
        data << qMakePair(QString("Image %1").arg(j), QStringList() << QString::number(random) << label);
    }
    view->setClassificationData(data);

}
