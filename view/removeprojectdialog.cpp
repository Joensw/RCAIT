#include "removeprojectdialog.h"
#include "ui_removeprojectdialog.h"

RemoveProjectDialog::RemoveProjectDialog(QWidget *parent, const QString &toRemove) :
        QDialog(parent),
        ui(new Ui::RemoveProjectDialog)
{
    ui->setupUi(this);
    mToRemove = toRemove;
    QString message = ui->label->text().replace(PROJECT_NAME_PLACEHOLDER, toRemove);
    ui->label->setText(message);
}

RemoveProjectDialog::~RemoveProjectDialog()
{
    delete ui;
}

QString RemoveProjectDialog::getProjectName() const {
    return mToRemove;
}

void RemoveProjectDialog::setErrorMessage(const QString &error)
{
    AnimationUtilities::setTextWithAnimation(ui->label_error, error);
}

void RemoveProjectDialog::on_buttonBox_accepted()
{
    emit sig_removeProjectConfirm();
}

void RemoveProjectDialog::on_buttonBox_rejected()
{
    this->reject();
}
