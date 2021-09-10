#include "topaccuraciesview.h"
#include "ui_topaccuraciesview.h"

TopAccuraciesView::TopAccuraciesView(SavableResultsWidget *tabWidget, QWidget *parent) :
        GenericGraphicsView(tabWidget, parent),
        ui(new Ui::TopAccuraciesView) {
    ui->setupUi(this);

    QTableWidget *table = ui->tableWidget_topAccuracies;
    table->setColumnCount(TABLE_COLUMN_COUNT);

    //Stretch table headers to fill the space available
    QHeaderView *h_header = table->horizontalHeader();
    QHeaderView *v_header = table->verticalHeader();
    h_header->setSectionResizeMode(QHeaderView::Stretch);
    v_header->setSectionResizeMode(QHeaderView::Fixed);
    configure_updateGraphicsButton();

    //Configure font
    QFont font(FONT_NAME, FONT_SIZE);
    v_header->setFont(font);

    //Internal signals/slots
    connect(m_pushButton_updateGraphics, &QAbstractButton::clicked, this,
            &TopAccuraciesView::slot_pushButton_updateGraphics_clicked);
    retranslateUi();
}

void TopAccuraciesView::addTopAccuraciesEntry(const QString &identifier, double top1, double top5) {
    auto table = ui->tableWidget_topAccuracies;
    auto top1Str = QString::number(top1, NUMBER_FORMAT, NUMBER_PRECISION);
    auto top5Str = QString::number(top5, NUMBER_FORMAT, NUMBER_PRECISION);

    int row = table->addTableRow(identifier, {top1Str, top5Str});

    //Set colors matching the graphical result
    table->at(row, 0)->setBackground(QBrush(TOP1_COLOR));
    table->at(row, 1)->setBackground(QBrush(TOP5_COLOR));
}

void TopAccuraciesView::removeTopAccuraciesEntry(const QString &identifier) {
    auto *table = ui->tableWidget_topAccuracies;
    table->removeTableRow(identifier);
}

TopAccuraciesView::~TopAccuraciesView() {
    m_topAccuraciesImage.clear();
    delete ui;
}

void TopAccuraciesView::setTopAccuraciesGraphics(const QSharedPointer<QGraphicsItem> &topAccuraciesImage) {
    m_topAccuraciesImage = topAccuraciesImage;

    auto view = ui->graphicsView_topAccuracies;
    m_topAccuraciesScene.reset(new QGraphicsScene);
    m_topAccuraciesScene->addItem(&*topAccuraciesImage);
    //Jump back to main programs thread to avoid warnings
    m_topAccuraciesScene->moveToThread(this->thread());

    view->scale(GRAPHICS_SCALING_FACTOR, GRAPHICS_SCALING_FACTOR);
    view->fitInView(m_topAccuraciesScene->sceneRect(), Qt::KeepAspectRatio);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setScene(&*m_topAccuraciesScene);
}

void TopAccuraciesView::slot_pushButton_updateGraphics_clicked() {
    emit sig_normal_requestTopAccuraciesGraphics(this);
}

void TopAccuraciesView::configure_updateGraphicsButton() {
    const auto icon = QIcon(UPDATE_GRAPHICS_BUTTON_ICON);
    m_pushButton_updateGraphics = ui->tableWidget_topAccuracies->getCornerButton();
    if (m_pushButton_updateGraphics) {
        m_pushButton_updateGraphics->setIcon(icon);
    }
}

[[maybe_unused]] void TopAccuraciesView::setUpdateGraphicsButtonState(bool enabled) {
    if (m_pushButton_updateGraphics)
        m_pushButton_updateGraphics->setEnabled(enabled);
}

[[maybe_unused]] bool TopAccuraciesView::getUpdateGraphicsButtonState() {
    if (m_pushButton_updateGraphics) {
        return m_pushButton_updateGraphics->isEnabled();
    }
    return false;
}

[[maybe_unused]] const QSharedPointer<QGraphicsItem> &TopAccuraciesView::getTopAccuraciesImage() const {
    return m_topAccuraciesImage;
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

    auto *table = ui->tableWidget_topAccuracies;
    table->setHorizontalHeaderLabels({tr(TOP1_HEADER), tr(TOP5_HEADER)});
    if (m_pushButton_updateGraphics) {
        m_pushButton_updateGraphics->setToolTip(tr(UPDATE_GRAPHICS_BUTTON_TOOLTIP));
    }
}
