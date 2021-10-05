#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <QString>
#include <QWidget>
#include <QSettings>
#include <QIcon>
#include <QDir>

/**
 * @brief The ConfigurationManager class contains the logic for configuration of the working directories and paths to plugins.
 */
class ConfigurationManager final : public QObject {

Q_OBJECT
public:

    /**
     * @brief ConfigurationManager deleted copy constructor
     */
    ConfigurationManager(const ConfigurationManager &) = delete;

    /**
     * @brief operator = deleted assignment operator
     */
    ConfigurationManager &operator=(const ConfigurationManager &) = delete;

    /**
     * @brief getInstance returns the only instance of the ConfigurationManager class
     * @return instance
     */
    static ConfigurationManager &getInstance() {
        // Guaranteed to be destroyed.
        static ConfigurationManager INSTANCE;
        return INSTANCE;
    }

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
                               const QString &imageLoaderDirectory, const QString &pythonPath) const;

    /**
     * @brief saveProjectsDir sets the value of the projects directory
     * @param dir the absolute path to the new projects directory
     */
    void saveProjectsDir(const QString &dir) const;

    /**
     * @return the absolute path to the current projects directory
     */
    [[nodiscard]] QString getProjectsDir() const;

    /**
     * @brief saveClassificationPluginDir set the value of the classification plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveClassificationPluginDir(const QString &dir) const;

    /**
     * @return the absolute path to the current classification plugin directory
     */
    [[nodiscard]] QString getClassificationPluginDir() const;

    /**
     * @brief saveImageLoaderPluginDir set the value of the image loader plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveImageLoaderPluginDir(const QString &dir) const;

    /**
     * @brief savePythonPath set the value of the python executable path
     * @param path the absolute path to the new python executable
     */
    void savePythonPath(const QString &path) const;

    /**
     * @return the absolute path to the current image loader plugin directory
     */
    [[nodiscard]] QString getImageLoaderPluginDir() const;

    /**
     * @return the absolute path to the currently set python executable
     * @fallback Uses "python" instead of an actual path in the case of no path being set.
     * This will prevent potential crashes.
     */
    [[nodiscard]] QString getPythonExecutablePath() const;

private:
    //Keys for the QSettings Settings object
    static constexpr auto projectDirectoryIdentifier = "ProjectDirectory";
    static constexpr auto classificationPluginDirectoryIdentifier = "ClassificationPluginPath";
    static constexpr auto imageLoaderPluginDirectoryIdentifier = "ImageLoaderPluginPath";
    static constexpr auto pythonExecutablePathIdentifier = "PythonPath";
    static constexpr auto PYTHON_FALLBACK = "python";
    QScopedPointer<QSettings> mGlobalSettings;

    ConfigurationManager();
};

#endif // CONFIGURATIONMANAGER_H
