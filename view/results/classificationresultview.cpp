#include "classificationresultview.h"
#include "ui_classificationresultview.h"

ClassificationResultView::ClassificationResultView(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ClassificationResultView) {
    ui->setupUi(this);

    QTableWidget *table = ui->tableWidget_classificationresult;

    //Stretch table headers to fill the space available
    QHeaderView *h_header = table->horizontalHeader();
    QHeaderView *v_header = table->verticalHeader();
    h_header->setSectionResizeMode(QHeaderView::Stretch);
    v_header->setSectionResizeMode(QHeaderView::Fixed);

    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"Accuracy", "Label"});

    configure_updateGraphicsButton();

    //Internal signals/slots
    connect(m_pushButton_updateGraphics, &QAbstractButton::pressed, this,
            &ClassificationResultView::slot_pushButton_updateGraphics_pressed);

}

void ClassificationResultView::setClassificationData(const QList<QPair<QString, QStringList>>& data){
    auto table = ui->tableWidget_classificationresult;
    for (const auto &[key,valuesList] : data){
        table->addTableRow(key,valuesList);
    }
}

void ClassificationResultView::setClassificationGraphics(QGraphicsItem *classificationGraphicsImage) {
    auto view = ui->graphicsView_classificationresult;
    auto *scene = new QGraphicsScene();
    scene->addItem(classificationGraphicsImage);
    //Jump back to main programs thread to avoid warnings
    scene->moveToThread(this->thread());

    view->scale(2, 2);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    view->setScene(scene);
}

void ClassificationResultView::slot_pushButton_updateGraphics_pressed() {
    emit sig_requestClassificationResultGraphics(this);
}

void ClassificationResultView::configure_updateGraphicsButton() {
    const auto icon = QIcon(":/Resources/UISymbols/UI_Reload_Icon.svg");
    m_pushButton_updateGraphics = ui->tableWidget_classificationresult->getCornerButton();
    if (m_pushButton_updateGraphics) {
        m_pushButton_updateGraphics->setIcon(icon);
    }
}


void ClassificationResultView::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is send if a translator is loaded
        retranslateUi();
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
    if (m_pushButton_updateGraphics)
        m_pushButton_updateGraphics->setToolTip("Update graphics...");
}

ClassificationResultView::~ClassificationResultView() {
    delete ui;
}
