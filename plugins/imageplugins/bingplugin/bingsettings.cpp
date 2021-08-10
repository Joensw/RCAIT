#include "bingsettings.h"
#include "ui_bingsettings.h"

BingSettings::BingSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BingSettings)
{
    ui->setupUi(this);
    loadSettings();
}

BingSettings::~BingSettings()
{
    delete ui;
}

void BingSettings::saveSettings()
{
    m_settings.setValue(m_pythonPath,ui->lineEdit_PythonPath->text());

}

void BingSettings::loadSettings()
{
    ui->lineEdit_PythonPath->setText(m_settings.value(m_pythonPath).toString());
}


QString BingSettings::getPythonPath(){
    return m_settings.value(m_pythonPath).toString();
}


