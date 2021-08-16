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
    void setGlobalSettingsError(QString error);

    /**
     * @brief setCurrentProjectDirectory sets project directory.
     *
     * @param path path of project directory.
     */
    void setCurrentProjectDirectory(QString path);

    /**
     * @brief setCurrentClassificationPluginDirectory sets classification plugin directory.
     *
     * @param path path of classification plugin directory.
     */
    void setCurrentClassificationPluginDirectory(QString path);

    /**
     * @brief setCurrentImageLoaderPluginDirectory sets imageloader plugin directory.
     *
     * @param path path of imageloader plugin directory.
     */
    void setCurrentImageLoaderPluginDirectory(QString path);

    /**
     * @brief addPluginWidgets adds plugin widgets to SettingsView.
     * @param pluginNames names of plugins.
     * @param pluginConfigurationWidgets config widgets of plugins.
     */
    void addPluginWidgets(QStringList pluginNames, QList<QWidget *> pluginConfigurationWidgets);
public slots:
    /**
     * @brief slot_retranslate is used to update translated pluginlist.
     *
     */
    void slot_retranslate();

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
    void changeEvent(QEvent *event);
private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void slot_setProjectDir();
    void slot_setClassificationPluginsDir();
    void slot_setImageLoaderPluginsDir();

private:
    Ui::SettingsView *ui;
    GlobalSettingsWidget * mGlobalSettingsWidget;

    QString mProjectDir;
    QString mClassificationPluginsDir;
    QString mImageLoaderPluginsDir;


};

#endif // SETTINGSVIEW_H
