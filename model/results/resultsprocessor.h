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

class ResultsProcessor : public QObject{
    Q_OBJECT
public:
    ResultsProcessor();

public slots:
    //Top Accuracies slots
    void slot_normal_generateTopAccuraciesGraphics(AbstractGraphicsView *receiver);
    void slot_comparison_loadAccuracyData(const QString &runNameToCompare, TopAccuraciesView *view);
    void slot_comparison_unloadAccuracyData(const QString &runNameToCompare, TopAccuraciesView *view);

    //Classification result slots
    void slot_normal_loadClassificationData(ClassificationResultView* view, ClassificationResult* result);
    void slot_normal_generateClassificationResultGraphics(AbstractGraphicsView *receiver, ClassificationResult* result);
    void slot_comparison_loadClassificationData(const QString &runNameToCompare, ClassificationResultView *view);
    void slot_comparison_loadClassificationResultGraphics(const QString &runNameToCompare, AbstractGraphicsView *receiver);

    //Training result slots
    void slot_comparison_loadTrainingResultGraphics(const QString& runNameToCompare, TrainingResultView* view);




private:
    TopAccuraciesGraphics *m_topAccuraciesGraphics;

};

#endif // RESULTSPROCESSOR_H
