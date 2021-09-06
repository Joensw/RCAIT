#ifndef RESULTSPROCESSOR_H
#define RESULTSPROCESSOR_H


#include <QString>
#include <QMap>
#include <trainingresultview.h>
#include <topaccuraciesview.h>
#include <classificationresultview.h>
#include "topaccuraciesgraphics.h"
#include "classificationgraphics.h"
#include "trainingresult.h"
#include "classificationresult.h"
#include <projectmanager.h>
#include <ce_string.h>

constexpr CE_String TRAINING_JSON = "training_%1.json";
constexpr CE_String CLASSIFICATION_JSON = "classification_%1.json";

class ResultsProcessor : public QObject {
Q_OBJECT
public:
    ResultsProcessor() = default;

public slots:

    //Top Accuracies slots
    void slot_normal_generateTopAccuraciesGraphics(TopAccuraciesView *receiver,
                                                   const QSharedPointer<TopAccuraciesGraphics> &graphics);

    //Classification result slots
    static void slot_normal_loadClassificationResultData(ClassificationResultView *view, ClassificationResult *result);

    void slot_normal_generateClassificationResultGraphics(GenericGraphicsView *receiver, ClassificationResult *result);

    //Training result slots
    static void slot_normal_loadTrainingResultData(TrainingResultView *view, TrainingResult *result);

    void slot_normal_generateTrainingResultGraphics(GenericGraphicsView *receiver, TrainingResult *result);

private:
    QMultiMap<GenericGraphicsView *, GenericResultGraphics *> m_mapGraphicsByReceiver;

    void addGraphicsGenerationJob(GenericGraphicsView *receiver,
                                  const QList<QSharedPointer<GenericResultGraphics>> &graphicsList);

private slots:

    void slot_graphicsGenerated(GenericGraphicsView *receiver, GenericResultGraphics *graphics,
                                const QString &fullPath);
};

#endif // RESULTSPROCESSOR_H
