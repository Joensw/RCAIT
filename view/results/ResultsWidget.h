#ifndef RCAIT_RESULTSWIDGET_H
#define RCAIT_RESULTSWIDGET_H


#include <QWidget>
#include <results/TrainingResult.h>

class ResultsWidget {
public:
    ResultsWidget(QWidget* parent);
    QString getSelectedTrainRunIdentifier();
    QString getSelectedClassifyRunIdentifier();
    //Todo: These will probably not just be QImages!
    void addTrainingResult(QList<QImage> result);
    void addClassificationResult(QList<QImage> result);
    void updateComparisonResultOverview(TrainingResult* trainingResult);
    //Todo: Weird
    void setErrorMessage(QString message);

    signals:
    void sig_saveResults();
    //Todo: Check if these are needed
    void sig_startTrainingComparison();
    void sig_startClassificationComparison();
};


#endif //RCAIT_RESULTSWIDGET_H
