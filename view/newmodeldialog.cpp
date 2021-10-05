#include "newmodeldialog.h"
#include "ui_newmodeldialog.h"

NewModelDialog::NewModelDialog(QWidget *parent, const QStringList &classificationPlugins) :
        QDialog(parent),
        ui(new Ui::NewModelDialog) {
    ui->setupUi(this);

    ui->classificationPluginComboBox->addItems(classificationPlugins);
    connect(ui->classificationPluginComboBox, &QComboBox::currentTextChanged, this,
            &NewModelDialog::slot_classificationPlugin_currentTextChanged);
}

NewModelDialog::~NewModelDialog()
{
    delete ui;
}

void NewModelDialog::setErrorMessage(const QString &error)
{
    AnimationUtilities::setTextWithAnimation(ui->label_information, error);
}

void NewModelDialog::setAvailableBases(const QStringList &bases)
{
    ui->pluginProfileComboBox->clear();
    ui->pluginProfileComboBox->addItems(bases);
}

QString NewModelDialog::getCurrentSelectedPlugin() const {
    return ui->classificationPluginComboBox->currentText();
}

void NewModelDialog::on_buttonBox_rejected(){
    this->reject();
}

void NewModelDialog::slot_classificationPlugin_currentTextChanged(const QString &text) {
    emit sig_pluginSelected(text);
}

void NewModelDialog::on_buttonBox_accepted(){
    emit sig_newModelConfirm(ui->lineEdit_nameEntry->text(), ui->classificationPluginComboBox->currentText(), ui->pluginProfileComboBox->currentText());
}
