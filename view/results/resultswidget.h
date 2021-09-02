#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H


#include <QWidget>
#include <results/trainingresult.h>
#include <ui_resultswidget.h>
#include "classificationresult.h"
#include "trainingresultview.h"


class ResultsWidget : public QWidget {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit ResultsWidget(QWidget *parent = nullptr);

    ~ResultsWidget();

    void addTrainingResult(TrainingResult *result);

    void addClassificationResult(ClassificationResult *result);

    void updateResultFolderPaths();

    TrainingResultsWidget* getTrainingResultsWidget();

    ClassificationResultsWidget* getClassificationResultsWidget();

signals:

    void sig_saveResults();

private:
    Ui::ResultsWidget *ui;
    TrainingResultsWidget* m_trainingResultsWidget;
    ClassificationResultsWidget* m_classificationResultsWidget;

    ProjectManager *m_projectManager;
};


#endif //RESULTSWIDGET_H
