#include "resultscontroller.h"

ResultsController::ResultsController(DataManager *manager, ResultsWidget *resultsWidget) {
    m_dataManager = manager;
    m_resultsWidget = resultsWidget;
    m_resultsProcessor = new ResultsProcessor();

    //Training Results
    auto trainingResultsWidget = m_resultsWidget->getTrainingResultsWidget();
    // Connect 'Top Accuracies Table' related signals/slots
    connect(trainingResultsWidget->getTopAccuraciesView(),&TopAccuraciesView::sig_requestTopAccuraciesGraphics, m_resultsProcessor,
            &ResultsProcessor::slot_generateTopAccuraciesGraphics);
    connect(trainingResultsWidget->getTopAccuraciesView(),&TopAccuraciesView::sig_accuraciesTable_rowAdded, m_resultsProcessor,
            &ResultsProcessor::slot_addedRow_topAccuraciesTable);
    connect(trainingResultsWidget->getTopAccuraciesView(),&TopAccuraciesView::sig_accuraciesTable_rowRemoved, m_resultsProcessor,
            &ResultsProcessor::slot_removedRow_topAccuraciesTable);

    //Connect 'Compare Run' related signals/slots
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_loadTrainingImagesToCompare, m_resultsProcessor,
            &ResultsProcessor::slot_loadTrainingImagesToCompare);
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_loadAccuracyDataToCompare, m_resultsProcessor,
            &ResultsProcessor::slot_loadAccuracyDataToCompare);

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
