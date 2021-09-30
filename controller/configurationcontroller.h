/**
 * @file configurationcontroller.h
 *
 * @brief insures program vital information is present before use of the applications
 *
 * @author Jonas Wille
 */
#ifndef CONFIGURATIONCONTROLLER_H
#define CONFIGURATIONCONTROLLER_H

#include <QObject>
#include <QMessageBox>
#include "datamanager.h"
#include "configurationdialog.h"
#include "settingsmanager.h"

/**
 * @brief The ConfigurationController class mediates between the configuration UI and the configuration logic
 */
class ConfigurationController final : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ConfigurationController constructs a ConfigurationController with the given parameters
     * @param parent optional parent object
     */
    explicit ConfigurationController(QObject *parent = nullptr);

    /**
     * If the paths are not resolvable the configuration UI will open, otherwise a signal to symbolize a successful configuration will be emitted
     * @brief verify checks if application critical paths are set correctly
     */
    void verify();

    /**
     * @brief operator = deleted assignment operator
     * @return
     */
    ConfigurationController &operator=(const ConfigurationController &) = delete;
public slots:
    /**
     * @brief slot_directoriesSpecified ports user specified paths into the application iff they are acceptable, otherwise shows on error message in the configuration UI
     * @param projectDir selected project directory
     * @param classificationPluginDir selected classification plugin directory
     * @param imageLoaderPluginsDir selected image loader plugin directory
     */
    void slot_directoriesSpecified(const QString &projectDir, const QString &classificationPluginDir,
                                   const QString &imageLoaderPluginsDir, const QString &pythonPath);
signals:
    /**
     * @brief sig_configurationComplete emitted when the configuration is accepted
     */
    void sig_configurationComplete();
private:
    QScopedPointer<ConfigurationDialog> mConfigurationDialog;

    SettingsManager *mSettingsManager;
    ConfigurationManager *mConfigurationManager;


};

#endif // CONFIGURATIONCONTROLLER_H
