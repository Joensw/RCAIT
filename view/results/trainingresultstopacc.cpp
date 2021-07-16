#include "trainingresultstopacc.h"
#include "ui_trainingresultstopacc.h"

TrainingResultsTopAcc::TrainingResultsTopAcc(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TrainingResultsTopAcc) {
    ui->setupUi(this);

    QTableWidget *table = ui->tableWidget_topAccuracy;

    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"Top 1%", "Top5%"});
    //Stretch table headers to fill the space available
    QHeaderView *header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

void TrainingResultsTopAcc::addTableRow(const QString& identifier, double top1, double top5) {
    QTableWidget *table = ui->tableWidget_topAccuracy;
    //Convert doubles to String with 2 decimal spots precision
    auto top1Str = QString::number(top1, 'G', 5);
    auto top5Str = QString::number(top5, 'G', 5);

    int row = table->rowCount();
    table->insertRow(row);

    //Fill table row
    table->setVerticalHeaderItem(row, new QTableWidgetItem(identifier));
    table->setItem(row, 0, new QTableWidgetItem(top1Str));
    table->setItem(row, 1, new QTableWidgetItem(top5Str));
}

void TrainingResultsTopAcc::removeTableRow(const QString& identifier) {
    QTableWidget *table = ui->tableWidget_topAccuracy;
    for (int i = 0; i < table->rowCount(); i++) {
        if (table->verticalHeaderItem(i)->text() == identifier){
            table->removeRow(i);
            return;
        }
    }
}

TrainingResultsTopAcc::~TrainingResultsTopAcc() {
    delete ui;
}
