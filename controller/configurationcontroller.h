#ifndef CONFIGURATIONCONTROLLER_H
#define CONFIGURATIONCONTROLLER_H

#include <QObject>
#include <QMessageBox>
#include "datamanager.h"
#include "configurationdialog.h"

/**
 * @brief The ConfigurationController class mediates between the configuration UI and the configuration logic
 */
class ConfigurationController : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ConfigurationController constructs a ConfigurationController with the given parameters
     * @param parent optional parent object
     * @param dataManager source of general information
     */
    explicit ConfigurationController(QObject *parent = nullptr, DataManager *dataManager = nullptr);

    /**
     * If the paths are not resolvable the configuration UI will open, otherwise a signal to symbolize a successful configuration will be emitted
     * @brief verify checks if application critical paths are set correctly
     */
    void verify();
public slots:
    /**
     * @brief slot_directoriesSpecified ports user specified paths into the application iff they are acceptable, otherwise shows on error message in the configuration UI
     * @param projectDir selected project directory
     * @param classificationPluginDir selected classification plugin directory
     * @param imageLoaderPluginsDir selected image loader plugin directory
     */
    void slot_directoriesSpecified(QString projectDir, QString classificationPluginDir, QString imageLoaderPluginsDir);
signals:
    /**
     * @brief sig_configurationComplete emitted when the configuration is accepted
     */
    void sig_configurationComplete();
private:
    ConfigurationDialog *mConfigurationDialog;

    DataManager *mDataManager;
};

#endif // CONFIGURATIONCONTROLLER_H
