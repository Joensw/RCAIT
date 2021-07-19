#ifndef RESULTSCONTROLLER_H
#define RESULTSCONTROLLER_H


#include <trainingresult.h>
#include <classificationresult.h>
#include <resultswidget.h>
#include <resultsprocessor.h>
#include <datamanager.h>

class ResultsController : public QObject{

    Q_OBJECT
public:
    ResultsController(DataManager *manager, ResultsWidget *resultsWidget);
    void addTrainingResult(TrainingResult* result);
    void addClassificationResult(ClassificationResult* result);

public slots:
    void slot_saveResult();

private:
    DataManager *m_dataManager;
    ResultsWidget *m_resultsWidget;
    ResultsProcessor *m_resultsProcessor;
    //TODO ??
    QList<TrainingResult> m_unsavedTrainingResults;
    QList<ClassificationResult> m_unsavedClassificationResults;
    void updateComparisonResultOverview(TrainingResult* result);
};


#endif //RESULTSCONTROLLER_H
