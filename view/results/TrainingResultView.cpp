#include "TrainingResultView.h"

#include <utility>
#include <QValueAxis>
#include "ui_trainingresultview.h"

TrainingResultView::TrainingResultView(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TrainingResultView) {
    ui->setupUi(this);
}

TrainingResultView::TrainingResultView(QWidget *parent, QLineSeries *trainSeries, QLineSeries *validationSeries,
                                       QGraphicsItem *matrixImage, QList<QImage> images) : TrainingResultView(parent) {
    setConfusionMatrix(matrixImage);
    setLossCurve(trainSeries, validationSeries);
    setMostMisclassifiedImages(std::move(images));
}

void TrainingResultView::setLossCurve(QLineSeries *trainSeries, QLineSeries *validationSeries) {
    auto view = ui->graphicsView_losscurve;
    QChart *chart = view->chart();
    chart->setBackgroundRoundness(0);

    chart->legend()->hide();
    chart->addSeries(trainSeries);
    chart->addSeries(validationSeries);

    auto *axisY = new QValueAxis();
    axisY->setLabelFormat("%.0f");
    chart->addAxis(axisY, Qt::AlignLeft);
    axisY->applyNiceNumbers();
    axisY->setMin(0);

    auto *axisX = new QValueAxis();
    axisX->setLabelFormat("%.0f");
    chart->addAxis(axisX, Qt::AlignBottom);
    axisX->applyNiceNumbers();

    trainSeries->attachAxis(axisY);
    validationSeries->attachAxis(axisY);
    trainSeries->attachAxis(axisX);
    validationSeries->attachAxis(axisX);

    view->setRenderHint(QPainter::Antialiasing);
    chart->setAnimationOptions(QChart::AllAnimations);
}

void TrainingResultView::setConfusionMatrix(QGraphicsItem *matrixImage) {
    auto view = ui->graphicsView_confusionmatrix;
    auto *scene = new QGraphicsScene();
    scene->addItem(matrixImage);

    auto vWidth = view->width();
    auto vHeight = view->height();
    auto sWidth = scene->width();
    auto sHeight = scene->height();
    view->scale(vWidth / sWidth, vHeight / sHeight);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setScene(scene);
}

void TrainingResultView::setMostMisclassifiedImages(QList<QImage> images) {
//TODO Access staticlist or imagegallery
}

TrainingResultView::~TrainingResultView() {
    delete ui;
}
