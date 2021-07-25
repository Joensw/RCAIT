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
    h_header->setSectionResizeMode(QHeaderView::Fixed);
    v_header->setSectionResizeMode(QHeaderView::Fixed);


    configure_updateGraphicsButton();

    //Internal signals/slots
    connect(m_pushButton_updateGraphics, &QAbstractButton::pressed, this,
            &ClassificationResultView::slot_pushButton_updateGraphics_pressed);

    dummyFunctionTest();
}

void ClassificationResultView::addTableRow(const QString &identifier, const QList<double> &data) {
    QTableWidget *table = ui->tableWidget_classificationresult;

    int row = table->rowCount();
    table->insertRow(row);
    emit sig_classificationResultTable_rowAdded(this, identifier, data);

    //Fill table row
    auto identifierItem = new QTableWidgetItem(identifier);
    int col = 0;
    for (const auto &value : data) {
        //Convert doubles to String with 2 decimal spots precision
        auto valueStr = QString::number(value, 'G', 5);
        auto valueStrItem = new QTableWidgetItem(valueStr);
        valueStrItem->setTextAlignment(Qt::AlignCenter);
        table->setVerticalHeaderItem(row, identifierItem);
        table->setItem(row, col++, valueStrItem);
    }
}

void ClassificationResultView::removeTableRow(const QString &identifier) {
    QTableWidget *table = ui->tableWidget_classificationresult;
    emit sig_classificationResultTable_rowRemoved(this, identifier);
    for (int i = 0; i < table->rowCount(); i++) {
        if (table->verticalHeaderItem(i)->text() == identifier) {
            table->removeRow(i);
            return;
        }
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

void ClassificationResultView::dummyFunctionTest() {
    QTableWidget *table = ui->tableWidget_classificationresult;
    QStringList labels = {"Car", "Truck", "Airplane", "Boat", "Bike"};
    table->setColumnCount(labels.size());
    table->setHorizontalHeaderLabels(labels);

    for (int j = 0; j < 20; ++j) {
        QList<double> randomData;
        int target = 100;
        for (int i = 0; i < labels.size(); ++i) {
            int random;
            if (i == labels.size() - 1)
                random = target;
            else
                random = QRandomGenerator::global()->bounded(target);
            target -= random;
            randomData << random;
        }
        this->addTableRow(QString("Image %1").arg(j), randomData);
    }
}
