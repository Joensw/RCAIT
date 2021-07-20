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
    QHeaderView *header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    configure_updateGraphicsButton();
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

void TopAccuraciesView::on_pushButton_updateGraphics_pressed() {
    emit sig_requestTopAccuraciesGraphics(this);
}

void TopAccuraciesView::configure_updateGraphicsButton() {
    const auto icon = QIcon(":/Resources/UISymbols/UI_Reload_Icon.svg");
    m_pushButton_updateGraphics->setIcon(icon);
    m_pushButton_updateGraphics->setFlat(true);
    connect(m_pushButton_updateGraphics, &QPushButton::pressed, this, &TopAccuraciesView::on_pushButton_updateGraphics_pressed);
    ui->verticalLayout_tableLayout->addWidget(m_pushButton_updateGraphics);
}
