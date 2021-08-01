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

void TopAccuraciesView::addTopAccuraciesEntry(const QString &identifier, double top1, double top5) {
    auto table = ui->tableWidget_topAccuracies;
    auto top1Str = QString::number(top1, 'G', 5);
    auto top5Str = QString::number(top5, 'G', 5);

    int row = table->addTableRow(identifier, {top1Str, top5Str});

    //Set colors matching the graphical result
    table->at(row,0)->setBackground(QBrush("royal blue"));
    table->at(row,1)->setBackground(QBrush("orange"));
}

void TopAccuraciesView::removeTopAccuraciesEntry(const QString &identifier) {
    auto *table = ui->tableWidget_topAccuracies;
    table->removeTableRow(identifier);
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
    emit sig_normal_requestTopAccuraciesGraphics(this);
}

void TopAccuraciesView::configure_updateGraphicsButton() {
    const auto icon = QIcon(":/Resources/UISymbols/UI_Reload_Icon.svg");
    m_pushButton_updateGraphics = ui->tableWidget_topAccuracies->getCornerButton();
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
