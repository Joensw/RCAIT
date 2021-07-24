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
    void slot_generateTopAccuraciesGraphics(AbstractGraphicsView *receiver);

    void slot_generateClassificationResultGraphics(AbstractGraphicsView *receiver);

    void slot_addedRow_topAccuraciesTable(const QString &identifier, double top1, double top5);

    void slot_removedRow_topAccuraciesTable(const QString &identifier);

    void slot_loadTrainingImagesToCompare(const QString& runNameToCompare, TrainingResultView* view);

    void slot_loadAccuracyDataToCompare(const QString &runNameToCompare, TopAccuraciesView *view);

    void slot_loadClassificationDataToCompare(const QString &runNameToCompare, ClassificationResultView *view);

private:
    TopAccuraciesGraphics *m_topAccuraciesGraphics;
    QMap<ClassificationResultView*, ClassificationGraphics*> m_classificationGraphicsMap;

};

#endif // RESULTSPROCESSOR_H
