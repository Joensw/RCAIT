#include <QPushButton>
#include <QMenu>
#include "ResultsWidget.h"
#include "TrainingResultView.h"
#include "ui_resultswidget.h"

ResultsWidget::ResultsWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ResultsWidget) {
    ui->setupUi(this);
    createAddRunButton(ui->tabWidget_comparison);


    for (int i = 0; i < 3; ++i) {
        QString run = QString("Run %1").arg(i + 1);
        auto tab = new TrainingResultView(this);
        ui->tabWidget_comparison->addTab(tab, run);
        auto *action = new QAction(run, this);
        action->setCheckable(true);
        action->setChecked(true);
        menu_addRun->addAction(action);
    }
}

void ResultsWidget::createAddRunButton(QTabWidget *tabWidget) {
    auto pushButton_addResult = new QPushButton("Compare Run ...", this);
    pushButton_addResult->setFlat(true);
    pushButton_addResult->setMenu(menu_addRun);
    tabWidget->setCornerWidget(pushButton_addResult, Qt::TopRightCorner);
}

ResultsWidget::~ResultsWidget() {
    delete ui;
}

QString ResultsWidget::getSelectedTrainRunIdentifier() {
    return QString();
}

QString ResultsWidget::getSelectedClassifyRunIdentifier() {
    return QString();
}

void ResultsWidget::addTrainingResult(QList<QImage> result) {
//TODO: TrainingResult class instead of Images??
}

void ResultsWidget::addClassificationResult(QList<QImage> result) {

}

void ResultsWidget::updateComparisonResultOverview(TrainingResult *trainingResult) {

}

void ResultsWidget::setErrorMessage(QString message) {

}
