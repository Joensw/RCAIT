#include "trainingresultview.h"
#include "ui_trainingresultview.h"

TrainingResultView::TrainingResultView(SavableResultsWidget *tabWidget, QWidget *parent) :
        GenericGraphicsView(tabWidget, parent),
        ui(new Ui::TrainingResultView) {
    ui->setupUi(this);
    ui->imageGallery_mostMisclassifiedImages->setQuadraticGrid(IMAGES_GRID_SIZE);
}

void TrainingResultView::setAccuracyCurve(const QSharedPointer<QGraphicsItem> &accuracyCurveImage) {
    m_accuracyCurveImage = accuracyCurveImage;

    auto view = ui->graphicsView_accuracycurve;
    m_accuracyCurveScene.reset(new QGraphicsScene);

    m_accuracyCurveScene->addItem(&*accuracyCurveImage);
    //Jump back to main programs thread to avoid warnings
    m_accuracyCurveScene->moveToThread(this->thread());

    view->scale(ACCURACY_CURVE_SCALING_FACTOR, ACCURACY_CURVE_SCALING_FACTOR);
    view->fitInView(m_accuracyCurveScene->sceneRect(), Qt::KeepAspectRatio);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setScene(&*m_accuracyCurveScene);
}

void TrainingResultView::setConfusionMatrix(const QSharedPointer<QGraphicsItem> &matrixImage) {
    m_confusionMatrixImage = matrixImage;

    auto view = ui->graphicsView_confusionmatrix;
    m_confusionMatrixScene.reset(new QGraphicsScene);
    m_confusionMatrixScene->addItem(&*matrixImage);
    //Jump back to main programs thread to avoid warnings
    m_confusionMatrixScene->moveToThread(this->thread());

    view->scale(CONFUSIONMATRIX_SCALING_FACTOR, CONFUSIONMATRIX_SCALING_FACTOR);
    view->fitInView(m_confusionMatrixScene->sceneRect(), Qt::KeepAspectRatio);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setScene(&*m_confusionMatrixScene);
}

void TrainingResultView::setMostMisclassifiedImages(const QStringList& images) {
    auto gallery = ui->imageGallery_mostMisclassifiedImages;
    gallery->concurrentAddImages(images);
}

TrainingResultView::~TrainingResultView() {
    m_accuracyCurveImage.clear();
    m_confusionMatrixImage.clear();
    delete ui;
}

[[maybe_unused]] const QSharedPointer<QGraphicsItem> &TrainingResultView::getAccuracyCurveImage() const {
    return m_accuracyCurveImage;
}

[[maybe_unused]] const QSharedPointer<QGraphicsItem> &TrainingResultView::getConfusionMatrixImage() const {
    return m_confusionMatrixImage;
}

void TrainingResultView::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}
