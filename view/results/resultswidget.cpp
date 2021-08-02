#include <QPushButton>
#include <QMenu>
#include <QRandomGenerator>
#include "resultswidget.h"
#include "ui_resultswidget.h"
#include "confusionmatrix.h"
#include "projectmanager.h"

ResultsWidget::ResultsWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ResultsWidget) {

    ui->setupUi(this);

    //Setup widget variables
    m_trainingResultsWidget = ui->tab_trainingResults;
    m_classificationResultsWidget = ui->tab_classificationResults;
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