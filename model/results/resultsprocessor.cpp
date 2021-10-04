#include "resultsprocessor.h"

void ResultsProcessor::addGraphicsGenerationJob(GenericGraphicsView *receiver,
                                                const QList<QSharedPointer<GenericResultGraphics>> &graphicsList) {

    auto count = 1;
    auto total = graphicsList.size();
    for (const auto &graphics: graphicsList) {
        if (!graphics) continue;

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
                                              const QPointer<GenericResultGraphics> &graphics) {
    Q_ASSERT(receiver);
    Q_ASSERT(graphics);
    if (!QFile::exists(graphics->getFullPath())) return;
    m_mapGraphicsByReceiver.remove(receiver, graphics);
    if (!m_mapGraphicsByReceiver.contains(receiver)) {
        //All pending graphics were generated. Result can be saved now.
        receiver->setSaved(false);
    }
}

/**
 * Top Accuracies slots
 */
void ResultsProcessor::slot_normal_generateTopAccuraciesGraphics(TopAccuraciesView *receiver,
                                                                 const QSharedPointer<TopAccuraciesGraphics> &graphics) {
    //Keeps user from clicking the 'update graphics' button multiple times
    receiver->setUpdateGraphicsButtonState(false);

    addGraphicsGenerationJob(receiver, {graphics});

    //Enable button again after generating graphics finished
    connect(&*graphics, &GenericResultGraphics::sig_graphicsGenerated,
            this, [receiver] { receiver->setUpdateGraphicsButtonState(true); });
}

/**
 * Classification result slots
 */
void ResultsProcessor::slot_normal_loadClassificationResultData(ClassificationResultView *view,
                                                                const QPointer<ClassificationResult> &result) {
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
        auto max_confidence = QString::number(*max * 100, 'f', 2);
        const auto &label = labels[index_max];

        tableMap[rowNumber++] = {max_confidence, label};
    }
    view->setClassificationData(tableMap);
}

void ResultsProcessor::slot_normal_generateClassificationResultGraphics(GenericGraphicsView *receiver,
                                                                        const QPointer<ClassificationResult> &result) {
    const auto &classificationGraphics = result->getClassificationGraphics();
    addGraphicsGenerationJob(receiver, {classificationGraphics});
}

void ResultsProcessor::slot_normal_loadAccuracyData(TopAccuraciesView *view,
                                                    const QPointer<TopAccuraciesGraphics> &graphics,
                                                    const QPointer<TrainingResult> &result) const {
    Q_ASSERT(graphics);
    Q_ASSERT(view);
    Q_ASSERT(result);

    auto runNameToCompare = result->getIdentifier();
    auto top1 = result->getTop1Accuracy();
    auto top5 = result->getTop5Accuracy();

    graphics->addDataRow(runNameToCompare, {top1, top5});
    view->addTopAccuraciesEntry(runNameToCompare, top1, top5);
}

/**
 * Training result slots
 */
void
ResultsProcessor::slot_normal_loadTrainingResultData(TrainingResultView *view, const QPointer<TrainingResult> &result) {
    auto mostMisclassifiedImages = result->getMostMisclassifiedImages();
    view->setMostMisclassifiedImages(mostMisclassifiedImages);
}

void ResultsProcessor::slot_normal_generateTrainingResultGraphics(GenericGraphicsView *receiver,
                                                                  const QPointer<TrainingResult> &result) {
    const auto &accCurve = result->getAccuracyCurve();
    const auto &confusionMatrix = result->getConfusionMatrix();
    addGraphicsGenerationJob(receiver, {accCurve, confusionMatrix});
}
