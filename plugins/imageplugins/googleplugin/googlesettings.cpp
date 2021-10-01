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
    m_errorMessage = CONFIGURED_STRING;
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

bool GoogleSettings::isConfigured()
{
    QStringList missingConfigs;
    int isConfigured = 3;
    if(m_settings.value(m_pythonPath).toString().isEmpty()){
        missingConfigs << m_pythonPath;
        isConfigured--;
    }

    if(m_settings.value(m_projectCX).toString().isEmpty()){
        missingConfigs << m_projectCX;
        isConfigured--;
    }

    if(m_settings.value(m_APIKey).toString().isEmpty()){
        missingConfigs << m_APIKey;
        isConfigured--;
    }

    if(!(isConfigured==3)){

        m_errorMessage = ERROR_STRING % missingConfigs.join(", ") % ERROR_END;
        return false;
    } else {

       return true;
    }
}

QString GoogleSettings::getMissingConfigError()
{
    return m_errorMessage;
}

void GoogleSettings::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}


