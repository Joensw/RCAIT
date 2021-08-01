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
    m_settings.setValue(m_apiKey,ui->lineEdit_ApiKey->text());
    m_settings.setValue(m_apiSecret,ui->lineEdit_ApiSecret->text());
    m_settings.setValue(m_pythonPath,ui->lineEdit_PythonPath->text());

}

void BingSettings::loadSettings()
{
    ui->lineEdit_ApiKey->setText(m_settings.value(m_apiKey).toString());
    ui->lineEdit_ApiSecret->setText(m_settings.value(m_apiSecret).toString());
    ui->lineEdit_PythonPath->setText(m_settings.value(m_pythonPath).toString());
}


QString BingSettings::getPythonPath(){
    return m_settings.value(m_pythonPath).toString();
}


QString BingSettings::getaAPIKey()
{
    return m_settings.value(m_apiKey).toString();
}

QString BingSettings::getAPISecret()
{
    return m_settings.value(m_apiSecret).toString();
}


