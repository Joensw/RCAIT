#include "resultsprocessor.h"

void ResultsProcessor::addGraphicsGenerationJob(GenericGraphicsView *receiver,
                                                const QList<QSharedPointer<GenericResultGraphics>> &graphicsList) {

    auto count = 1;
    auto total = graphicsList.size();
    for (const auto &graphics: graphicsList) {
        //Connect 'finished graphics generation' signal with slot
        connect(&*graphics, &GenericResultGraphics::sig_graphicsGenerated,
                this, &ResultsProcessor::slot_graphicsGenerated);

        auto type = QString(graphics->metaObject()->className());
        qInfo() << qPrintable(QString("(%1/%2) Generating %3 \n").arg(count++).arg(total).arg(type));

        m_mapGraphicsByReceiver.insert(receiver, &*graphics);
        graphics->generateGraphics(receiver);
    }
}

void ResultsProcessor::slot_graphicsGenerated(GenericGraphicsView *receiver,
                                              GenericResultGraphics *graphics, const QString &fullPath) {

    if (!QFile::exists(fullPath)) return;
    m_mapGraphicsByReceiver.remove(receiver, graphics);
    if (m_mapGraphicsByReceiver.contains(receiver)) return;
    receiver->setSaved(false);
}

/**
 * Top Accuracies slots
 */
void ResultsProcessor::slot_normal_generateTopAccuraciesGraphics(TopAccuraciesView *receiver,
                                                                 const QSharedPointer<TopAccuraciesGraphics> &graphics) {
    //Keeps user from clicking the 'update graphics' button multiple times
    receiver->updateGraphicsButton_setEnabled(false);

    addGraphicsGenerationJob(receiver, {graphics});

    //Enable button again after generating graphics finished
    connect(&*graphics, &GenericResultGraphics::sig_graphicsGenerated,
            this, [receiver] { receiver->updateGraphicsButton_setEnabled(true); });
}

/**
 * Classification result slots
 */
void ResultsProcessor::slot_normal_loadClassificationResultData(ClassificationResultView *view,
                                                                ClassificationResult *result) {
    const auto &map = result->getClassificationData();
    const auto &labels = result->getLabels();
    Q_ASSERT(!map.isEmpty());
    Q_ASSERT(!labels.isEmpty());

    QMap<int, QStringList> tableMap;

    int rowNumber = 1;
    for (const auto &accList: map) {
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
    const auto &classificationGraphics = result->getClassificationGraphics();
    addGraphicsGenerationJob(receiver, {classificationGraphics});
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
    const auto &accCurve = result->getAccuracyCurve();
    const auto &confusionMatrix = result->getConfusionMatrix();
    addGraphicsGenerationJob(receiver, {accCurve, confusionMatrix});
}
