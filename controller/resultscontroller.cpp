#include "resultscontroller.h"

ResultsController::ResultsController(DataManager *manager, ResultsWidget *resultsWidget) {
    m_dataManager = manager;
    m_resultsWidget = resultsWidget;
    m_resultsProcessor = new ResultsProcessor();

    /*
     * Training Results
     */
    auto trainingResultsWidget = m_resultsWidget->getTrainingResultsWidget();
    // Connect 'Top Accuracies Table' related signals/slots
    connect(trainingResultsWidget->getTopAccuraciesView(), &TopAccuraciesView::sig_normal_requestTopAccuraciesGraphics,
            m_resultsProcessor,
            &ResultsProcessor::slot_normal_generateTopAccuraciesGraphics);

    //Connect 'Compare Run' related signals/slots
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_comparison_loadTrainingResultGraphics, m_resultsProcessor,
            &ResultsProcessor::slot_comparison_loadTrainingResultGraphics);
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_comparison_loadAccuracyData, m_resultsProcessor,
            &ResultsProcessor::slot_comparison_loadAccuracyData);
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_comparison_unloadAccuracyData,
            m_resultsProcessor,
            &ResultsProcessor::slot_comparison_unloadAccuracyData);

/*
 * Classification Results
 */
    auto classificationResultsWidget = m_resultsWidget->getClassificationResultsWidget();

    //Connect 'Compare Run' related signals/slots
    connect(classificationResultsWidget, &ClassificationResultsWidget::sig_comparison_loadClassificationData,
            m_resultsProcessor,
            &ResultsProcessor::slot_comparison_loadClassificationData);
    connect(classificationResultsWidget, &ClassificationResultsWidget::sig_comparison_loadClassificationResultGraphics,
            m_resultsProcessor,
            &ResultsProcessor::slot_comparison_loadClassificationResultGraphics);
    connect(classificationResultsWidget, &ClassificationResultsWidget::sig_normal_loadClassificationData,
            m_resultsProcessor,
            &ResultsProcessor::slot_normal_loadClassificationData);
    connect(classificationResultsWidget, &ClassificationResultsWidget::sig_normal_generateClassificationResultGraphics,
            m_resultsProcessor,
            &ResultsProcessor::slot_normal_generateClassificationResultGraphics);

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
//TODO Useless
}

void ResultsController::slot_saveResult() {
//TODO Move
}
