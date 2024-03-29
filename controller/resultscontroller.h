/**
 * @file resultscontroller.h
 *
 * @brief connects the logic of the results processing and handling with the visual user interface
 *
 * @author Paul Schaarschmidt
 */
#ifndef RESULTSCONTROLLER_H
#define RESULTSCONTROLLER_H

#include <resultsexporter.h>
#include <trainingresult.h>
#include <classificationresult.h>
#include <resultswidget.h>
#include <resultsprocessor.h>
#include <datamanager.h>
#include <resultsimporter.h>
#include <resultsexporter.h>
#include <trainingresultswidget.h>
#include <classificationresultswidget.h>

/**
 * @brief The ResultsController class mediates between the results logic and UI.
*/
class ResultsController final : public QObject {

Q_OBJECT
public:
    /**
     * @brief Constructs a ResultsController
     * @param manager source of general information.
     * @param resultsWidget UI component to display information
     */
    ResultsController(DataManager *manager, ResultsWidget *resultsWidget);

    /**
     * @brief operator = deleted assignment operator
     * @return
     */
    ResultsController &operator=(const ResultsController &) = delete;

public slots:

    /**
     * @brief Gets called when the project path has changed.
     * This notifies all specialised result widgets with the new folder path
     * to load/save results from/to.
     */
    void slot_projectPathUpdated();

    /**
     * @brief Adds a new TrainingResult to the corresponding specialised widget
     * @param result result to be added
     */
    void slot_addTrainingResult(const QPointer<TrainingResult> &result);

    /**
     * @brief Adds a new ClassificationResult to the corresponding specialised widget
     * @param result result to be added
     */
    void slot_addClassificationResult(const QPointer<ClassificationResult> &result);

private:
    DataManager *m_dataManager;
    ResultsWidget *m_resultsWidget;
    ResultsProcessor m_resultsProcessor;
    ResultsImporter m_resultsImporter;
    ResultsExporter m_resultsExporter;
};


#endif //RESULTSCONTROLLER_H
