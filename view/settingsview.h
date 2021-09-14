#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>

#include "globalsettingswidget.h"

namespace Ui {
class SettingsView;
}

/**
 * @brief The SettingsView class is an UI class for changing programm settings.
 *
 */
class SettingsView : public QWidget
{
    Q_OBJECT


public:
    /**
     * @brief SettingsView constructor creates a SettingsView.
     *
     * @param parent Optional parent widget.
     */
    explicit SettingsView(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~SettingsView();

    /**
     * @brief SettingsView constructor creates a SettingsView with a list of settings.
     *
     * @param parent parent widget.
     * @param pluginNames list of plugins.
     * @param pluginConfigurationWidgets list of settings widgets provided by plugins.
     */
    SettingsView(QWidget *parent, const QStringList &pluginNames, const QList<QWidget*> &pluginConfigurationWidgets);

    /**
     * @brief pathsUpdated shows according text based on amount parameter.
     *
     * @param amount number of paths updated.
     */
    void pathsUpdated(int amount);

    /**
     * @brief clearPaths clears set paths.
     */
    void clearPaths();

    /**
     * @brief setGlobalSettingsError sets error message in GlobalSettingsWidget.
     *
     * @param error the error message.
     */
    void setGlobalSettingsError(const QString &error);

    /**
     * @brief setCurrentProjectDirectory sets project directory.
     *
     * @param path path of project directory.
     */
    void setCurrentProjectDirectory(const QString &path);

    /**
     * @brief setCurrentClassificationPluginDirectory sets classification plugin directory.
     *
     * @param path path of classification plugin directory.
     */
    void setCurrentClassificationPluginDirectory(const QString &path);

    /**
     * @brief setCurrentImageLoaderPluginDirectory sets imageloader plugin directory.
     *
     * @param path path of imageloader plugin directory.
     */
    void setCurrentImageLoaderPluginDirectory(const QString &path);

    /**
     * @brief addPluginWidgets adds plugin widgets to SettingsView.
     * @param pluginNames names of plugins.
     * @param pluginConfigurationWidgets config widgets of plugins.
     */
    void addPluginWidgets(QStringList pluginNames, QList<QWidget *> pluginConfigurationWidgets);

signals:
    /**
     * @brief sig_applyGlobalSettings send when global settings should be applied.
     *
     * @param projectsDir selected project directory.
     * @param classificationPluginsDir selected classification plugin directory.
     * @param imageLoaderPluginsDir selected imageloader plugin directory.
     */
    void sig_applyGlobalSettings(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPluginsDir);

    /**
     * @brief sig_applySettings send when settings at index should be applied.
     *
     * @param index position of plugin settings widget.
     */
    void sig_applySettings(int index);

protected:

    /**
     * @brief changeEvent event handler
     *
     * @param event incoming event
     */
    void changeEvent(QEvent *event);

private slots:

    [[maybe_unused]] void on_saveButton_clicked();

    [[maybe_unused]] void on_cancelButton_clicked();

    void slot_setProjectDir();
    void slot_setClassificationPluginsDir();

    void slot_setImageLoaderPluginsDir();

private:
    static constexpr auto PROJECT_SELECT = QT_TR_NOOP("Select project directory");
    static constexpr auto CLASSIFICATION_SELECT = QT_TR_NOOP("Select classification plugin directory");
    static constexpr auto LOADER_SELECT = QT_TR_NOOP("Select image loader plugin directory");

    static constexpr auto EMPTY_PATH = "";

    Ui::SettingsView *ui;
    QScopedPointer<GlobalSettingsWidget> mGlobalSettingsWidget;

    QString mProjectDir;
    QString mClassificationPluginsDir;
    QString mImageLoaderPluginsDir;

    /**
     * @brief This method is used to update translated plugin list.
     */
    void retranslateUi();

};

#endif // SETTINGSVIEW_H
