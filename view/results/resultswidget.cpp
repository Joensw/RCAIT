#include "resultswidget.h"
#include "ui_resultswidget.h"
#include "projectmanager.h"

ResultsWidget::ResultsWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ResultsWidget) {

    ui->setupUi(this);

    //Setup widget variables
    m_trainingResultsWidget = ui->tab_trainingResults;
    m_classificationResultsWidget = ui->tab_classificationResults;

    //Connect signals & slots
    connect(this, &ResultsWidget::sig_updateResultFolderPaths, m_trainingResultsWidget,
            &TrainingResultsWidget::slot_updateResultFolderPaths);
    connect(this, &ResultsWidget::sig_updateResultFolderPaths, m_classificationResultsWidget,
            &ClassificationResultsWidget::slot_updateResultFolderPaths);

}

void ResultsWidget::addTrainingResult(TrainingResult *result) {
    m_trainingResultsWidget->addTrainingResult(result);
}

void ResultsWidget::addClassificationResult(ClassificationResult *result) {
    m_classificationResultsWidget->addClassificationResult(result);
}

ResultsWidget::~ResultsWidget() {
    delete ui;
}

void ResultsWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

TrainingResultsWidget *ResultsWidget::getTrainingResultsWidget() {
    return m_trainingResultsWidget;
}

ClassificationResultsWidget *ResultsWidget::getClassificationResultsWidget() {
    return m_classificationResultsWidget;
}

void ResultsWidget::updateResultFolderPaths() {
    ProjectManager *pm = &ProjectManager::getInstance();
    auto trainingPath = pm->getTrainingResultsDir();
    auto classificationPath = pm->getClassificationResultsDir();
    emit sig_updateResultFolderPaths(trainingPath, classificationPath);
}
