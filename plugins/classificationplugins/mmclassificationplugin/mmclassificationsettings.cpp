#include "mmclassificationsettings.h"
#include "ui_mmclassificationsettings.h"

MMClassificationSettings::MMClassificationSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MMClassificationSettings)
{
    ui->setupUi(this);
    loadSettings();
}

MMClassificationSettings::~MMClassificationSettings()
{
    delete ui;
}

void MMClassificationSettings::saveSettings()
{
    m_settings.setValue(m_mmclassificationPath, ui->lineEdit_mmclassificationPath->text());
    m_settings.setValue(m_mmclsPath, ui->lineEdit_mmclsPath->text());
    m_settings.setValue(m_pythonPath, ui->lineEdit_pythonPath->text());

}

void MMClassificationSettings::loadSettings()
{
    ui->lineEdit_mmclassificationPath->setText(m_settings.value(m_mmclassificationPath).toString());
    ui->lineEdit_mmclsPath->setText(m_settings.value(m_mmclsPath).toString());
    ui->lineEdit_pythonPath->setText(m_settings.value(m_pythonPath).toString());
}

QString MMClassificationSettings::getMMClassificationPath()
{
    return m_settings.value(m_mmclassificationPath).toString();
}

QString MMClassificationSettings::getMMClsPath()
{
    return m_settings.value(m_mmclsPath).toString();
}

QString MMClassificationSettings::getPythonPath(){
    return m_settings.value(m_pythonPath).toString();
}


