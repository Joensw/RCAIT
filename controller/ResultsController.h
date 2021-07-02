#ifndef RCAIT_RESULTSCONTROLLER_H
#define RCAIT_RESULTSCONTROLLER_H


#include <plugins/results/TrainingResult.h>
#include <model/results/ResultImagesGenerator.h>
#include <plugins/results/ClassificationResult.h>
#include <view/results/ResultsWidget.h>
#include "model/ProjectManager.h"

class ResultsController {
private:
    QList<TrainingResult> unsavedTrainingResults;
    QList<ClassificationResult> unsavedClassificationResults;
    void updateComparisonResultOverview(TrainingResult* result);

public:
    ResultsController(ResultImagesGenerator* imageGenerator, ProjectManager* manager, ResultsWidget* resultsWidget);
    void addTrainingResult(TrainingResult* result);
    void addClassificationResult(ClassificationResult* result);

    //TODO: Check if all of these are needed
public slots:
    void slot_startTrainingComparison();
    void slot_startClassificationComparison();
    void slot_saveResult();

};


#endif //RCAIT_RESULTSCONTROLLER_H
