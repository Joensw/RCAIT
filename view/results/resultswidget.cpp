#include "resultswidget.h"
#include "ui_resultswidget.h"


ResultsWidget::ResultsWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ResultsWidget),
        m_projectManager(&ProjectManager::getInstance()) {

    ui->setupUi(this);

    //Setup widget variables
    m_trainingResultsWidget = ui->tab_trainingResults;
    m_classificationResultsWidget = ui->tab_classificationResults;

    //Start at first tab
    ui->tabWidget_mode->setCurrentIndex(0);
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
    auto trainingPath = m_projectManager->getTrainingResultsDir();
    auto classificationPath = m_projectManager->getClassificationResultsDir();

    m_trainingResultsWidget->updateResultFolderPath(trainingPath);
    m_classificationResultsWidget->updateResultFolderPath(classificationPath);
}

QTabWidget *ResultsWidget::getTabWidget()
{
    return ui->tabWidget_mode;
}
