#include "inputimageswidget.h"
#include "ui_inputimageswidget.h"

InputImagesWidget::InputImagesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputImagesWidget)
{
    ui->setupUi(this);
}

InputImagesWidget::~InputImagesWidget()
{
    delete ui;
}
