#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"
//has to be declared here out of necessity
#include "projectcontroller.h"

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);
    ui->label_information->hide();
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

void NewProjectDialog::showErrorMessage(){
    ui->label_information->show();
}

void NewProjectDialog::hideErrorMessage(){
    ui->label_information->hide();
}

void NewProjectDialog::setErrorMessage(const QString &error){
    AnimationUtilities::setTextWithAnimation(ui->label_information, error);
}

void NewProjectDialog::on_buttonBox_rejected(){
    this->reject();
}

void NewProjectDialog::on_buttonBox_accepted(){
    emit sig_newProjectConfirm(ui->name_entry->text());
}

