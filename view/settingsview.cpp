#include "settingsview.h"
#include "ui_settingsview.h"

SettingsView::SettingsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsView)
{
    ui->setupUi(this);
}

SettingsView::~SettingsView()
{
    delete ui;
}

SettingsView::SettingsView(QWidget *parent, QStringList pluginNames, QList<QWidget *> pluginConfigurationWidgets) :
    QDialog(parent),
    ui(new Ui::SettingsView)
{
    ui->setupUi(this);
    ui->pluginList->addItem("Global settings");
    ui->pluginWidget = mGlobalSettingsWidget;

    assert(pluginNames.size() == pluginConfigurationWidgets.size());

    mPluginWidgets = pluginConfigurationWidgets;

    for(QString name : pluginNames){
        ui->pluginList->addItem(name);
    }

}

void SettingsView::on_applyButton_clicked()
{
    int index =  ui->pluginList->currentIndex().row();

    if (index == 0){
        //TODO proper arguments, implementing global settings widget
        emit sig_applyGlobalSettings("","","");
    } else {
        emit sig_applySettings(index);
    }
}


void SettingsView::on_pluginList_clicked(const QModelIndex &index)
{
    int indexNum =  index.row();

    if (indexNum == 0){
        ui->pluginWidget = mGlobalSettingsWidget;
    } else {
        ui->pluginWidget = mPluginWidgets.at(indexNum - 1);
    }
}


void SettingsView::on_closeButton_clicked()
{
    close();
}

