#include "ResultsWidget.h"

ResultsWidget::ResultsWidget(QWidget *parent) {

}

QString ResultsWidget::getSelectedTrainRunIdentifier() {
    return QString();
}

QString ResultsWidget::getSelectedClassifyRunIdentifier() {
    return QString();
}

void ResultsWidget::addTrainingResult(QList<QImage> result) {

}

void ResultsWidget::addClassificationResult(QList<QImage> result) {

}

void ResultsWidget::updateComparisonResultOverview(TrainingResult *trainingResult) {

}

void ResultsWidget::setErrorMessage(QString message) {

}

void ResultsWidget::sig_saveResults() {

}

void ResultsWidget::sig_startTrainingComparison() {

}

void ResultsWidget::sig_startClassificationComparison() {

}
