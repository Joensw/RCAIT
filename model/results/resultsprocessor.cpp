#include <projectmanager.h>
#include <classificationresultview.h>
#include "resultsprocessor.h"
#include "mapadapt.h"

enum Type {
    CLASSIFICATION,
    ACCURACYCURVE,
    CONFUSIONMATRIX,
    TOPACCURACIES,
    _COUNT
};
const std::array<QRegularExpression, _COUNT> TYPES2REGEX = {
        QRegularExpression("classification_(.*)\\.(svg|png)$"),
        QRegularExpression("accuracycurve_(.*)\\.(svg|png)$"),
        QRegularExpression("confusionmatrix_(.*)\\.(svg|png)$"),
        QRegularExpression("topaccuracies_(.*)\\.(svg|png)$")
};

ResultsProcessor::ResultsProcessor() {
    m_topAccuraciesGraphics = new TopAccuraciesGraphics();
}

/**
 * Top Accuracies slots
 */
void ResultsProcessor::slot_normal_generateTopAccuraciesGraphics(AbstractGraphicsView *receiver) {
    m_topAccuraciesGraphics->updateIdentifier(Result::generateIdentifier());
    m_topAccuraciesGraphics->generateGraphics(receiver);
}

void ResultsProcessor::slot_comparison_loadAccuracyData(TopAccuraciesView *view, const QString &runNameToCompare) {
    double top1 = QRandomGenerator::global()->bounded(100);
    double top5 = QRandomGenerator::global()->bounded(100);
    m_topAccuraciesGraphics->addDataRow(runNameToCompare, {top1, top5});
    view->addTopAccuraciesEntry(runNameToCompare, top1, top5);
    //TODO Load real accuracy data from JSON file
}

void ResultsProcessor::slot_comparison_unloadAccuracyData(TopAccuraciesView *view, const QString &runNameToCompare) {
    m_topAccuraciesGraphics->removeDataRow(runNameToCompare);
    view->removeTopAccuraciesEntry(runNameToCompare);
}


/**
 * Classification result slots
 */
void ResultsProcessor::slot_normal_loadClassificationResultData(ClassificationResultView *view,
                                                                ClassificationResult *result) {
    auto map = result->getClassificationData();
    auto labels = result->getLabels();
    Q_ASSERT(!map.isEmpty());
    Q_ASSERT(!labels.isEmpty());

    auto tableMap = QMap<QString, QStringList>();

    for (const auto &[image, accList] : MapAdapt(map)) {
        //Assert that each accuracy value has a corresponding label
        Q_ASSERT(accList.size() == labels.size());
        auto max = std::max_element(accList.begin(), accList.end());

        //Calculate argmax(map)
        auto index_max = std::distance(accList.begin(), max);
        auto max_accuracy = QString::number(*max);
        auto label = labels[index_max];

        tableMap[image] = {max_accuracy, label};
    }
    view->setClassificationData(tableMap);
}

void ResultsProcessor::slot_normal_generateClassificationResultGraphics(AbstractGraphicsView *receiver,
                                                                        ClassificationResult *result) {
    auto graphics = result->getClassificationGraphics();
    graphics->generateGraphics(receiver);
}

void ResultsProcessor::slot_comparison_loadClassificationResultData(ClassificationResultView *view,
                                                                    const QString &runNameToCompare) {
    //TODO Load data from JSON file
    QStringList labels = {"Car", "Truck", "Airplane", "Boat", "Bike"};
    QMap<QString, QStringList> data;
    for (int j = 0; j < 20; ++j) {
        long long randomLabel = QRandomGenerator::global()->bounded(labels.size());
        auto label = labels[randomLabel];
        int random = QRandomGenerator::global()->bounded(65, 100);
        data.insert(QString("Image %1").arg(j), {QString::number(random), label});
    }
    view->setClassificationData(data);

}

void ResultsProcessor::slot_comparison_loadClassificationResultGraphics(AbstractGraphicsView *receiver,
                                                                        const QString &runNameToCompare) {
    auto dirPath = ProjectManager::getInstance().getClassificationResultsDir();
    loadGraphicsInView(receiver, runNameToCompare, dirPath);
}


/**
 * Training result slots
 */
void ResultsProcessor::slot_normal_loadTrainingResultData(TrainingResultView *view, TrainingResult *result) {
    auto mostMisclassifiedImages = result->getMostMisclassifiedImages();
    view->setMostMisclassifiedImages(mostMisclassifiedImages);
}

void ResultsProcessor::slot_normal_generateTrainingResultGraphics(AbstractGraphicsView *receiver,
                                                                  TrainingResult *result) {
    auto accCurve = result->getAccuracyCurve();
    auto confusionMatrix = result->getConfusionMatrix();
    accCurve->generateGraphics(receiver);
    confusionMatrix->generateGraphics(receiver);
}

void
ResultsProcessor::slot_comparison_loadTrainingResultData(TrainingResultView *view, const QString &runNameToCompare) {
    //TODO Load most misclassified images.
}

void ResultsProcessor::slot_comparison_loadTrainingResultGraphics(AbstractGraphicsView *receiver,
                                                                  const QString &runNameToCompare) {
    auto dirPath = ProjectManager::getInstance().getTrainingResultsDir();
    loadGraphicsInView(receiver, runNameToCompare, dirPath);
}

void ResultsProcessor::loadGraphicsInView(AbstractGraphicsView *receiver, const QString &resultsFolder,
                                          const QString &baseDir){
    auto dir = QDir(baseDir);
    dir.cd(resultsFolder);

    for (const auto &file : dir.entryInfoList(QDir::Files, QDir::Time)) {
        for (int i = 0; i < _COUNT; i++) {
            auto regex = TYPES2REGEX[i];
            auto match = regex.match(file.fileName());

            if (!match.hasMatch()) continue;

            auto identifier = match.captured(1);
            auto extension = match.captured(2);

            if (resultsFolder != identifier) continue;

            QGraphicsItem* graphics;
            if (extension == "svg")
                graphics = new QGraphicsSvgItem(file.absoluteFilePath());
            else
                graphics = new QGraphicsPixmapItem(file.absoluteFilePath());

            switch(i){
                case CLASSIFICATION:
                    receiver->setClassificationGraphics(graphics);
                    break;
                case ACCURACYCURVE:
                    receiver->setAccuracyCurve(graphics);
                    break;
                case CONFUSIONMATRIX:
                    receiver->setConfusionMatrix(graphics);
                    break;
                case TOPACCURACIES:
                    receiver->setTopAccuraciesGraphics(graphics);
                    break;
                default:
                    qDebug() << "Attempted to set unknown result graphics type";
                    break;
            }

        }
    }
}