#ifndef RESULTSPROCESSOR_H
#define RESULTSPROCESSOR_H


#include "topaccuraciesgraphics.h"
#include <QString>
#include <QMap>
#include <trainingresultview.h>

class ResultsProcessor : public QObject{
    Q_OBJECT
public:
    ResultsProcessor();

public slots:
    void slot_generateTopAccuraciesGraphics(AbstractGraphicsView *receiver);

    void slot_addedRow_topAccuraciesTable(const QString &identifier, double top1, double top5);

    void slot_removedRow_topAccuraciesTable(const QString &identifier);

    void slot_loadTrainingDataToCompare(const QString& runNameToCompare, TrainingResultView* view);

private:
    TopAccuraciesGraphics *m_topAccuraciesGraphics;

};

#endif // RESULTSPROCESSOR_H
