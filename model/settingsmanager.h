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

#include <classificationpluginmanager.h>
#include <imageloaderpluginmanager.h>

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
     * @brief operator = deleted assignment operator
     */

    SettingsManager &operator=(const SettingsManager &) = delete;

    /**
     * @brief getInstance returns the only instance of the SettingsManager class
     * @return instance
     */
    static SettingsManager &getInstance() {
        static SettingsManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
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
     * @brief saveProjectsDir sets the value of the projects directory
     * @param dir the absolute path to the new projects directory
     */
    void saveProjectsDir(const QString &dir);

    /**
     * @return the absolute path to the current projects directory
     */
    QString getProjectsDir();

    /**
     * @brief saveClassificationPluginDir set the value of the classification plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveClassificationPluginDir(const QString &dir);

    /**
     * @return the absolute path to the current classification plugin directory
     */
    QString getClassificationPluginDir();

    /**
     * @brief saveImageLoaderPluginDir set the value of the image loader plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveImageLoaderPluginDir(const QString &dir);

    /**
     * @brief savePythonPath set the value of the python executable path
     * @param path the absolute path to the new python executable
     */
    void savePythonPath(const QString &path);

    /**
     * @return the absolute path to the current image loader plugin directory
     */
    QString getImageLoaderPluginDir();

    /**
     * @return the absolute path to the currently set python executable
     */
    QString getPythonExecutablePath();

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
                             const QString &pythonPath, QString *error = nullptr, int *pathsChanged = nullptr);

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
     * The paths are valid, when they are not empty ie. "" or the nullstring, when they are not identical, and actually exist.
     * If the paths provided arent absolute there is no guarantee for whether the check passes or fails.
     *
     * @brief verifyDirectories check if the current set directories are valid
     * @return true if they are, false otherwise
     */
    bool verifyDirectories();

    /**
     * The paths are valid, when they are not empty ie. "" or the nullstring, when they are not identical, and actually exist.
     * If the paths provided arent absolute there is no guarantee for whether the check passes or fails.
     *
     * @brief verifyPaths check if the the specified directories would be considered valid by the application
     * @param paths list of paths to check for validity
     * @return true if valid, false otherwise
     */
    static bool verifyPaths(const QStringList &paths);

    /** Used by the configuration controller, to set paths for further program use
     * @brief configureSettingsFile set the paths in the settings file
     * @param projectsDirectory absolute path to the projects directory
     * @param classificationPluginDirectory absolute path the the classification plugin directory
     * @param imageLoaderDirectory absolute path to the image loader plugin directory
     */
    void configureSettingsFile(const QString &projectsDirectory, const QString &classificationPluginDirectory,
                               const QString &imageLoaderDirectory, const QString &pythonPath);

    /**
     * @brief reload manually prompt the plugin managers to reload the plugins from the current directories
     */
    void reload();

private:
    //Keys for the QSettings Settings object
    static constexpr auto projectDirectoryIdentifier = "ProjectDirectory";
    static constexpr auto classificationPluginDirectoryIdentifier = "ClassificationPluginPath";
    static constexpr auto imageLoaderPluginDirectoryIdentifier = "ImageLoaderPluginPath";
    static constexpr auto pythonExecutablePathIdentifier = "PythonPath";

    static constexpr auto ERROR_CONFLICT = QT_TR_NOOP(
            "Settings have not been updated, there is a conflict. \n Paths may not be identical and must exist, this includes new and unchanged paths.");

    ClassificationPluginManager *mClassificationPluginManager;
    ImageLoaderPluginManager *mImageLoaderPluginManager;


    QScopedPointer<QSettings> mGlobalSettings;

    SettingsManager();

};

#endif // SETTINGSMANAGER_H
