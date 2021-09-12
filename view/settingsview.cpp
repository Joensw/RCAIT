#include "settingsview.h"
#include "ui_settingsview.h"


SettingsView::SettingsView(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SettingsView) {
    ui->setupUi(this);
}

SettingsView::SettingsView(QWidget *parent, const QStringList &pluginNames,
                           const QList<QWidget *> &pluginConfigurationWidgets) :
        QWidget(parent),
        ui(new Ui::SettingsView),
        mGlobalSettingsWidget(new GlobalSettingsWidget(this)) {
    ui->setupUi(this);

    ui->pluginList->addItem(mGlobalSettingsWidget->windowTitle());

    connect(&*mGlobalSettingsWidget, &GlobalSettingsWidget::sig_setProjectDir, this, &SettingsView::slot_setProjectDir);
    connect(&*mGlobalSettingsWidget, &GlobalSettingsWidget::sig_setClassificationPluginsDir, this,
            &SettingsView::slot_setClassificationPluginsDir);
    connect(&*mGlobalSettingsWidget, &GlobalSettingsWidget::sig_setImageLoaderPluginsDir, this,
            &SettingsView::slot_setImageLoaderPluginsDir);

    ui->pluginWidget->addWidget(&*mGlobalSettingsWidget);

    addPluginWidgets(pluginNames, pluginConfigurationWidgets);

    //Without this the GlobalSettingsWidget ist shown, but the index of the list is at -1, leading to crashes.
    ui->pluginList->setCurrentRow(0);
}

void SettingsView::addPluginWidgets(QStringList pluginNames, QList<QWidget *> pluginConfigurationWidgets) {
    for (int i = ui->pluginWidget->count() - 1; i >= 1; --i) {
        delete (ui->pluginList->takeItem(i));
        QWidget *widget = ui->pluginWidget->widget(i);
        ui->pluginWidget->removeWidget(widget);
        widget->deleteLater();
    }

    assert(pluginNames.size() == pluginConfigurationWidgets.size());

    for (int i = 0; i < pluginNames.size(); i++) {
        ui->pluginList->addItem(pluginNames[i]);
        ui->pluginWidget->addWidget(pluginConfigurationWidgets[i]);
    }
}

void SettingsView::pathsUpdated(int amount) {
    mGlobalSettingsWidget->showUpdate(amount);
}

void SettingsView::clearPaths() {
    mClassificationPluginsDir.clear();
    mImageLoaderPluginsDir.clear();
    mProjectDir.clear();
    mGlobalSettingsWidget->clearNewPaths();
}

void SettingsView::setGlobalSettingsError(const QString &error) {
    mGlobalSettingsWidget->setError(error);
}

void SettingsView::setCurrentProjectDirectory(const QString &path) {
    mGlobalSettingsWidget->setCurrentProjectsDir(path);
}

void SettingsView::setCurrentClassificationPluginDirectory(const QString &path) {
    mGlobalSettingsWidget->setCurrentClassificationDir(path);
}

void SettingsView::setCurrentImageLoaderPluginDirectory(const QString &path) {
    mGlobalSettingsWidget->setCurrentImageLoaderDir(path);
}

[[maybe_unused]] void SettingsView::on_saveButton_clicked() {
    int index = ui->pluginList->currentIndex().row();

    if (index == 0) {
        emit sig_applyGlobalSettings(mProjectDir, mClassificationPluginsDir, mImageLoaderPluginsDir);
    } else {
        // -1 because 0th entry is Global settings
        emit sig_applySettings(index - 1);
    }
}

[[maybe_unused]] void SettingsView::on_cancelButton_clicked() {
    this->close();
}

//private slots for global settings widget
void SettingsView::slot_setProjectDir() {
    mProjectDir = QFileDialog::getExistingDirectory(this, tr("Select project directory"));
    if (!mProjectDir.isEmpty()) {
        mGlobalSettingsWidget->setNewProjectPath(mProjectDir);
        return;
    }
    mGlobalSettingsWidget->setNewProjectPath("-");
}

void SettingsView::slot_setClassificationPluginsDir() {
    mClassificationPluginsDir = QFileDialog::getExistingDirectory(this, tr("Select classification plugin directory"));
    if (!mClassificationPluginsDir.isEmpty()) {
        mGlobalSettingsWidget->setNewClassificationPluginPath(mClassificationPluginsDir);
        return;
    }
    mGlobalSettingsWidget->setNewClassificationPluginPath("-");
}

void SettingsView::slot_setImageLoaderPluginsDir() {
    mImageLoaderPluginsDir = QFileDialog::getExistingDirectory(this, tr("Select image loader plugin directory"));
    if (!mImageLoaderPluginsDir.isEmpty()) {
        mGlobalSettingsWidget->setNewImageLoaderPath(mImageLoaderPluginsDir);
        return;
    }
    mGlobalSettingsWidget->setNewImageLoaderPath("-");
}


SettingsView::~SettingsView() {
    delete ui;
}

void SettingsView::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        retranslateUi();
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}


void SettingsView::retranslateUi() {
    for (int i = 0; i < ui->pluginList->count(); i++) {
        auto text = ui->pluginWidget->widget(i)->windowTitle();
        ui->pluginList->item(i)->setText(text);
    }
}

