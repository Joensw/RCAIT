
#include "resultscontroller.h"

ResultsController::ResultsController(DataManager *manager, ResultsWidget *resultsWidget) {
    m_dataManager = manager;
    m_resultsWidget = resultsWidget;

    //Connect ResultsWidget to ResultsController
    connect(resultsWidget, &ResultsWidget::sig_saveResults, this, &ResultsController::slot_saveResult);

}

void ResultsController::addTrainingResult(TrainingResult *result) {
    m_resultsWidget->addTrainingResult(result);
}

void ResultsController::addClassificationResult(ClassificationResult *result) {
    m_resultsWidget->addClassificationResult(result);
}

void ResultsController::updateComparisonResultOverview(TrainingResult *result) {
//TODO Fill
}

void ResultsController::slot_saveResult() {
//TODO Fill
}
