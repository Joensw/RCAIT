#include "classificationresultview.h"
#include "ui_classificationresultview.h"

ClassificationResultView::ClassificationResultView(SavableResultsWidget *tabWidget, QWidget *parent) :
        GenericGraphicsView(tabWidget, parent),
        ui(new Ui::ClassificationResultView) {
    ui->setupUi(this);

    auto *table = ui->tableWidget_classificationresult;
    table->setColumnCount(TABLE_COLUMN_CODE);

    // Add full touch compliance
    QScroller::grabGesture(ui->graphicsView_classificationresult, QScroller::TouchGesture);
    QScroller::grabGesture(ui->tableWidget_classificationresult, QScroller::TouchGesture);

    //Stretch table headers to fill the space available
    QHeaderView *h_header = table->horizontalHeader();
    QHeaderView *v_header = table->verticalHeader();
    h_header->setStretchLastSection(true);
    v_header->setSectionResizeMode(QHeaderView::Fixed);
    h_header->setSectionResizeMode(QHeaderView::ResizeToContents);
    v_header->setDefaultAlignment(Qt::AlignRight | Qt::AlignVCenter);

    table->setCornerButtonEnabled(false);

    retranslateUi();
}

void ClassificationResultView::setClassificationData(const QMap<int, QStringList> &data) {
    auto table = ui->tableWidget_classificationresult;
    for (const auto &[key, valuesList]: MapAdapt(data)) {
        table->addTableRow(QString::number(key) % " ", valuesList);
    }
}

void ClassificationResultView::setClassificationGraphics(
        const QSharedPointer<QGraphicsItem> &classificationGraphicsImage) {
    m_classificationGraphics = classificationGraphicsImage;

    auto view = ui->graphicsView_classificationresult;
    m_classificationScene.reset(new QGraphicsScene);
    m_classificationScene->addItem(&*classificationGraphicsImage);
    //Jump back to main programs thread to avoid warnings
    m_classificationScene->moveToThread(this->thread());

    view->scale(CLASSIFICATION_GRAPHICS_SCALING_FACTOR, CLASSIFICATION_GRAPHICS_SCALING_FACTOR);
    view->fitInView(m_classificationScene->sceneRect(), Qt::KeepAspectRatio);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    view->setScene(&*m_classificationScene);

    //Scroll up to the beginning of the scene on startup
    view->verticalScrollBar()->setValue(1);
}

[[maybe_unused]] const QSharedPointer<QGraphicsItem> &ClassificationResultView::getClassificationGraphics() const {
    return m_classificationGraphics;
}

ClassificationResultView::~ClassificationResultView() {
    m_classificationGraphics.clear();
    delete ui;
}

void ClassificationResultView::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        retranslateUi();
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

/**
 * Translate and set all the strings which
 * were not created in the UI builder
 */
void ClassificationResultView::retranslateUi() {
    auto *table = ui->tableWidget_classificationresult;
    table->setHorizontalHeaderLabels({tr(CONFIDENCE_HEADER), tr(LABEL_HEADER)});
}
