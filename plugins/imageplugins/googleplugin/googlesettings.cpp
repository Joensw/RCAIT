/**
 *@file Googlesettings.cpp
 *
 *@brief contains implementation for methods of GoogleSettings class
 */
#include "googlesettings.h"
#include "ui_googlesettings.h"

GoogleSettings::GoogleSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoogleSettings)
{
    ui->setupUi(this);
    loadSettings();
}

GoogleSettings::~GoogleSettings()
{
    delete ui;
}

void GoogleSettings::saveSettings()
{
    m_settings.setValue(m_pythonPath,ui->lineEdit_PythonPath->text());
    m_settings.setValue(m_APIKey,ui->lineEdit_GoogleAPIKey->text());
    m_settings.setValue(m_projectCX,ui->lineEdit_GoogleCX->text());

}

void GoogleSettings::loadSettings()
{
    ui->lineEdit_PythonPath->setText(m_settings.value(m_pythonPath).toString());
    ui->lineEdit_GoogleAPIKey->setText(m_settings.value(m_APIKey).toString());
    ui->lineEdit_GoogleCX->setText(m_settings.value(m_projectCX).toString());
}


QString GoogleSettings::getPythonPath(){
    return m_settings.value(m_pythonPath).toString();
}

void GoogleSettings::setPythonPath(QString path)
{
    m_settings.setValue(m_pythonPath,path);
}

QString GoogleSettings::getAPIKey()
{
    return m_settings.value(m_APIKey).toString();
}

QString GoogleSettings::getProjectCX()
{
    return m_settings.value(m_projectCX).toString();
}

void GoogleSettings::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}


