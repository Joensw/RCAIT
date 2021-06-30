#include "removemodeldialog.h"
#include "ui_removemodeldialog.h"

RemoveModelDialog::RemoveModelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveModelDialog)
{
    ui->setupUi(this);
}

RemoveModelDialog::~RemoveModelDialog()
{
    delete ui;
}
