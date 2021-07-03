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

    //Less wasted space on the sides
    chart->setBackgroundRoundness(0);
    chart->setContentsMargins(-20, -15, -10, -40);

    //Visual configuration of QLineSeries
    auto pen = trainSeries->pen();
    pen.setWidth(3);
    pen.setColor("royal blue");
    trainSeries->setName("Training");
    trainSeries->setPen(pen);

    pen = validationSeries->pen();
    pen.setWidth(3);
    pen.setColor("orange");
    validationSeries->setName("Validation");
    validationSeries->setPen(pen);

    //Legend placement
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setMarkerShape(QLegend::MarkerShapeCircle);
    chart->legend()->show();

    chart->addSeries(trainSeries);
    chart->addSeries(validationSeries);

    //Axis corrections
    auto *axisY = new QValueAxis();
    axisY->setLabelFormat("%.2f");
    chart->addAxis(axisY, Qt::AlignLeft);

    trainSeries->attachAxis(axisY);
    validationSeries->attachAxis(axisY);

    auto *axisX = new QValueAxis();
    axisX->setLabelFormat("%.0f");
    chart->addAxis(axisX, Qt::AlignBottom);

    trainSeries->attachAxis(axisX);
    validationSeries->attachAxis(axisX);

    axisX->applyNiceNumbers();
    axisY->setMin(0);

    //Rendering options
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
    view->scale(0.8,0.8);
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
