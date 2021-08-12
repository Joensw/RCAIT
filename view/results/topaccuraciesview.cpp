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
    connect(m_pushButton_updateGraphics, &QAbstractButton::clicked, this,
            &TopAccuraciesView::slot_pushButton_updateGraphics_clicked);
}

void TopAccuraciesView::addTopAccuraciesEntry(const QString &identifier, double top1, double top5) {
    auto table = ui->tableWidget_topAccuracies;
    auto top1Str = QString::number(top1, 'f', 2);
    auto top5Str = QString::number(top5, 'f', 2);

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

void TopAccuraciesView::setTopAccuraciesGraphics(const QSharedPointer<QGraphicsItem> &topAccuraciesImage) {
    m_topAccuraciesImage = topAccuraciesImage;

    auto view = ui->graphicsView_topAccuracies;
    auto *scene = new QGraphicsScene();
    scene->addItem(topAccuraciesImage.get());
    //Jump back to main programs thread to avoid warnings
    scene->moveToThread(this->thread());

    view->scale(0.9, 0.9);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setScene(scene);
}

void TopAccuraciesView::slot_pushButton_updateGraphics_clicked() {
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
        // this event is sent if a translator is loaded
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
        m_pushButton_updateGraphics->setToolTip(tr("Update graphics..."));
}
