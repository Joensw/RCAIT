#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <QMessageBox>

#include <settingsview.h>
#include <datamanager.h>
#include "configurationdialog.h"



/**
 * @brief The SettingsController class mediates between the settings logic and settings UI.
 *
 */
class SettingsController : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief SettingsController constructs a SettingsController with the given parameters.
     *
     * @param parent optional parent object.
     * @param dataManager source of general information.
     */
    explicit SettingsController(QObject *parent = nullptr, DataManager *dataManager = nullptr);


public slots:

    /**
     * @brief slot_openSettings opens a SettingView when triggered.
     *
     */
    void slot_openSettings();

    /**
     * @brief slot_applySettings aplies settings of plugin at index.
     *
     * @param index position of plugin settings widget.
     */
    void slot_applySettings(int index);

    /**
     * @brief slot_applyGlobalSettings applies global settings.
     * @param projectDir projectsDir selected project directory.
     * @param classificationPluginDir selected classification plugin directory.
     * @param imageLoaderPluginsDir selected imageloader plugin directory.
     */
    void slot_applyGlobalSettings(QString projectDir, QString classificationPluginDir, QString imageLoaderPluginsDir);

signals:

    /**
     * @brief sig_projectDirectoryChanged emitted when project directory is changed.
     *
     */
    void sig_projectDirectoryChanged();


    /**
     * @brief sig_imgagePluginsChanged emitted when image plugins directory is changed.
     *
     */
    void sig_imagePluginsDirectoryChanged();

private:
    SettingsView *mSettingsView;

    DataManager *mDataManager;

};

#endif // SETTINGSCONTROLLER_H
