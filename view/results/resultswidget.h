#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H


#include <QWidget>
#include <results/trainingresult.h>
#include <ui_resultswidget.h>
#include "classificationresult.h"
#include "trainingresultview.h"

/**
 * @brief This widget contains all specialised result comparison widgets.
 */
class ResultsWidget : public QWidget {
Q_OBJECT

protected:
    /**
     * @brief this event is called, when a new translator is loaded or the system language is changed
     */
    void changeEvent(QEvent *) override;

public:
    /**
     * @brief Construct a new ResultsWidget.
     * @param parent QWidget parent (optional)
     */
    explicit ResultsWidget(QWidget *parent = nullptr);

    /**
     * @brief Destructor for this class.
     */
    ~ResultsWidget() override;

    /**
     * @brief Add training result to the corresponding TrainingResultsWidget
     * @param result result to be added
     */
    void addTrainingResult(TrainingResult *result);

    /**
     * @brief Add training result to the corresponding ClassificationResultsWidget
     * @param result result to be added
     */
    void addClassificationResult(ClassificationResult *result);

    /**
     * @brief Update the results folder of the specialised result widgets
     */
    void updateResultFolderPaths();

    /*
     * Get specialized
     */
    /**
     * @brief Get the training results widget
     * @return pointer to training results widget
     */
    TrainingResultsWidget *getTrainingResultsWidget();

    /**
     * @brief Get the classification results widget
     * @return pointer to classification results widget
     */
    ClassificationResultsWidget *getClassificationResultsWidget();

private:
    Ui::ResultsWidget *ui;
    TrainingResultsWidget *m_trainingResultsWidget;
    ClassificationResultsWidget *m_classificationResultsWidget;

    ProjectManager *m_projectManager;
};


#endif //RESULTSWIDGET_H
