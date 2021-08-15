#include <projectmanager.h>
#include <classificationresultview.h>
#include "resultsprocessor.h"
#include "mapadapt.h"

const QString TRAINING_JSON = QString("training_%1.json");
const QString CLASSIFICATION_JSON = QString("classification_%1.json");

/**
 * Top Accuracies slots
 */
void ResultsProcessor::slot_normal_generateTopAccuraciesGraphics(GenericGraphicsView *receiver,
                                                                 TopAccuraciesGraphics *graphics) {
    graphics->generateGraphics(receiver);
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

    auto tableMap = QMap<int, QStringList>();

    int rowNumber = 1;
    for (const auto &[_, accList] : MapAdapt(map)) {
        //Assert that each accuracy value has a corresponding label
        Q_ASSERT(accList.size() == labels.size());
        auto max = std::max_element(accList.begin(), accList.end());

        //Calculate argmax(map), choose label with the highest confidence
        auto index_max = std::distance(accList.begin(), max);
        auto max_confidence = QString::number(*max, 'f', 2);
        auto label = labels[index_max];

        tableMap[rowNumber++] = {max_confidence, label};
    }
    view->setClassificationData(tableMap);
}

void ResultsProcessor::slot_normal_generateClassificationResultGraphics(GenericGraphicsView *receiver,
                                                                        ClassificationResult *result) {
    auto graphics = result->getClassificationGraphics();
    graphics->generateGraphics(receiver);
}

/**
 * Training result slots
 */
void ResultsProcessor::slot_normal_loadTrainingResultData(TrainingResultView *view, TrainingResult *result) {
    auto mostMisclassifiedImages = result->getMostMisclassifiedImages();
    view->setMostMisclassifiedImages(mostMisclassifiedImages);
}

void ResultsProcessor::slot_normal_generateTrainingResultGraphics(GenericGraphicsView *receiver,
                                                                  TrainingResult *result) {
    auto accCurve = result->getAccuracyCurve();
    auto confusionMatrix = result->getConfusionMatrix();
    accCurve->generateGraphics(receiver);
    confusionMatrix->generateGraphics(receiver);
}
