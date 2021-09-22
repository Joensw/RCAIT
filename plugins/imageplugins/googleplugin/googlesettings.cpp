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

}

void GoogleSettings::loadSettings()
{
    ui->lineEdit_PythonPath->setText(m_settings.value(m_pythonPath).toString());
}


QString GoogleSettings::getPythonPath(){
    return m_settings.value(m_pythonPath).toString();
}

void GoogleSettings::setPythonPath(QString path)
{
    m_settings.setValue(m_pythonPath,path);
}

void GoogleSettings::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}


