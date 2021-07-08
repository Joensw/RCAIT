#include "aitrainingwidget.h"
#include "ui_aitrainingwidget.h"

AITrainingWidget::AITrainingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AITrainingWidget)
{
    ui->setupUi(this);
}

AITrainingWidget::~AITrainingWidget()
{
    delete ui;
}
