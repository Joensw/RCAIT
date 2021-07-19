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

    mGlobalSettingsWidget = new GlobalSettingsWidget();

    ui->pluginList->addItem(mGlobalSettingsWidget->windowTitle());

    connect(mGlobalSettingsWidget, &GlobalSettingsWidget::sig_wasTranslated, this, &SettingsView::slot_retranslate);

    connect(mGlobalSettingsWidget, &GlobalSettingsWidget::sig_setProjectDir, this, &SettingsView::slot_setProjectDir);
    connect(mGlobalSettingsWidget, &GlobalSettingsWidget::sig_setClassificationPluginsDir, this, &SettingsView::slot_setClassificationPluginsDir);
    connect(mGlobalSettingsWidget, &GlobalSettingsWidget::sig_setImageLoaderPluginsDir, this, &SettingsView::slot_setImageLoaderPluginsDir);

    ui->pluginWidget->addWidget(mGlobalSettingsWidget);


    assert(pluginNames.size() == pluginConfigurationWidgets.size());

    int i = 0;
    for(QString name : pluginNames){
        ui->pluginList->addItem(name);
        ui->pluginWidget->addWidget(pluginConfigurationWidgets.at(i));
    }
}

void SettingsView::pathsUpdated(int amount)
{
    if (amount == 0){
        mGlobalSettingsWidget->showNonUpdate();
        return;
    }
    mGlobalSettingsWidget->showUpdate(amount);
}

void SettingsView::clearPaths()
{
    mClassificationPluginsDir.clear();
    mImageLoaderPluginsDir.clear();
    mProjectDir.clear();
    mGlobalSettingsWidget->clearNewPaths();
}

void SettingsView::setGlobalSettingsError(QString error)
{
    mGlobalSettingsWidget->setError(error);
}

void SettingsView::setCurrentProjectDirectory(QString path)
{
    mGlobalSettingsWidget->setCurrentProjectsDir(path);
}

void SettingsView::setCurrentClassificationPluginDirectory(QString path)
{
    mGlobalSettingsWidget->setCurrentClassificationDir(path);
}

void SettingsView::setCurrentImageLoaderPluginDirectory(QString path)
{
    mGlobalSettingsWidget->setCurrentImageLoaderDir(path);
}

void SettingsView::on_saveButton_clicked()
{
    int index = ui->pluginList->currentIndex().row();

    if (index == 0){
        /*
        if (mProjectDir.isNull() || mClassificationPluginsDir.isNull() || mImageLoaderPluginsDir.isNull()){
            return;
            // shouldnt be a problem, this path is them simply not updated, same thing should occur if user closes out of file dialog
            // that is why i have commented this section
        }
        */
        emit sig_applyGlobalSettings(mProjectDir, mClassificationPluginsDir, mImageLoaderPluginsDir);
    } else {
        // -1 weil 0. Eintrag GlobalSettings ist.
        emit sig_applySettings(index - 1);
    }
}


//private slots for global settings widget
void SettingsView::slot_setProjectDir()
{
    mProjectDir = QFileDialog::getExistingDirectory(this, tr("Select project directory"));
    if (!mProjectDir.isEmpty()){
        mGlobalSettingsWidget->setNewProjectPath(mProjectDir);
        return;
    }
    mGlobalSettingsWidget->setNewProjectPath("-");
}

void SettingsView::slot_setClassificationPluginsDir()
{
    mClassificationPluginsDir = QFileDialog::getExistingDirectory(this, tr("Select classification plugin directory"));
    if (!mClassificationPluginsDir.isEmpty()) {
        mGlobalSettingsWidget->setNewClassificationPluginPath(mClassificationPluginsDir);
        return;
    }
    mGlobalSettingsWidget->setNewClassificationPluginPath("-");
}

void SettingsView::slot_setImageLoaderPluginsDir()
{
    mImageLoaderPluginsDir = QFileDialog::getExistingDirectory(this, tr("Select image loader plugin directory"));
    if (!mImageLoaderPluginsDir.isEmpty()) {
        mGlobalSettingsWidget->setNewImageLoaderPath(mImageLoaderPluginsDir);
        return;
    }
    mGlobalSettingsWidget->setNewImageLoaderPath("-");
}


SettingsView::~SettingsView()
{
    delete ui;
}

void SettingsView::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        // this event is send if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

void SettingsView::slot_retranslate()
{
    for (int i = 0; i < ui->pluginList->count(); i++){
        ui->pluginList->item(i)->setText(ui->pluginWidget->widget(i)->windowTitle());
    }
}

