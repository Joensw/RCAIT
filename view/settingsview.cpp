#include "settingsview.h"
#include "ui_settingsview.h"


SettingsView::SettingsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsView)
{
    ui->setupUi(this);
}

SettingsView::SettingsView(QWidget *parent, QStringList pluginNames, QList<QWidget *> pluginConfigurationWidgets) :
    QWidget(parent),
    ui(new Ui::SettingsView)
{
    ui->setupUi(this);


    ui->pluginList->addItem("Global settings");
    mGlobalSettingsWidget = new QWidget();
    ui->pluginWidget->addWidget(mGlobalSettingsWidget);

    assert(pluginNames.size() == pluginConfigurationWidgets.size());

    int i = 0;
    for(QString name : pluginNames){
        ui->pluginList->addItem(name);
        ui->pluginWidget->addWidget(pluginConfigurationWidgets.at(i));
    }

}

void SettingsView::on_saveButton_clicked()
{
    int index = ui->pluginList->currentIndex().row();

    if (index == 0){
        //TODO proper arguments, implementing global settings widget
        emit sig_applyGlobalSettings("","","");
    } else {
        // -1 weil 0. Eintrag GlobaklSettings ist.
        emit sig_applySettings(index - 1);
    }
}


SettingsView::~SettingsView()
{
    delete ui;
}


