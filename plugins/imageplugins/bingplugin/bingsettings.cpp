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

void BingSettings::setPythonPath(QString path)
{
    m_settings.setValue(m_pythonPath,path);
}

void BingSettings::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}


