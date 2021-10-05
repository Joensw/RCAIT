#include "settingsview.h"
#include "ui_settingsview.h"


SettingsView::SettingsView(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SettingsView) {
    ui->setupUi(this);
    retranslateUi();
}

SettingsView::SettingsView(QWidget *parent, const QStringList &pluginNames,
                           const QList<QSharedPointer<QWidget>> &pluginConfigurationWidgets,
                           const QList<QSharedPointer<QIcon>> &pluginIcons) :
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
    connect(&*mGlobalSettingsWidget, &GlobalSettingsWidget::sig_setGeneralPythonPath, this,
            &SettingsView::slot_setGeneralPythonPath);

    ui->pluginWidget->addWidget(&*mGlobalSettingsWidget);

    addPluginWidgets(pluginNames, pluginConfigurationWidgets, pluginIcons);

    //Without this the GlobalSettingsWidget ist shown, but the index of the list is at -1, leading to crashes.
    ui->pluginList->setCurrentRow(0);
}

void SettingsView::addPluginWidgets(const QStringList &pluginNames,
                                    const QList<QSharedPointer<QWidget>> &pluginConfigurationWidgets,
                                    const QList<QSharedPointer<QIcon>> &pluginIcons) {
    for (int i = ui->pluginWidget->count() - 1; i >= 1; --i) {
        delete (ui->pluginList->takeItem(i));
        QWidget *widget = ui->pluginWidget->widget(i);
        ui->pluginWidget->removeWidget(widget);
        //we don't delete the widget here. If it is deleted, the shared pointer pointing to it cannot call the destructor and
        //the program crashes. We let the shared pointer handle the destruction of the Widget, which is why we use it
    }

    assert(pluginNames.size() == pluginConfigurationWidgets.size());

    for (int i = 0; i < pluginNames.size(); i++) {
        //Use translatable accessible name, fall back to codename (english) if needed
        auto pluginName = pluginConfigurationWidgets[i]->accessibleName().isEmpty()
                          ? pluginNames[i]
                          : pluginConfigurationWidgets[i]->accessibleName();

        QListWidgetItem *pluginEntry;
        if (pluginIcons[i]->isNull())
            pluginEntry = new QListWidgetItem(QIcon(PLUGIN_ICON), pluginName);
        else
            pluginEntry = new QListWidgetItem(*pluginIcons[i], pluginName);

        ui->pluginList->addItem(pluginEntry);
        ui->pluginWidget->addWidget(&*pluginConfigurationWidgets[i]);
    }

}

void SettingsView::pathsUpdated(const int &amount) const {
    mGlobalSettingsWidget->showUpdate(amount);
}

void SettingsView::clearPaths() {
    mClassificationPluginsDir.clear();
    mImageLoaderPluginsDir.clear();
    mProjectDir.clear();
    mGlobalSettingsWidget->clearNewPaths();
}

void SettingsView::setGlobalSettingsError(const QString &error) const {
    mGlobalSettingsWidget->setError(error);
}

void SettingsView::setCurrentProjectDirectory(const QString &path) const {
    mGlobalSettingsWidget->setCurrentProjectsDir(path);
}

void SettingsView::setCurrentClassificationPluginDirectory(const QString &path) const {
    mGlobalSettingsWidget->setCurrentClassificationDir(path);
}

void SettingsView::setCurrentImageLoaderPluginDirectory(const QString &path) const {
    mGlobalSettingsWidget->setCurrentImageLoaderDir(path);
}

void SettingsView::setCurrentPythonExecutablePath(const QString &path) const {
    mGlobalSettingsWidget->setCurrentPythonPath(path);
}

[[maybe_unused]] void SettingsView::on_saveButton_clicked() {
    int index = ui->pluginList->currentIndex().row();

    if (index == 0) {
        emit sig_applyGlobalSettings(mProjectDir, mClassificationPluginsDir, mImageLoaderPluginsDir,
                                     mPythonExecutablePath);
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
    mProjectDir = QFileDialog::getExistingDirectory(this, tr(PROJECT_SELECT_MSG));
    mGlobalSettingsWidget->setNewProjectPath(mProjectDir);
}

void SettingsView::slot_setClassificationPluginsDir() {
    mClassificationPluginsDir = QFileDialog::getExistingDirectory(this, tr(CLASSIFICATION_SELECT_MSG));
    mGlobalSettingsWidget->setNewClassificationPluginPath(mClassificationPluginsDir);
}

void SettingsView::slot_setImageLoaderPluginsDir() {
    mImageLoaderPluginsDir = QFileDialog::getExistingDirectory(this, tr(LOADER_SELECT_MSG));
    mGlobalSettingsWidget->setNewImageLoaderPath(mImageLoaderPluginsDir);
}

void SettingsView::slot_setGeneralPythonPath() {
    mPythonExecutablePath = QFileDialog::getOpenFileName(this, tr(PYTHON_SELECT_MSG));
    mGlobalSettingsWidget->setNewPythonPath(mPythonExecutablePath);
}


SettingsView::~SettingsView() {
    //we have to set the parent of our settingswidgets to nullptr
    //they have to be deleted with their qshared_pointer
    //otherwise the QObject system deletes them when our UI is deleted.
    for (int i = ui->pluginWidget->count() - 1; i >= 1; --i) {
        QWidget *widget = ui->pluginWidget->widget(i);
        ui->pluginWidget->removeWidget(widget);
        widget->setParent(nullptr);
    }

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

