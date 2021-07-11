#include "removeprojectdialog.h"
#include "ui_removeprojectdialog.h"

RemoveProjectDialog::RemoveProjectDialog(QWidget *parent, QString toRemove) :
    QDialog(parent),
    ui(new Ui::RemoveProjectDialog)
{
    ui->setupUi(this);
    mToRemove = toRemove;
    QString message = ui->label->text().replace("&lt;name&gt;", toRemove);
    ui->label->setText(message);
}

RemoveProjectDialog::~RemoveProjectDialog()
{
    delete ui;
}

QString RemoveProjectDialog::getProjectName()
{
    return mToRemove;
}

void RemoveProjectDialog::on_buttonBox_accepted()
{
    emit sig_removeProjectConfirm();
}

void RemoveProjectDialog::on_buttonBox_rejected()
{
    this->reject();
}
