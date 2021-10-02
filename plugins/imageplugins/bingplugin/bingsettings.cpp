/**
 *@file bingsettings.cpp
 *
 *@brief contains implementation for methods of BingSettings class
 */
#include "bingsettings.h"
#include "ui_bingsettings.h"

BingSettings::BingSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BingSettings)
{
    m_errorMessage = CONFIGURED_STRING;
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

void BingSettings::loadSettings() const
{
    ui->lineEdit_PythonPath->setText(m_settings.value(m_pythonPath).toString());
}


QString BingSettings::getPythonPath() const{
    return m_settings.value(m_pythonPath).toString();
}

void BingSettings::setPythonPath(const QString& path)
{
    m_settings.setValue(m_pythonPath,path);
}

bool BingSettings::isConfigured()
{
    if(QString pythonPath = m_settings.value(m_pythonPath).toString(); pythonPath.isEmpty()){
        m_errorMessage = NOT_CONFIGURED_STRING;
        return false;
    }

    return true;
}

QString BingSettings::getMissingConfigError() const
{
    return m_errorMessage;
}

void BingSettings::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}


