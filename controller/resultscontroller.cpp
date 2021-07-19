#include "resultscontroller.h"

ResultsController::ResultsController(DataManager *manager, ResultsWidget *resultsWidget) {
    m_dataManager = manager;
    m_resultsWidget = resultsWidget;
    m_resultsProcessor = new ResultsProcessor();

    // Connect 'Top Accuracies Table' related signals/slots
    connect(m_resultsWidget->getTopAccuraciesView(),&TopAccuraciesView::sig_requestTopAccuraciesGraphics, m_resultsProcessor,
            &ResultsProcessor::slot_generateTopAccuraciesGraphics);
    connect(m_resultsWidget->getTopAccuraciesView(),&TopAccuraciesView::sig_accuraciesTable_rowAdded, m_resultsProcessor,
            &ResultsProcessor::slot_addedRow_topAccuraciesTable);
    connect(m_resultsWidget->getTopAccuraciesView(),&TopAccuraciesView::sig_accuraciesTable_rowRemoved, m_resultsProcessor,
            &ResultsProcessor::slot_removedRow_topAccuraciesTable);


    //Connect ResultsWidget to ResultsController
    connect(m_resultsWidget, &ResultsWidget::sig_saveResults, this, &ResultsController::slot_saveResult);

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
