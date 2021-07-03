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

void InputImagesWidget::slot_loaded(QString path) {

}

void InputImagesWidget::slot_progress(int progress) {

}
