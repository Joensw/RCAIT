#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"
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

void NewProjectDialog::on_buttonBox_rejected(){
    this->reject();
}
//this is simple for now, if there is time the actual error could be used as message.
void NewProjectDialog::on_buttonBox_accepted(){
    //using a static method here is not that nice
    if (ProjectController::verifyName(ui->name_entry->text())) {
        emit newProjectConfirm(ui->name_entry->text());
        this->accept();
        return;
    }
    ui->label_invalidname->show();
}

