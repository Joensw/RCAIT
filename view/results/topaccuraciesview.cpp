#include "topaccuraciesview.h"
#include "ui_topaccuraciesview.h"

TopAccuraciesView::TopAccuraciesView(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TopAccuraciesView) {
    ui->setupUi(this);

    QTableWidget *table = ui->tableWidget_topAccuracies;

    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"Top 1%", "Top5%"});
    //Stretch table headers to fill the space available
    QHeaderView *h_header = table->horizontalHeader();
    QHeaderView *v_header = table->verticalHeader();
    h_header->setSectionResizeMode(QHeaderView::Stretch);
    v_header->setSectionResizeMode(QHeaderView::Fixed);
    configure_updateGraphicsButton();

    //Internal signals/slots
    connect(m_pushButton_updateGraphics, &QAbstractButton::pressed, this,
            &TopAccuraciesView::slot_pushButton_updateGraphics_pressed);
}

void TopAccuraciesView::addTableRow(const QString &identifier, double top1, double top5) {
    QTableWidget *table = ui->tableWidget_topAccuracies;
    //Convert doubles to String with 2 decimal spots precision
    auto top1Str = QString::number(top1, 'G', 5);
    auto top5Str = QString::number(top5, 'G', 5);

    int row = table->rowCount();
    table->insertRow(row);
    emit sig_accuraciesTable_rowAdded(identifier, top1, top5);

    //Fill table row
    auto identifierItem = new QTableWidgetItem(identifier);
    auto top1StrItem = new QTableWidgetItem(top1Str);
    auto top5StrItem = new QTableWidgetItem(top5Str);

    top1StrItem->setTextAlignment(Qt::AlignCenter);
    top5StrItem->setTextAlignment(Qt::AlignCenter);

    table->setVerticalHeaderItem(row, identifierItem);
    table->setItem(row, 0, top1StrItem);
    table->setItem(row, 1, top5StrItem);
}

void TopAccuraciesView::removeTableRow(const QString &identifier) {
    QTableWidget *table = ui->tableWidget_topAccuracies;
    emit sig_accuraciesTable_rowRemoved(identifier);
    for (int i = 0; i < table->rowCount(); i++) {
        if (table->verticalHeaderItem(i)->text() == identifier) {
            table->removeRow(i);
            return;
        }
    }
}

TopAccuraciesView::~TopAccuraciesView() {
    delete ui;
}

void TopAccuraciesView::setTopAccuraciesGraphics(QGraphicsItem *topAccuraciesImage) {
    auto view = ui->graphicsView_topAccuracies;
    auto *scene = new QGraphicsScene();
    scene->addItem(topAccuraciesImage);
    //Jump back to main programs thread to avoid warnings
    scene->moveToThread(this->thread());

    view->scale(0.9, 0.9);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setScene(scene);
}

void TopAccuraciesView::slot_pushButton_updateGraphics_pressed() {
    emit sig_requestTopAccuraciesGraphics(this);
}

void TopAccuraciesView::configure_updateGraphicsButton() {
    const auto icon = QIcon(":/Resources/UISymbols/UI_Reload_Icon.svg");
    m_pushButton_updateGraphics = ui->tableWidget_topAccuracies->findChild<QAbstractButton *>();
    if (m_pushButton_updateGraphics) {
        m_pushButton_updateGraphics->setIcon(icon);
    }
}


void TopAccuraciesView::changeEvent(QEvent *event) {
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
void TopAccuraciesView::retranslateUi() {
    if (m_pushButton_updateGraphics)
        m_pushButton_updateGraphics->setToolTip("Update graphics...");
}
