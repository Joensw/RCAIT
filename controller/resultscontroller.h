#ifndef RESULTSCONTROLLER_H
#define RESULTSCONTROLLER_H


#include <trainingresult.h>
#include <classificationresult.h>
#include <resultswidget.h>
#include <resultsprocessor.h>
#include <datamanager.h>
#include <resultsimporter.h>
#include <resultsexporter.h>
#include <trainingresultswidget.h>
#include <classificationresultswidget.h>

class ResultsController : public QObject {

Q_OBJECT
public:
    ResultsController(DataManager *manager, ResultsWidget *resultsWidget);

    void addTrainingResult(TrainingResult *result);

    void addClassificationResult(ClassificationResult *result);

    void slot_projectPathUpdated();

public slots:

    void slot_saveResult();

private:
    DataManager *m_dataManager;
    ResultsWidget *m_resultsWidget;
    ResultsProcessor *m_resultsProcessor;
    ResultsImporter *m_resultsImporter;
    ResultsExporter *m_resultsExporter;

    //TODO ??
    QList<TrainingResult> m_unsavedTrainingResults;
    QList<ClassificationResult> m_unsavedClassificationResults;

    void updateComparisonResultOverview(TrainingResult *result);
};


#endif //RESULTSCONTROLLER_H
