#include <projectmanager.h>
#include <classificationresultview.h>
#include "resultsprocessor.h"
#include "mapadapt.h"

ResultsProcessor::ResultsProcessor() {
    m_topAccuraciesGraphics = new TopAccuraciesGraphics();
}

void ResultsProcessor::slot_normal_generateTopAccuraciesGraphics(AbstractGraphicsView *receiver) {
    m_topAccuraciesGraphics->updateIdentifier(Result::generateIdentifier());
    m_topAccuraciesGraphics->generateGraphics(receiver);
}

void ResultsProcessor::slot_comparison_loadAccuracyData(const QString &runNameToCompare, TopAccuraciesView *view) {
    double top1 = QRandomGenerator::global()->bounded(100);
    double top5 = QRandomGenerator::global()->bounded(100);
    m_topAccuraciesGraphics->addDataRow(runNameToCompare, {top1, top5});
    view->addTopAccuraciesEntry(runNameToCompare, top1, top5);
    //TODO Load real accuracy data from JSON file
}

void ResultsProcessor::slot_comparison_unloadAccuracyData(const QString &runNameToCompare, TopAccuraciesView *view) {
    m_topAccuraciesGraphics->removeDataRow(runNameToCompare);
    view->removeTopAccuraciesEntry(runNameToCompare);
}




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

void ResultsProcessor::slot_comparison_loadClassificationResultData(const QString &runNameToCompare,
                                                                    ClassificationResultView *view) {
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

void ResultsProcessor::slot_comparison_loadClassificationResultGraphics(const QString &runNameToCompare,
                                                                        AbstractGraphicsView *receiver) {
    //TODO Fill
    auto file = QFileInfo("classification_TEST.svg");
    receiver->setClassificationGraphics(new QGraphicsSvgItem(file.absoluteFilePath()));
}



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

void ResultsProcessor::slot_comparison_loadTrainingResultGraphics(const QString &runNameToCompare,
                                                                  TrainingResultView *view) {
    //Accuracy Curve
    int sum = 0;
    auto *pointsMap = new QMap<int, QPair<double, double>>();
    for (int j = 1; j <= 20; j++) {
        double random = QRandomGenerator::global()->bounded(3 * 100) / 100.0;
        int random2 = QRandomGenerator::global()->bounded(1, 10);
        sum += random2;
        pointsMap->insert(j, qMakePair(-100.0 / sum + 100, random + 90));
    }
    auto ac = new AccuracyCurve(runNameToCompare, *pointsMap);
    ac->generateGraphics(view);

    //Confusion Matrix
    QList<int> values = QList<int>();
    QStringList labels = {"A", "B", "C", "D", "E", "F", "G", "H"};
    const qsizetype N = labels.size();
    qsizetype target = 0;
    for (int j = 0; j < N * N; ++j) {
        int min = 0;
        int max = 10;
        //Check if we are on diagonal line of matrix
        if (target == j) {
            target += N + 1;
            min = 30;
            max = 100;
        }
        int random = QRandomGenerator::global()->bounded(min, max);
        values << random;
    }

    auto matrix = new ConfusionMatrix(runNameToCompare, labels, values);
    matrix->generateGraphics(view);
    /*
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
     */
    //TODO Load most misclassified images.
}