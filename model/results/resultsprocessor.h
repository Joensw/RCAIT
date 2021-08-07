#ifndef RESULTSPROCESSOR_H
#define RESULTSPROCESSOR_H


#include <QString>
#include <QMap>
#include <QRandomGenerator>
#include <trainingresultview.h>
#include <topaccuraciesview.h>
#include <classificationresultview.h>
#include "topaccuraciesgraphics.h"
#include "classificationgraphics.h"
#include "trainingresult.h"
#include "classificationresult.h"

class ResultsProcessor : public QObject{
    Q_OBJECT
public:
    ResultsProcessor();

public slots:
    //Top Accuracies slots
    void slot_normal_generateTopAccuraciesGraphics(AbstractGraphicsView *receiver);
    void slot_comparison_loadAccuracyData(TopAccuraciesView *view, const QString &runNameToCompare);
    void slot_comparison_unloadAccuracyData(TopAccuraciesView *view, const QString &runNameToCompare);

    //Classification result slots
    void slot_normal_loadClassificationResultData(ClassificationResultView* view, ClassificationResult* result);
    void slot_normal_generateClassificationResultGraphics(AbstractGraphicsView *receiver, ClassificationResult* result);
    void slot_comparison_loadClassificationResultData(ClassificationResultView *view, const QString &runNameToCompare);
    void slot_comparison_loadClassificationResultGraphics(AbstractGraphicsView *receiver, const QString &runNameToCompare);

    //Training result slots
    void slot_normal_loadTrainingResultData(TrainingResultView* view, TrainingResult* result);
    void slot_normal_generateTrainingResultGraphics(AbstractGraphicsView *receiver, TrainingResult *result);
    void slot_comparison_loadTrainingResultData(TrainingResultView *view, const QString &runNameToCompare);
    void slot_comparison_loadTrainingResultGraphics(AbstractGraphicsView *receiver, const QString &runNameToCompare);

private:
    TopAccuraciesGraphics *m_topAccuraciesGraphics;

    static void loadGraphicsInView(AbstractGraphicsView *receiver, const QString &resultsFolder, const QString &baseDir);
};

#endif // RESULTSPROCESSOR_H
