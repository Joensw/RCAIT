#ifndef RCAIT_RESULTSCONTROLLER_H
#define RCAIT_RESULTSCONTROLLER_H


#include <plugins/results/trainingresult.h>
#include <plugins/results/classificationresult.h>
#include <view/results/resultswidget.h>
#include "model/projectmanager.h"

class ResultsController {
private:
    QList<TrainingResult> unsavedTrainingResults;
    QList<ClassificationResult> unsavedClassificationResults;
    void updateComparisonResultOverview(TrainingResult* result);

public:
    ResultsController(ProjectManager *manager, ResultsWidget *resultsWidget);
    void addTrainingResult(TrainingResult* result);
    void addClassificationResult(ClassificationResult* result);

    //TODO: Check if all of these are needed
public slots:
    void slot_startTrainingComparison();
    void slot_startClassificationComparison();
    void slot_saveResult();

};


#endif //RCAIT_RESULTSCONTROLLER_H
