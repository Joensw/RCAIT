#include "trainingresultview.h"
#include "ui_trainingresultview.h"

TrainingResultView::TrainingResultView(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TrainingResultView) {
    ui->setupUi(this);
}

void TrainingResultView::setAccuracyCurve(QGraphicsItem *accuracyCurveImage) {
    auto view = ui->graphicsView_accuracycurve;
    auto *scene = new QGraphicsScene();
    scene->addItem(accuracyCurveImage);
    //Jump back to main programs thread to avoid warnings
    scene->moveToThread(this->thread());

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
    //Jump back to main programs thread to avoid warnings
    scene->moveToThread(this->thread());

    view->scale(0.85, 0.85);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setScene(scene);
}

void TrainingResultView::setMostMisclassifiedImages(const QList<QImage>& images) {
    auto gallery = ui->imageGallery_mostMisclassifiedImages;
    gallery->concurrentAddDir(images);
}

TrainingResultView::~TrainingResultView() {
    delete ui;
}

void TrainingResultView::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}
