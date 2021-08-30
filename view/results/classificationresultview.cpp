#include <mapadapt.h>
#include <QScroller>
#include <QScrollBar>
#include "classificationresultview.h"
#include "ui_classificationresultview.h"

ClassificationResultView::ClassificationResultView(SavableResultsWidget *tabWidget, QWidget *parent) :
        GenericGraphicsView(tabWidget, parent),
        ui(new Ui::ClassificationResultView) {
    ui->setupUi(this);

    auto *table = ui->tableWidget_classificationresult;
    table->setColumnCount(2);

    // Add full touch compliance
    QScroller::grabGesture(ui->graphicsView_classificationresult, QScroller::TouchGesture);
    QScroller::grabGesture(ui->tableWidget_classificationresult, QScroller::TouchGesture);

    //Stretch table headers to fill the space available
    QHeaderView *h_header = table->horizontalHeader();
    QHeaderView *v_header = table->verticalHeader();
    h_header->setStretchLastSection(true);
    v_header->setSectionResizeMode(QHeaderView::Fixed);

    table->setCornerButtonEnabled(false);

    retranslateUi();
}

void ClassificationResultView::setClassificationData(const QMap<int, QStringList> &data) {
    auto table = ui->tableWidget_classificationresult;
    for (const auto &[key, valuesList] : MapAdapt(data)) {
        table->addTableRow(QString::number(key), valuesList);
    }
}

void ClassificationResultView::setClassificationGraphics(
        const QSharedPointer<QGraphicsItem> &classificationGraphicsImage) {
    m_classificationGraphics = classificationGraphicsImage;

    auto view = ui->graphicsView_classificationresult;
    auto *scene = new QGraphicsScene();
    scene->addItem(&*classificationGraphicsImage);
    //Jump back to main programs thread to avoid warnings
    scene->moveToThread(this->thread());

    view->scale(0.6, 0.6);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    view->setScene(scene);

    //Scroll up to the beginning of the scene on startup
    view->verticalScrollBar()->setValue(1);
}

[[maybe_unused]] [[maybe_unused]] const QSharedPointer<QGraphicsItem> &ClassificationResultView::getClassificationGraphics() const {
    return m_classificationGraphics;
}

ClassificationResultView::~ClassificationResultView() {
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
    table->setHorizontalHeaderLabels({tr("Confidence"), tr("Label")});
}
