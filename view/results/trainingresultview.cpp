#include "trainingresultview.h"

#include <utility>
#include "ui_trainingresultview.h"

TrainingResultView::TrainingResultView(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TrainingResultView) {
    ui->setupUi(this);
}

TrainingResultView::TrainingResultView(QWidget *parent, QGraphicsItem *lossCurveImage, QGraphicsItem *matrixImage,
                                       QList<QImage> images) : TrainingResultView(parent) {
    setConfusionMatrix(matrixImage);
    setLossCurve(lossCurveImage);
    setMostMisclassifiedImages(std::move(images));
}

void TrainingResultView::setLossCurve(QGraphicsItem *lossCurveImage) {
    auto view = ui->graphicsView_losscurve;
    auto *scene = new QGraphicsScene();
    scene->addItem(lossCurveImage);

    view->scale(0.9, 0.9);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setScene(scene);
}

void TrainingResultView::setConfusionMatrix(QGraphicsItem *matrixImage) {
    auto view = ui->graphicsView_confusionmatrix;
    auto *scene = new QGraphicsScene();
    scene->addItem(matrixImage);

    view->scale(0.85, 0.85);
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
