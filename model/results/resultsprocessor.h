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

extern const QString TRAINING_JSON;
extern const QString CLASSIFICATION_JSON;

class ResultsProcessor : public QObject {
Q_OBJECT
public:
    ResultsProcessor() = default;

public slots:
    //Top Accuracies slots
    void slot_normal_generateTopAccuraciesGraphics(GenericGraphicsView *receiver, TopAccuraciesGraphics *graphics);

    //Classification result slots
    void slot_normal_loadClassificationResultData(ClassificationResultView* view, ClassificationResult* result);
    void slot_normal_generateClassificationResultGraphics(GenericGraphicsView *receiver, ClassificationResult* result);

    //Training result slots
    void slot_normal_loadTrainingResultData(TrainingResultView* view, TrainingResult* result);
    void slot_normal_generateTrainingResultGraphics(GenericGraphicsView *receiver, TrainingResult *result);

};

#endif // RESULTSPROCESSOR_H
