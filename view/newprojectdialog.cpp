#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"
//has to be delcared here out of necessity
#include "projectcontroller.h"

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);
    ui->label_invalidname->hide();
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

void NewProjectDialog::showErrorMessage(){
    ui->label_invalidname->show();
}

void NewProjectDialog::hideErrorMessage(){
    ui->label_invalidname->hide();
}

void NewProjectDialog::setErrorMessage(const QString &error){
    ui->label_invalidname->setText(error);
}

void NewProjectDialog::on_buttonBox_rejected(){
    this->reject();
}

void NewProjectDialog::on_buttonBox_accepted(){
    emit sig_newProjectConfirm(ui->name_entry->text());
}

