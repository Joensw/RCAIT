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

public slots:

    void slot_projectPathUpdated();
    void slot_addTrainingResult(TrainingResult *result);
    void slot_addClassificationResult(ClassificationResult *result);

private:
    DataManager *m_dataManager;
    ResultsWidget *m_resultsWidget;
    ResultsProcessor *m_resultsProcessor;
    ResultsImporter *m_resultsImporter;
    ResultsExporter *m_resultsExporter;
};


#endif //RESULTSCONTROLLER_H
