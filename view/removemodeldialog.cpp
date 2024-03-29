#include "removemodeldialog.h"
#include "ui_removemodeldialog.h"

RemoveModelDialog::RemoveModelDialog(QWidget *parent, const QString &toRemove) :
        QDialog(parent),
        ui(new Ui::RemoveModelDialog)
{
    ui->setupUi(this);
    mToRemove = toRemove;
    QString message = ui->label->text().replace(MODEL_NAME_PLACEHOLDER, toRemove);
    ui->label->setText(message);

}

RemoveModelDialog::~RemoveModelDialog()
{
    delete ui;
}

QString RemoveModelDialog::getModelName() const {
    return mToRemove;
}

void RemoveModelDialog::setErrorMessage(const QString &error)
{
    AnimationUtilities::setTextWithAnimation(ui->label_error, error);
}

void RemoveModelDialog::on_buttonBox_accepted()
{
    emit sig_removeModelConfirm();
}

void RemoveModelDialog::on_buttonBox_rejected()
{
    this->reject();
}

