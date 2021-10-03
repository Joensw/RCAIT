/**
 * @file settingscontroller.h
 *
 * @brief connects the logic of the settings with the visual user interface
 *
 * @author Jonas Wille
 */
#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <QMessageBox>

#include <settingsview.h>
#include <datamanager.h>
#include <utility>
#include <configurationdialog.h>

/**
 * @brief The SettingsController class mediates between the settings logic and settings UI.
 *
 */
class SettingsController final : public QObject {
Q_OBJECT
public:

    /**
     * @brief SettingsController constructs a SettingsController with the given parameters.
     *
     * @param parent optional parent object.
     * @param dataManager source of general information.
     */
    explicit SettingsController(QObject *parent = nullptr, DataManager *dataManager = nullptr);

    /**
     * @brief operator = deleted assignment operator
     */
    SettingsController &operator=(const SettingsController &) = delete;


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
     * @param pythonPath selected path to python executable
     */
    void slot_applyGlobalSettings(QString projectDir, QString classificationPluginDir, QString imageLoaderPluginDir,
                                  QString pythonPath);

signals:

    /**
     * @brief sig_projectDirectoryChanged emitted when project directory is updated
     *
     */
    void sig_projectDirectoryChanged(const QString &newDirectory);


    /**
     * @brief sig_imgagePluginsChanged emitted when image plugins directory is changed.
     *
     */
    void sig_imagePluginsDirectoryChanged(const QString &newDirectory);


    /**
     * @brief sig_classificationDirectoryChanged emmitted when classification plugin directory is changed.
     * @param newDirectory
     */
    void sig_classificationDirectoryChanged(const QString &newDirectory);

    /**
     * @brief sig_settingsApplied emitted when the global settings have been applied
     */
    void sig_settingsApplied();

private:
    QScopedPointer<SettingsView> mSettingsView;

    DataManager *mDataManager;

};

#endif // SETTINGSCONTROLLER_H
