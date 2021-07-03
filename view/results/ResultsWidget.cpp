#include <QPushButton>
#include <QMenu>
#include <QSplineSeries>
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
        createTrainingResultTab(run);
        auto *action = new QAction(run, this);
        action->setCheckable(true);
        action->setChecked(true);
        menu_addRun->addAction(action);
    }
}

void ResultsWidget::createAddRunButton(QTabWidget *tabWidget) {
    pushButton_addResult->setText("Compare ...");
    const auto icon = QIcon(":/Resources/UISymbols/UI_Add_Result_Comparison_Icon.svg");
    pushButton_addResult->setIcon(icon);
    pushButton_addResult->setFlat(true);
    pushButton_addResult->setMenu(menu_addRun);
    tabWidget->setCornerWidget(pushButton_addResult, Qt::TopRightCorner);
}

QString ResultsWidget::getSelectedTrainRunIdentifier() {
    return QString();
}

QString ResultsWidget::getSelectedClassifyRunIdentifier() {
    return QString();
}

void ResultsWidget::addTrainingResult(TrainingResult *result) {
    QString name = "Run";
    auto data_lossCurve = result->getLossCurve();
    auto labels_confusionMatrix = result->getClassLabels();
    auto data_confusionMatrix = result->getConfusionMatrix();
    auto data_mostMisclassifiedImages = result->getMostMisclassifiedImages();

    auto tab = createTrainingResultTab(name);

    //Parse Loss curve
    //TODO: Extract method
    auto *trainSeries = new QSplineSeries();
    auto *validationSeries = new QSplineSeries();
    trainSeries->setName("train");
    validationSeries->setName("validation");
    trainSeries->setColor("blue");
    validationSeries->setColor("orange");

    for (const auto &xValue : data_lossCurve.keys()){
        QPair<double,double> pair = data_lossCurve.value(xValue);
        auto yTrain = pair.first;
        auto yValidation = pair.second;
        auto trainPoint = QPointF(xValue,yTrain);
        auto validationPoint = QPointF(xValue,yValidation);

        *trainSeries << trainPoint;
        *validationSeries << validationPoint;
    }

//Parse Confusion Matrix
//TODO: Call python script to generate CM from Table

//TODO: (Adrians Help) Pass QList<QImages>


    tab->setLossCurve(trainSeries,validationSeries);
    tab->setConfusionMatrix(nullptr);
    tab->setMostMisclassifiedImages(QList<QImage>());
}

void ResultsWidget::addClassificationResult(QList<QImage> result) {
//TODO Adapt type to something better
}

void ResultsWidget::updateComparisonResultOverview(TrainingResult *trainingResult) {
//TODO: Clarify if useless
}

void ResultsWidget::setErrorMessage(QString message) {

}

ResultsWidget::~ResultsWidget() {
    delete ui;
}

TrainingResultView * ResultsWidget::createTrainingResultTab(const QString& tabName) {
    auto tab = new TrainingResultView(this);
    ui->tabWidget_comparison->addTab(tab, tabName);
    return tab;
}
