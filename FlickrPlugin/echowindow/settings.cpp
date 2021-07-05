#include "settings.h"
#include "ui_settings.h"


Settings::Settings(QWidget *parent, ImageLoaderPlugin *plugin) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    this->plugin = plugin;
    ui->setupUi(this);
}


QString Settings::addSettings(QString name, QWidget *settingsWidget)
{
    QListWidgetItem *itemSettingsGlobal = new QListWidgetItem(name);
    ui->listWidget->addItem(itemSettingsGlobal);
    pluginSettings.append(settingsWidget);
    ui->stackedWidget->addWidget(settingsWidget);

    return "super";
}


Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    saveSettings();
}

void Settings::saveSettings(){
    plugin->saveConfiguration();

}
