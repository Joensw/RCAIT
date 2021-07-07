#include "settingsview.h"
#include "ui_settingsview.h"

#include <QFileDialog>


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
    QVBoxLayout *layout = new QVBoxLayout(mGlobalSettingsWidget);

    QPushButton *projectDirButton = new QPushButton("Select project directory");
    QPushButton *classificationPluginsDirButton = new QPushButton("Select classification plugin directory");
    QPushButton *imageLoaderPluginsDirButton = new QPushButton("Select image loader plugin directory");
    connect(projectDirButton, &QPushButton::clicked, this, &SettingsView::slot_setProjectDir);
    connect(classificationPluginsDirButton, &QPushButton::clicked, this, &SettingsView::slot_setClassificationPluginsDir);
    connect(imageLoaderPluginsDirButton, &QPushButton::clicked, this, &SettingsView::slot_setImageLoaderPluginsDir);

    layout->addWidget(projectDirButton);
    layout->addWidget(classificationPluginsDirButton);
    layout->addWidget(imageLoaderPluginsDirButton);

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
        emit sig_applyGlobalSettings(mProjectDir, mClassificationPluginsDir, mImageLoaderPluginsDir);
    } else {
        // -1 weil 0. Eintrag GlobalSettings ist.
        emit sig_applySettings(index - 1);
    }
}


//private slots for global settings widget
void SettingsView::slot_setProjectDir()
{
     mProjectDir = QFileDialog::getExistingDirectory(this, "Select project directory");
}

void SettingsView::slot_setClassificationPluginsDir()
{
     mClassificationPluginsDir = QFileDialog::getExistingDirectory(this, "Select project directory");
}

void SettingsView::slot_setImageLoaderPluginsDir()
{
     mImageLoaderPluginsDir = QFileDialog::getExistingDirectory(this, "Select project directory");
}




SettingsView::~SettingsView()
{
    delete ui;
}


