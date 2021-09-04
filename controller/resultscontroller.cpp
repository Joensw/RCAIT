#include <resultsexporter.h>
#include "resultscontroller.h"

ResultsController::ResultsController(DataManager *manager, ResultsWidget *resultsWidget)
        : m_dataManager(manager),
          m_resultsWidget(resultsWidget) {

/*
 * Training Results
 */
    auto trainingResultsWidget = m_resultsWidget->getTrainingResultsWidget();

    /**
     * Import functions
     */
    //Connect 'Compare Run' related signals/slots
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_comparison_loadTrainingResultData,
            &m_resultsImporter,
            &ResultsImporter::slot_comparison_loadTrainingResultData);
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_comparison_loadTrainingResultGraphics,
            &m_resultsImporter,
            &ResultsImporter::slot_comparison_loadTrainingResultGraphics);
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_comparison_loadAccuracyData,
            &m_resultsImporter,
            &ResultsImporter::slot_comparison_loadAccuracyData);
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_comparison_unloadAccuracyData,
            &m_resultsImporter,
            &ResultsImporter::slot_comparison_unloadAccuracyData);

    /**
     * Processing functions
     */
    //Connect signals/slots related to showing training results
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_normal_generateTrainingResultGraphics,
            &m_resultsProcessor,
            &ResultsProcessor::slot_normal_generateTrainingResultGraphics);
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_normal_loadTrainingResultData,
            &m_resultsProcessor,
            &ResultsProcessor::slot_normal_loadTrainingResultData);
    connect(&m_resultsImporter, &ResultsImporter::sig_normal_loadTrainingResultData,
            &m_resultsProcessor,
            &ResultsProcessor::slot_normal_loadTrainingResultData);

    // Connect 'Top Accuracies Table' related signals/slots
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_normal_requestTopAccuraciesGraphics,
            &m_resultsProcessor,
            &ResultsProcessor::slot_normal_generateTopAccuraciesGraphics);

    /**
     * Export functions
     */
    //Connect signals/slots related to saving training results
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_save_TrainingResult,
            &m_resultsExporter,
            &ResultsExporter::slot_save_TrainingResult);
    //Connect signals/slots related to saving top accuracies
    connect(trainingResultsWidget, &TrainingResultsWidget::sig_save_TopAccuracies,
            &m_resultsExporter,
            &ResultsExporter::slot_save_TopAccuracies);

/*
 * Classification Results
 */
    auto classificationResultsWidget = m_resultsWidget->getClassificationResultsWidget();

    /**
     *Import functions
     */
    //Connect 'Compare Run' related signals/slots
    connect(classificationResultsWidget, &ClassificationResultsWidget::sig_comparison_loadClassificationResultData,
            &m_resultsImporter,
            &ResultsImporter::slot_comparison_loadClassificationResultData);
    connect(classificationResultsWidget, &ClassificationResultsWidget::sig_comparison_loadClassificationResultGraphics,
            &m_resultsImporter,
            &ResultsImporter::slot_comparison_loadClassificationResultGraphics);

    //Connect signals/slots related to showing classification results
    connect(&m_resultsImporter, &ResultsImporter::sig_normal_loadClassificationResultData,
            &m_resultsProcessor,
            &ResultsProcessor::slot_normal_loadClassificationResultData);

    /**
     * Processing functions
     */
    connect(classificationResultsWidget, &ClassificationResultsWidget::sig_normal_loadClassificationResultData,
            &m_resultsProcessor,
            &ResultsProcessor::slot_normal_loadClassificationResultData);
    connect(classificationResultsWidget, &ClassificationResultsWidget::sig_normal_generateClassificationResultGraphics,
            &m_resultsProcessor,
            &ResultsProcessor::slot_normal_generateClassificationResultGraphics);

    /**
     * Export functions
     */
    //Connect signals/slots related to saving classification results
    connect(classificationResultsWidget, &ClassificationResultsWidget::sig_save_ClassificationResult,
            &m_resultsExporter,
            &ResultsExporter::slot_save_ClassificationResult);
}

void ResultsController::slot_projectPathUpdated() {
    m_resultsWidget->updateResultFolderPaths();
    m_resultsImporter.updateResultFolderPaths();
    m_resultsExporter.updateResultFolderPaths();
}

void ResultsController::slot_addTrainingResult(TrainingResult *result) {
    m_resultsWidget->addTrainingResult(result);
}

void ResultsController::slot_addClassificationResult(ClassificationResult *result) {
    m_resultsWidget->addClassificationResult(result);
}
