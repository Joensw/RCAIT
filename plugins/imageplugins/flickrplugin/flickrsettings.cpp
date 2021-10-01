/**
 * @file flickrsettings.cpp
 *
 * @brief implmenets methods for FlickrSettings class
 *
 */
#include "flickrsettings.h"
#include "ui_flickrsettings.h"

FlickrSettings::FlickrSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlickrSettings)
{
    m_errorMessage = CONFIGURED_STRING;
    ui->setupUi(this);
    loadSettings();
}

FlickrSettings::~FlickrSettings()
{
    delete ui;
}

void FlickrSettings::saveSettings()
{
    m_settings.setValue(m_apiKey,ui->lineEdit_ApiKey->text());
    m_settings.setValue(m_apiSecret,ui->lineEdit_ApiSecret->text());
    m_settings.setValue(m_pythonPath,ui->lineEdit_PythonPath->text());

}

void FlickrSettings::loadSettings()
{
    ui->lineEdit_ApiKey->setText(m_settings.value(m_apiKey).toString());
    ui->lineEdit_ApiSecret->setText(m_settings.value(m_apiSecret).toString());
    ui->lineEdit_PythonPath->setText(m_settings.value(m_pythonPath).toString());
}


QString FlickrSettings::getPythonPath(){
    return m_settings.value(m_pythonPath).toString();
}

void FlickrSettings::setAPIKey(QString key)
{
    m_settings.setValue(m_apiKey,key);
}

void FlickrSettings::setAPISecret(QString key)
{
    m_settings.setValue(m_apiSecret, key);
}

void FlickrSettings::setPythonPath(QString path)
{
    m_settings.setValue(m_pythonPath, path);
}

bool FlickrSettings::isConfigured()
{
    QStringList missingConfigs;
    if(m_settings.value(m_pythonPath).toString().isEmpty()){
        missingConfigs << m_pythonPath;
    }

    if(m_settings.value(m_apiSecret).toString().isEmpty()){
        missingConfigs << m_apiSecret;
    }

    if(m_settings.value(m_apiKey).toString().isEmpty()){
        missingConfigs << m_apiKey;
    }

    if(!missingConfigs.isEmpty()){
        m_errorMessage = ERROR_STRING % missingConfigs.join(", ") % ERROR_END;
        return false;
    } else {

        return true;
    }
}

QString FlickrSettings::getMissingConfigError()
{
    return m_errorMessage;
}


QString FlickrSettings::getAPIKey() {
    return m_settings.value(m_apiKey).toString();
}

QString FlickrSettings::getAPISecret()
{
    return m_settings.value(m_apiSecret).toString();
}

void FlickrSettings::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}


