/**
 * @file settingsmanager.h
 *
 * @brief functions for managing application and plugin settings
 *
 * @author Jonas Wille
 *
 */
#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QWidget>
#include <QSettings>
#include <QIcon>

#include <classificationpluginmanager.h>
#include <imageloaderpluginmanager.h>
#include <configurationmanager.h>
#include <ostream>

/**
 * The SettingsManager contains logic for global settings of the application as well as plugin specific settings
 * @brief The SettingsManager class contains the logic for for the settings UI
 */
class SettingsManager : public QObject {
Q_OBJECT
public:

    /**
     * @brief SettingsManager deleted copy constructor
     */

    SettingsManager(const SettingsManager &) = delete;

    /**
     * Default destructor.
     */
    ~SettingsManager() override = default;

    /**
     * @brief operator = deleted assignment operator
     */

    SettingsManager &operator=(const SettingsManager &) = delete;

    /**
     * @brief getInstance returns the only instance of the SettingsManager class
     * @return instance
     */
    static SettingsManager &getInstance() {
        static SettingsManager INSTANCE; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return INSTANCE;
    }

    /**
     * @return a list of the names of all the plugins that were loaded
     */
    QStringList getPluginNames();

    /**
     * @return the input UI's of all the plugins
     */
    QList<QSharedPointer<QWidget>> getPluginSettings();

    /**
     * @brief savePluginSettings saves the settings of the plugin specified in the UI at the current index
     * @param index position of plugin settings widget
     */
    void savePluginSettings(int index);

    /**
     * @brief applyGlobalSettings changes the program paths according to parameters, if they are resolvable.
     * @param projectsDir the new projects directory
     * @param classificationPluginDir the new classification plugin directory
     * @param imageLoaderPluginDir the new image loader plugin directory
     * @param pythonPath the new path to the python executable
     * @param error optional argument, if an error occurs it will be written to here
     * @param pathChanged optional argument, the amount of paths updated will be written here
     * @return true if the new paths could be applied, false otherwise
     */
    bool applyGlobalSettings(const QString &projectsDir, const QString &classificationPluginDir,
                             const QString &imageLoaderPluginDir,
                             const QString &pythonPath, QString &error, int &pathsChanged);

    /**
     * @return the names of all loaded image loader plugins
     */
    QStringList getImageLoaderPluginNames();

    /**
     * @return the names of all loaded classification plugins
     */
    QStringList getClassificationPluginNames();

    /**
     * @param basesOf the classification plugin
     * @return list of the bases of a particular classification plugin
     */
    QStringList getClassificationPluginBase(const QString &plugin);

    /**
     * @brief reload manually prompt the plugin managers to reload the plugins from the current directories
     */
    void reload();

    /**
     * @brief getPluginIcons gets the icons of the plugins
     * @return the icons
     */
    QList<QSharedPointer<QIcon>> getPluginIcons();

    /**
     * @brief saveClassificationPluginDir set the value of the classification plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveClassificationPluginDir(const QString &dir);

    /**
     * @brief saveImageLoaderPluginDir set the value of the image loader plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveImageLoaderPluginDir(const QString &dir);

private:

    static constexpr auto ERROR_CONFLICT = QT_TR_NOOP(
                                                   "Settings have not been updated, there is a conflict. "
                                                   "\n Paths may not be identical and must exist, this includes new and unchanged paths.");

    ClassificationPluginManager *mClassificationPluginManager;
    ImageLoaderPluginManager *mImageLoaderPluginManager;
    ConfigurationManager *mConfigurationManager;

    SettingsManager();

};

#endif // SETTINGSMANAGER_H
