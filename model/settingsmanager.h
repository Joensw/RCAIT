#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QWidget>
#include <QSettings>

#include "classificationpluginmanager.h"
#include "imageloaderpluginmanager.h"

extern const QString GLOBAL_SETTINGS_LOCATION;

/**
 * The SettingsManager contains logic for global settings of the application as well as plugin specific settings
 * @brief The SettingsManager class contains the logic for for the settings UI
 */
class SettingsManager{
public:
    SettingsManager(); //might also become a singleton? TODO
    /**
     * @return a list of the names of all the plugins that were loaded
     */
    QStringList getPluginNames();

    /**
     * @return the input UI's of all the plugins
     */
    QList<QWidget*> getPluginSettings();

    /**
     * @brief savePluginSettings saves the settings of the plugin specified in the UI at the current index
     * @param index position of plugin settings widget
     */
    void savePluginSettings(int index);

    /**
     * @brief saveProjectsDir sets the value of the projects directory
     * @param dir the absolute path to the new projects directory
     */
    void saveProjectsDir(QString dir);

    /**
     * @return the absolute path to the current projects directory
     */
    QString getProjectsDir();

    /**
     * @brief saveClassificationPluginDir set the value of the classification plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveClassificationPluginDir(QString dir);

    /**
     * @return the absolute path to the curent classifcation plugin directory
     */
    QString getClassificationPluginDir();

    /**
     * @brief saveImageLoaderPluginDir set the value of the image loader plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveImageLoaderPluginDir(QString dir);

    /**
     * @return the absolute path to the current image loader plugin directory
     */
    QString getImageLoaderPluginDir();

    /**
     * @brief applyGlobalSettings changes the program paths acording to parameters, if they are resolvable.
     * @param projectsDir the new projects directory
     * @param classificationPluginDir the new classification plugin directory
     * @param imageLoaderPluginDir the new image loader pluign directory
     * @param error optional argument, if an error occurs it will be written to here
     * @return true if the new paths could be applied, false otherwise
     */
    bool applyGlobalSettings(QString projectsDir, QString classificationPluginDir, QString imageLoaderPluginDir,
                             QString * error = nullptr, int * pathsChanged = nullptr);

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
     * @return list of of the bases a particular classification plugin
     */
    QStringList getClassificationPluginBase(QString basesOf);

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
     * @param projectsDirectory absolute path to the projects directory
     * @param classificationPluginDirectory absolute path the the classification plugin directory
     * @param imageLoaderDirectory absolute path to the image loader plugin directory
     * @return true if valid, false otherwise
     */
    bool verifyPaths(QString projectsDirectory, QString classificationPluginDirectory, QString imageLoaderDirectory);

    /**
     * @brief verifyPath check if a single path would be considered valid on it own
     * @param path the absolute path
     * @return true if valid, false otherwise
     */
    bool verifyPath(QString path);

private:
    ClassificationPluginManager * mClassificationPluginManager;
    ImageLoaderPluginManager * mImageLoaderPluginManager;


    QSettings * mGlobalSettings;



};

#endif // SETTINGSMANAGER_H
