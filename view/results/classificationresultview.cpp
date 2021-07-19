#include "classificationresultview.h"
#include "ui_classificationresultview.h"

ClassificationResultView::ClassificationResultView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassificationResultView)
{
    ui->setupUi(this);
}

ClassificationResultView::~ClassificationResultView()
{
    delete ui;
}
