#include "TrainingResultView.h"
#include "ui_trainingresultview.h"

TrainingResultView::TrainingResultView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainingResultView)
{
    ui->setupUi(this);
}

TrainingResultView::~TrainingResultView()
{
    delete ui;
}
