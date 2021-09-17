#include "settingsview.h"
#include "ui_settingsview.h"


SettingsView::SettingsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsView) {
    ui->setupUi(this);
    retranslateUi();
}

SettingsView::SettingsView(QWidget *parent, const QStringList &pluginNames,
                           const QList<QWidget *> &pluginConfigurationWidgets) :
    QWidget(parent),
    ui(new Ui::SettingsView),
    mGlobalSettingsWidget(new GlobalSettingsWidget(this)) {
    ui->setupUi(this);

    auto globalSettingsEntry = new QListWidgetItem(QIcon(CONFIGURATION_ICON), mGlobalSettingsWidget->windowTitle());
    ui->pluginList->addItem(globalSettingsEntry);

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
        auto pluginEntry = new QListWidgetItem(QIcon(PLUGIN_ICON), pluginNames[i]);
        ui->pluginList->addItem(pluginEntry);
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
    mProjectDir = QFileDialog::getExistingDirectory(this, PROJECT_SELECT_MSG);
    if (!mProjectDir.isEmpty()) {
        mGlobalSettingsWidget->setNewProjectPath(mProjectDir);
        return;
    }
    mGlobalSettingsWidget->setNewProjectPath(EMPTY_PATH);
}

void SettingsView::slot_setClassificationPluginsDir() {
    mClassificationPluginsDir = QFileDialog::getExistingDirectory(this, CLASSIFICATION_SELECT_MSG);
    if (!mClassificationPluginsDir.isEmpty()) {
        mGlobalSettingsWidget->setNewClassificationPluginPath(mClassificationPluginsDir);
        return;
    }
    mGlobalSettingsWidget->setNewClassificationPluginPath(EMPTY_PATH);
}

void SettingsView::slot_setImageLoaderPluginsDir() {
    mImageLoaderPluginsDir = QFileDialog::getExistingDirectory(this, LOADER_SELECT_MSG);
    if (!mImageLoaderPluginsDir.isEmpty()) {
        mGlobalSettingsWidget->setNewImageLoaderPath(mImageLoaderPluginsDir);
        return;
    }
    mGlobalSettingsWidget->setNewImageLoaderPath(EMPTY_PATH);
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
        auto text = ui->pluginWidget->widget(i)->accessibleName();
        ui->pluginList->item(i)->setText(text);
    }
}

